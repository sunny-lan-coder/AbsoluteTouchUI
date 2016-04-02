#ifndef TOUCHPAD_MANAGER_H
#define TOUCHPAD_MANAGER_H

#include "Containers.h"
#include "Include/SynKit.h"

struct TouchEvent
{
    Point<long> point;
    bool touching;
};

typedef void (*TouchCallback)(TouchEvent e);

class TouchpadManager : private _ISynDeviceEvents
{
public:
    bool Initialize();
    bool Acquire();
    void Unacquire();
    void SetTouchCallback(TouchCallback callback);
    bool IsTouchpadEnabled();
    void SetTouchpadEnabled(bool enabled);
    Rect<long> GetDefaultTouchpadRect();
    ~TouchpadManager();

private:
    Point<long> NormalizeCoordinates(long x, long y);
    HRESULT STDMETHODCALLTYPE OnSynDevicePacket(long seqNum) override;

    ISynAPI *m_api = nullptr;
    ISynDevice *m_device = nullptr;
    ISynPacket *m_packet = nullptr;
    bool m_initialized = false;
    bool m_coinitialized = false;
    bool m_acquired = false;
    TouchCallback m_callback = nullptr;
    Rect<long> m_bounds;
};

#endif
