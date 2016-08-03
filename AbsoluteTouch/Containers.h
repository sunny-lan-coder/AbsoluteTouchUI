#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <ostream>

template <typename T>
struct Rect
{
    T x1;
    T y1;
    T x2;
    T y2;

    Rect() = default;
    Rect(T x1, T y1, T x2, T y2) : x1(x1), y1(y1), x2(x2), y2(y2) { }

    T width()
    {
        return x2 - x1;
    }

    T height()
    {
        return y2 - y1;
    }
};

template <typename T>
std::ostream & operator<<(std::ostream &os, Rect<T> rect)
{
    os << "{X1=" << rect.x1 << ", Y1=" << rect.y1;
    os << ", X2=" << rect.x2 << ", Y2=" << rect.y2 << "}";
    return os;
}

template <typename T>
struct Point
{
    T x;
    T y;

    Point() = default;
    Point(T x, T y) : x(x), y(y) { }
};

template <typename T>
std::ostream & operator<<(std::ostream &os, Point<T> point)
{
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

#endif
