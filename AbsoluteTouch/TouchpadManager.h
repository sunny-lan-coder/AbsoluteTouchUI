#ifndef TOUCHPAD_MANAGER_H
#define TOUCHPAD_MANAGER_H

#include "Containers.h"
#include "Include/SynKit.h"

typedef void (*TouchCallback)(long touchpadX, long touchpadY);

class TouchpadManager : private _ISynDeviceEvents
{
public:
    bool Initialize();
    bool Acquire();
    void Unacquire();
    void SetTouchCallback(TouchCallback callback);
    void SetTouchpadEnabled(bool enabled);
    Rect<long> GetDefaultTouchpadRect();
    ~TouchpadManager();

private:
    HRESULT STDMETHODCALLTYPE OnSynDevicePacket(long seqNum) override;

    ISynAPI *m_api = nullptr;
    ISynDevice *m_device = nullptr;
    ISynPacket *m_packet = nullptr;
    bool m_initialized = false;
    bool m_coinitialized = false;
    bool m_acquired = false;
    TouchCallback m_callback = nullptr;
};

#endif
