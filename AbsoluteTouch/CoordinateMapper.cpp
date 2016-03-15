#include "CoordinateMapper.h"

void CoordinateMapper::SetTouchpadRect(Rect<long> rect)
{
    m_touchpadRect = rect;
}

void CoordinateMapper::SetScreenRect(Rect<int> rect)
{
    m_screenRect = rect;
}

Point<int> CoordinateMapper::TouchpadToScreenCoords(long touchpadX, long touchpadY)
{
    long tpDeltaX = touchpadX - m_touchpadRect.x;
    long tpDeltaY = touchpadY - m_touchpadRect.y;
    int scDeltaX = (int)(tpDeltaX * m_screenRect.width / m_touchpadRect.width);
    int scDeltaY = (int)((m_touchpadRect.height - tpDeltaY) * m_screenRect.height / m_touchpadRect.height);
    int screenX = m_screenRect.x + scDeltaX;
    int screenY = m_screenRect.y + scDeltaY;
    return Point<int>(screenX, screenY);
}
