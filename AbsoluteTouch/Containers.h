#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <ostream>

template <typename T>
struct Rect
{
    T x;
    T y;
    T width;
    T height;

    Rect() = default;
    Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) { }
};

template <typename T>
std::ostream & operator<<(std::ostream &os, Rect<T> rect)
{
    os << "{X=" << rect.x << ", Y=" << rect.y;
    os << ", W=" << rect.width << ", H=" << rect.height << "}";
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
    os << "{X=" << point.x << ", Y=" << point.y << "}";
    return os;
}

#endif
