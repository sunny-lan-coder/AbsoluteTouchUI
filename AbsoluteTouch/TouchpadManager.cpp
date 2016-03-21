#include "TouchpadManager.h"
#include <cassert>

bool TouchpadManager::Initialize()
{
    assert(!m_coinitialized);
    HRESULT res = CoInitialize(nullptr);
    if (res != S_OK && res != S_FALSE)
        return false;
    m_coinitialized = true;
    if (CoCreateInstance(_uuidof(SynAPI), nullptr, CLSCTX_INPROC_SERVER, _uuidof(ISynAPI), (void **)&m_api) != S_OK)
        return false;
    if (m_api->Initialize() != SYN_OK)
        return false;
    long handle = -1;
    if (m_api->FindDevice(SE_ConnectionAny, SE_DeviceTouchPad, &handle) != SYN_OK)
        return false;
    if (m_api->CreateDevice(handle, &m_device) != SYN_OK)
        return false;
    if (m_device->CreatePacket(&m_packet) != SYN_OK)
        return false;
    m_device->GetProperty(SP_XLoSensor, &m_bounds.x1);
    m_device->GetProperty(SP_XHiSensor, &m_bounds.x2);
    m_device->GetProperty(SP_YLoSensor, &m_bounds.y1);
    m_device->GetProperty(SP_YHiSensor, &m_bounds.y2);
    m_initialized = true;
    return true;
}

bool TouchpadManager::Acquire()
{
    assert(m_initialized);
    if (m_acquired)
        return true;
    if (m_device->Acquire(0) != SYN_OK)
        return false;
    m_acquired = true;
    return true;
}

void TouchpadManager::Unacquire()
{
    assert(m_initialized);
    if (!m_acquired)
        return;
    HRESULT res = m_device->Unacquire();
    assert(res == SYN_OK);
    m_acquired = false;
}

void TouchpadManager::SetTouchCallback(TouchCallback callback)
{
    if (callback != nullptr && m_callback == nullptr) {
        HRESULT res = m_device->SetSynchronousNotification(this);
        assert(res == SYN_OK);
    } else if (callback == nullptr && m_callback != nullptr) {
        HRESULT res = m_device->SetSynchronousNotification(nullptr);
        assert(res == SYN_OK);
    }
    m_callback = callback;
}

bool TouchpadManager::IsTouchpadEnabled()
{
    assert(m_initialized);
    HRESULT out;
    HRESULT res = m_device->GetProperty(SP_DisableState, &out);
    assert(res == SYN_OK);
    assert(out == SYN_FALSE || out == SYN_TRUE);
    return (out == SYN_FALSE);
}

void TouchpadManager::SetTouchpadEnabled(bool enabled)
{
    assert(m_initialized);
    HRESULT res = m_device->SetProperty(SP_DisableState, enabled ? SYN_FALSE : SYN_TRUE);
    assert(res == SYN_OK);
}

Rect<long> TouchpadManager::GetDefaultTouchpadRect()
{
    assert(m_initialized);
    long minX, maxX, minY, maxY;
    m_device->GetProperty(SP_XLoBorder, &minX);
    m_device->GetProperty(SP_XHiBorder, &maxX);
    m_device->GetProperty(SP_YLoBorder, &minY);
    m_device->GetProperty(SP_YHiBorder, &maxY);
    Point<long> topLeft = NormalizeCoordinates(minX, maxY);
    Point<long> bottomRight = NormalizeCoordinates(maxX, minY);
    return Rect<long>(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

Point<long> TouchpadManager::NormalizeCoordinates(long x, long y)
{
    long nx = x - m_bounds.x1;
    long ny = m_bounds.y2 - y;
    return Point<long>(nx, ny);
}

HRESULT STDMETHODCALLTYPE TouchpadManager::OnSynDevicePacket(long seqNum)
{
    assert(m_initialized);
    HRESULT res = m_device->LoadPacket(m_packet);
    if (res != SYN_OK && res != SYNE_SEQUENCE)
        return res;
    long fingerState;
    m_packet->GetProperty(SP_FingerState, &fingerState);
    if ((fingerState & SF_FingerPresent) == 0)
        return SYN_OK;
    long x, y;
    m_packet->GetProperty(SP_XRaw, &x);
    m_packet->GetProperty(SP_YRaw, &y);
    Point<long> coords = NormalizeCoordinates(x, y);
    if (m_callback != nullptr)
        m_callback(coords);
    return SYN_OK;
}

TouchpadManager::~TouchpadManager()
{
    if (m_initialized) {
        SetTouchCallback(nullptr);
        Unacquire();
    }
    if (m_coinitialized) {
        if (m_packet != nullptr) m_packet->Release();
        if (m_device != nullptr) m_device->Release();
        if (m_api != nullptr) m_api->Release();
        CoUninitialize();
    }
}
