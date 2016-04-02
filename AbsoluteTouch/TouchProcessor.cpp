#include "TouchProcessor.h"

void TouchProcessor::SetWeight(float weight)
{
    m_weight = weight;
}

void TouchProcessor::TouchEnded()
{
    m_touching = false;
}

Point<long> TouchProcessor::Update(Point<long> rawPoint)
{
    if (m_weight == 0.0f || !m_touching) {
        m_average = rawPoint;
        m_touching = true;
    } else {
        m_average.x = (long)((1.0f - m_weight) * rawPoint.x + m_weight * m_average.x);
        m_average.y = (long)((1.0f - m_weight) * rawPoint.y + m_weight * m_average.y);
    }
    return m_average;
}
