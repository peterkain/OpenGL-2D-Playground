#pragma once

struct Vector2
{
    Vector2() {}
    Vector2(const float& x, const float& y)
        :   x   {x}
        ,   y   {y}
    {}

    float x, y;
};
