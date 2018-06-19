#pragma once

#pragma once

#include <array>
#include <GL/glew.h>
#include <cmath>

#include "math/Vector2.h"


struct Vector3
{
    Vector3()
    {}

    Vector3(const Vector3& v)
    {
        data = v.data;
    }

    Vector3(const GLfloat& x, const GLfloat& y, const GLfloat& z)
        : x{x}
        , y{y}
        , z{z}
    {                   }

    void normalize()
    {
        GLfloat l = length();
        x /= l;
        y /= l;
        z /= l;
    }

    Vector2 xy()
    {
        return Vector2(x, y);
    }

    GLfloat length()
    {
        return sqrt(x * x + y * y + z * z);
    }

    union
    {
        std::array<GLfloat, 3> data;

        struct
        {
            GLfloat x, y, z;
        };
    };


    Vector3& operator*(const Vector3& r)
    {
        x *= r.x;
        y *= r.y;
        z *= r.z;
        return *this;
    }

    friend Vector3& operator*(Vector3& l, const float& f)
    {
        l.x *= f;
        l.y *= f;
        l.z *= f;
        return l;
    }
};
