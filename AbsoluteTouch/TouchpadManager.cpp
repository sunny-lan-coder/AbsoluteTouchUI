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
    return Rect<long>(minX, minY, maxX - minX, maxY - minY);
}

HRESULT STDMETHODCALLTYPE TouchpadManager::OnSynDevicePacket(long seqNum)
{
    assert(m_initialized);
    HRESULT res = m_device->LoadPacket(m_packet);
    if (res != SYN_OK && res != SYNE_SEQUENCE)
        return res;
    long fingerState;
    m_packet->GetProperty(SP_FingerState, &fingerState);
    if (!(fingerState & SF_FingerPresent))
        return SYN_OK;
    long x, y;
    m_packet->GetProperty(SP_XRaw, &x);
    m_packet->GetProperty(SP_YRaw, &y);
    if (m_callback != nullptr)
        m_callback(x, y);
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
