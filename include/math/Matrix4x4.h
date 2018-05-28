#pragma once

#include "types/IntTypes.h"
#include "math/Vector4.h"

#include <array>
#include <GL/glew.h>
#include <iostream>
#include <cstring>


struct Matrix4x4;

namespace Matrix
{
    extern Matrix4x4 translation(const GLfloat& dx, const GLfloat& dy, const GLfloat& dz);
    extern Matrix4x4 rotation(const GLfloat& angle, const GLfloat& x, const GLfloat& y, const GLfloat& z);
    extern Matrix4x4 scale(const GLfloat& scale_x, const GLfloat& scale_y, const GLfloat& scale_z);

    extern Matrix4x4 orthographic(const GLfloat& l, const GLfloat& r, const GLfloat& t, const GLfloat& b, const GLfloat& f, const GLfloat& n);
}


struct Matrix4x4
{
    Matrix4x4();
    Matrix4x4(const GLfloat& diagonal);
    Matrix4x4(const std::array<GLfloat, 16>& data);
    Matrix4x4(const GLfloat& x11, const GLfloat& x12, const GLfloat& x13, const GLfloat& x14,
              const GLfloat& x21, const GLfloat& x22, const GLfloat& x23, const GLfloat& x24,
              const GLfloat& x31, const GLfloat& x32, const GLfloat& x33, const GLfloat& x34,
              const GLfloat& x41, const GLfloat& x42, const GLfloat& x43, const GLfloat& x44);

    Matrix4x4(const Matrix4x4& m);
    Matrix4x4(Matrix4x4&& m);

    union
    {
        std::array<GLfloat, 16> data;

        struct
        {
            GLfloat x11, x21, x31, x41,
                    x12, x22, x32, x42,
                    x13, x23, x33, x43,
                    x14, x24, x34, x44;
        };

        std::array<Vector4, 4> grid;
    };


    void translate_by(const GLfloat& dx, const GLfloat& dy, const GLfloat& dz);
    void rotate_by(const GLfloat& angle, const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void scale_by(const GLfloat& scale_x, const GLfloat& scale_y, const GLfloat& scale_z);
    void transpose();


    void operator*=(const Matrix4x4& r)
    {
        *this = *this * r;
    }

    void operator*=(const Vector4& r)
    {
        *this = *this * r;
    }

    void operator=(const Matrix4x4& m)
    {
        data = m.data;
    }

    void operator=(float* arr)
    {
        GLfloat* p = &data[0];
        std::memcpy(p, arr, sizeof(arr) * 16);
    }

    Matrix4x4 operator*(const float& f)
    {
        for(auto& d : data) d *= f;
        return *this;
    }

    friend Matrix4x4 operator*(Matrix4x4& m, const float& f)
    {
        for(auto& d : m.data) d *= f;
        return m;
    }

    friend Matrix4x4 operator*(const Matrix4x4& l, const Matrix4x4& r)
    {
        Matrix4x4 res;
        for(intf8 i{0}; i < 4; ++i)
        {
            for(intf8 j{0}; j < 4; ++j)
            {
                float sum{0};
                for(intf8 k{0}; k < 4; ++k)
                {
                    sum += l.data[i + k * 4] * r.data[k + j * 4];
                }
                res.data[i + j * 4] = sum;
            }
        }
        return res;
    }

    friend Matrix4x4 operator*(const Matrix4x4& l, const Vector4& r)
    {
        Matrix4x4 res;
        for(intf8 i{0}; i < 4; ++i)
        {
            for(intf8 j{0}; j < 4; ++j)
            {
                float sum{0};
                uintl16 row_offset = i * 4;
                for(intf8 k{0}; k < 4; ++k)
                {
                    sum += l.data[row_offset + k] * r.data[k];
                }
                res.data[row_offset + j] = sum;
            }
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& s, const Matrix4x4& m)
    {
        for(intf8 i{0}; i < 16; ++i)
        {
            if(i % 4 == 0)    s << '\n';
            s << m.data[i] << ' ';
        }
        return s;
    }
};
