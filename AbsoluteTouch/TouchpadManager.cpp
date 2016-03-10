#include "TouchpadManager.h"
#include <cassert>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

bool TouchpadManager::Initialize(Rect<int> screenRect)
{
    assert(!m_coinitialized);
    HRESULT res = CoInitialize(NULL);
    if (res != S_OK && res != S_FALSE)
        return false;
    m_coinitialized = true;
    if (CoCreateInstance(_uuidof(SynAPI), NULL, CLSCTX_INPROC_SERVER, _uuidof(ISynAPI), (void **)&m_api) != S_OK)
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
    SetTouchpadRect(GetDefaultTouchpadRect());
    SetScreenRect(screenRect);
    m_initialized = true;
    return true;
}

bool TouchpadManager::Acquire()
{
    assert(m_initialized);
    HRESULT res = m_device->SetSynchronousNotification(this);
    assert(res == SYN_OK);
    if (m_device->Acquire(0) != SYN_OK)
        return false;
    m_acquired = true;
    return true;
}

bool TouchpadManager::Unacquire()
{
    assert(m_initialized);
    if (!m_acquired)
        return false;
    HRESULT res = m_device->Unacquire();
    assert(res == SYN_OK);
    res = m_device->SetSynchronousNotification(NULL);
    assert(res == SYN_OK);
    m_acquired = false;
    return true;
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

void TouchpadManager::SetScreenRect(Rect<int> rect)
{
    m_screenRect = rect;
}

void TouchpadManager::SetTouchpadRect(Rect<long> rect)
{
    m_touchpadRect = rect;
}

Point<int> TouchpadManager::TouchpadToScreenCoords(long touchpadX, long touchpadY)
{
    long tpDeltaX = touchpadX - m_touchpadRect.x;
    long tpDeltaY = touchpadY - m_touchpadRect.y;
    float unitX = tpDeltaX / (float)m_touchpadRect.width;
    float unitY = tpDeltaY / (float)m_touchpadRect.height;
    int scDeltaX = (int)(unitX * m_screenRect.width);
    int scDeltaY = (int)((1.0f - unitY) * m_screenRect.height);
    int screenX = m_screenRect.x + scDeltaX;
    int screenY = m_screenRect.y + scDeltaY;
    return Point<int>(screenX, screenY);
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
    Point<int> screenCoords = TouchpadToScreenCoords(x, y);
    SetCursorPos(screenCoords.x, screenCoords.y);
    return SYN_OK;
}

TouchpadManager::~TouchpadManager()
{
    if (m_initialized) {
        Unacquire();
    }
    if (m_packet) m_packet->Release();
    if (m_device) m_device->Release();
    if (m_api) m_api->Release();
    if (m_coinitialized) {
        CoUninitialize();
    }
}
