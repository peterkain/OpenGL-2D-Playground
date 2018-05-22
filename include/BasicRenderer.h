#pragma once

#include "math/Vector2.h"
#include "math/Vector4.h"
#include "types/IntTypes.h"

#include <GL/glew.h>
#include <memory>

namespace vertex_buffers
{
    constexpr uintl8 VBO = 0;
    constexpr uintl8 EBO = 1;
}

struct Matrix4x4;

class BasicRenderer
{
public:
    BasicRenderer() = delete;

    static void init();
    static void draw_rect(const GLuint& program, const Vector2& pos, const GLfloat& angle, const Vector2& rotation, const Vector2& scale, const Vector4& color);

private:
    // static std::unique_ptr<GLuint> _vaos;

    static GLuint _vao;
    static std::array<GLuint, 2> _buffers;

    static Matrix4x4 _projection;
};