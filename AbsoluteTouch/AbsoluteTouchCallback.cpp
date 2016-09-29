#include "AbsoluteTouchCallback.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "InputHelper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"

void AbsoluteTouchCallback::SetTouchpadRect(Rect<long> touchpadRect)
{
    m_coordMapper.SetTouchpadRect(touchpadRect);
}

void AbsoluteTouchCallback::SetScreenRect(Rect<long> screenRect)
{
    m_coordMapper.SetScreenRect(screenRect);
}

void AbsoluteTouchCallback::SetSmoothingWeight(int weight)
{
    m_touchProcessor.SetWeight(weight);
}

void AbsoluteTouchCallback::SetSendClick(bool sendClick)
{
    m_sendClick = sendClick;
}

void AbsoluteTouchCallback::OnTouchStarted(Point<long> touchPt)
{
    Point<long> screenPt = TouchToScreen(touchPt);
    if (m_sendClick) {
        SendLeftDown(screenPt);
    } else {
        MoveCursor(screenPt);
    }
}

void AbsoluteTouchCallback::OnTouchMoved(Point<long> touchPt)
{
    MoveCursor(TouchToScreen(touchPt));
}

void AbsoluteTouchCallback::OnTouchEnded()
{
    if (m_sendClick) {
        SendLeftUp();
    }
    m_touchProcessor.TouchEnded();
}

Point<long> AbsoluteTouchCallback::TouchToScreen(Point<long> touchPt)
{
    Point<long> avgPt = m_touchProcessor.Update(touchPt);
    Point<long> screenPt = m_coordMapper.TouchToScreenCoords(avgPt);
    return screenPt;
}
