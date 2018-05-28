#pragma once

#include <array>
#include <GL/glew.h>
#include <cmath>

struct Vector4
{
    Vector4()
    {}

    Vector4(const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w)
        :   x   {x}
        ,   y   {y}
        ,   z   {z}
        ,   w   {w}
    {                   }

    void normalize()
    {
        GLfloat l = length();
        x /= l;
        y /= l;
        z /= l;
    }

    GLfloat length()
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    union
    {
        std::array<GLfloat, 4> data;

        struct
        {
            GLfloat x, y, z, w;
        };
    };
};
