#ifndef TOUCHPAD_MANAGER_H
#define TOUCHPAD_MANAGER_H

#include "Containers.h"
#include "Include/SynKit.h"

class TouchpadManager : private _ISynDeviceEvents
{
public:
    bool Initialize(Rect<int> screenRect);
    bool Acquire();
    bool Unacquire();
    void SetTouchpadEnabled(bool enabled);
    Rect<long> GetDefaultTouchpadRect();
    void SetTouchpadRect(Rect<long> rect);
    void SetScreenRect(Rect<int> rect);
    ~TouchpadManager();

private:
    Point<int> TouchpadToScreenCoords(long touchpadX, long touchpadY);
    HRESULT STDMETHODCALLTYPE OnSynDevicePacket(long seqNum) override;

    ISynAPI *m_api = NULL;
    ISynDevice *m_device = NULL;
    ISynPacket *m_packet = NULL;
    Rect<long> m_touchpadRect;
    Rect<int> m_screenRect;
    bool m_initialized = false;
    bool m_coinitialized = false;
    bool m_acquired = false;
};

#endif
