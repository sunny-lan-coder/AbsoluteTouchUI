#ifndef TOUCH_PROCESSOR_H
#define TOUCH_PROCESSOR_H

#include "Containers.h"

class TouchProcessor
{
public:
    void SetWeight(float weight);
    void TouchEnded();
    Point<long> Update(Point<long> rawPoint);

private:
    float m_weight = 0.0f;
    bool m_touching = false;
    Point<long> m_average;
};

#endif
