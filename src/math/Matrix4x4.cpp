#include "math/Matrix4x4.h"
#include "math/Vector3.h"


namespace Matrix
{
    Matrix4x4 translation(const GLfloat& dx, const GLfloat& dy, const GLfloat& dz)
    {
        return  {1, 0, 0, dx,
                 0, 1, 0, dy,
                 0, 0, 1, dz,
                 0, 0, 0, 1};
    }


    Matrix4x4 rotation(const GLfloat& a, const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        GLfloat c { cos(a) };
        GLfloat s { sin(a) };
        GLfloat t {1.0f - c};
        
        return  {x * x * t + c,     y * x * t + z * s, x * z * t - y * s, 0,
                 x * y * t - z * s, y * y * t + c,     y * z * t + x * s, 0,
                 x * z * t + y * s, y * z * t - x * s, z * z * t + c,     0,
                 0,                 0,                 0,                 1};
    }


    Matrix4x4 scale(const GLfloat& scale_x, const GLfloat& scale_y, const GLfloat& scale_z)
    {
        return  {scale_x, 0,       0,       0,
                 0,       scale_y, 0,       0,
                 0,       0,       scale_z, 0,
                 0,       0,       0,       1};
    }


    Matrix4x4 orthographic(const GLfloat& l, const GLfloat& r, const GLfloat& t, const GLfloat& b, const GLfloat& n, const GLfloat& f)
    {
        return  {2 / (r - l), 0,           0,           -(r + l) / (r - l),
                 0,           2 / (t - b), 0,           -(t + b) / (t - b),
                 0,           0,          -2 / (f - n), -(f + n) / (f - n),
                 0,           0,           0,            1};
    }
}


Matrix4x4::Matrix4x4()
{
    data.fill(1.0f);
}


Matrix4x4::Matrix4x4(const GLfloat& diagonal)
{
    data.fill(0.0f);
    x11 = x22 = x33 = x44 = diagonal;
}


Matrix4x4::Matrix4x4(const std::array<GLfloat, 16>& data)
    : data{data}
{                       }


Matrix4x4::Matrix4x4(const GLfloat& x11, const GLfloat& x12, const GLfloat& x13, const GLfloat& x14,
                     const GLfloat& x21, const GLfloat& x22, const GLfloat& x23, const GLfloat& x24,
                     const GLfloat& x31, const GLfloat& x32, const GLfloat& x33, const GLfloat& x34,
                     const GLfloat& x41, const GLfloat& x42, const GLfloat& x43, const GLfloat& x44)
    :   x11 {x11},  x12 {x12},  x13 {x13},  x14 {x14}
    ,   x21 {x21},  x22 {x22},  x23 {x23},  x24 {x24}
    ,   x31 {x31},  x32 {x32},  x33 {x33},  x34 {x34}
    ,   x41 {x41},  x42 {x42},  x43 {x43},  x44 {x44}
{                                                       }


Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
    data = m.data;
}


Matrix4x4::Matrix4x4(Matrix4x4&& m)
{
    data = std::move(m.data);
}


void Matrix4x4::translate_by(const GLfloat& dx, const GLfloat& dy, const GLfloat& dz)
{
    *this *= Matrix::translation(dx, dy, dz);
}


void Matrix4x4::rotate_by(const GLfloat& angle, const GLfloat& x, const GLfloat& y, const GLfloat& z)
{
    *this *= Matrix::rotation(angle, x, y, z);
}


void Matrix4x4::scale_by(const GLfloat& scale_x, const GLfloat& scale_y, const GLfloat& scale_z)
{
    *this *= Matrix::scale(scale_x, scale_y, scale_z);
}


void Matrix4x4::transpose()
{
    std::swap(x12, x21);
    std::swap(x13, x31);
    std::swap(x14, x41);

    std::swap(x23, x32);
    std::swap(x24, x42);

    std::swap(x34, x43);
}