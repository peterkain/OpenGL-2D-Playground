#pragma once
#include <cmath>


struct Vector2
{
    Vector2() {}
    Vector2(const float& x, const float& y)
        :   x   {x}
        ,   y   {y}
    {}


    static Vector2 distance(const Vector2& l, const Vector2& r)
    {
        return Vector2::normalize(Vector2{l.x - r.x, l.y - r.y});
    }


    static Vector2 normalize(const Vector2& o)
    {
        return Vector2{o.x / o.length(), o.y / o.length()};
    }


    float length() const
    {
        return std::sqrt(x * x + y * y);
    }


    float x, y;
};
