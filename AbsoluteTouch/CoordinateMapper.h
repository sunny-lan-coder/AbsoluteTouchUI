#ifndef COORDINATE_MAPPER_H
#define COORDINATE_MAPPER_H

#include "Containers.h"

class CoordinateMapper
{
public:
    Point<int> TouchpadToScreenCoords(long touchpadX, long touchpadY);
    void SetTouchpadRect(Rect<long> rect);
    void SetScreenRect(Rect<int> rect);

private:
    Rect<long> m_touchpadRect;
    Rect<int> m_screenRect;
};

#endif
