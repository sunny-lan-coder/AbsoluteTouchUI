#include "CoordinateMapper.h"

void CoordinateMapper::SetTouchpadRect(Rect<long> rect)
{
    m_touchpadRect = rect;
}

void CoordinateMapper::SetScreenRect(Rect<int> rect)
{
    m_screenRect = rect;
}

Point<int> CoordinateMapper::TouchpadToScreenCoords(Point<long> touchpadCoords)
{
    long tpWidth = m_touchpadRect.x2 - m_touchpadRect.x1 + 1;
    long tpHeight = m_touchpadRect.y2 - m_touchpadRect.y1 + 1;
    int scWidth = m_screenRect.x2 - m_screenRect.x1 + 1;
    int scHeight = m_screenRect.y2 - m_screenRect.y1 + 1;
    long tpDeltaX = touchpadCoords.x - m_touchpadRect.x1;
    long tpDeltaY = touchpadCoords.y - m_touchpadRect.y1;
    int scDeltaX = (int)(tpDeltaX * scWidth / tpWidth);
    int scDeltaY = (int)(tpDeltaY * scHeight / tpHeight);
    int screenX = m_screenRect.x1 + scDeltaX;
    int screenY = m_screenRect.y1 + scDeltaY;
    return Point<int>(screenX * 65535 / scWidth, screenY * 65535 / scHeight);
}
