#ifndef CONTAINERS_H
#define CONTAINERS_H

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

template <typename R>
struct Point
{
    R x;
    R y;

    Point() = default;
    Point(R x, R y) : x(x), y(y) { }
};

#endif
