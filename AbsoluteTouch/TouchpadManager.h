#ifndef TOUCHPAD_MANAGER_H
#define TOUCHPAD_MANAGER_H

#include "Include/SynKit.h"
#include "Containers.h"

class TouchpadManager : private _ISynDeviceEvents
{
public:
    bool Initialize(Rect<int> screenRect);
    bool Acquire();
    void Unacquire();
    void SetTouchpadEnabled(bool enabled);
    Rect<long> GetDefaultTouchpadRect();
    void SetTouchpadRect(Rect<long> rect);
    void SetScreenRect(Rect<int> rect);
    ~TouchpadManager();

private:
    Point<int> TouchpadToScreenCoords(long touchpadX, long touchpadY);
    HRESULT STDMETHODCALLTYPE OnSynDevicePacket(long seqNum) override;

    ISynAPI *m_api;
    ISynDevice *m_device;
    ISynPacket *m_packet;
    Rect<long> m_touchpadRect;
    Rect<int> m_screenRect;
    bool m_initialized = false;
    bool m_coinitialized = false;
    bool m_acquired = false;
};

#endif
