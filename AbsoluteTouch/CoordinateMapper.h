#ifndef COORDINATE_MAPPER_H
#define COORDINATE_MAPPER_H

#include "Containers.h"

class CoordinateMapper
{
public:
    Point<int> TouchpadToScreenCoords(Point<long> touchpadCoords);
    void SetTouchpadRect(Rect<long> rect);
    void SetScreenRect(Rect<int> rect);

private:
    Rect<long> m_touchpadRect;
    Rect<int> m_screenRect;
};

#endif
