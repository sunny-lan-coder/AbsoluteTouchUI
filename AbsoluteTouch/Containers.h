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

template <typename T>
struct Point
{
    T x;
    T y;

    Point() = default;
    Point(T x, T y) : x(x), y(y) { }
};

#endif
