#pragma once

#include "Vector2.h"
#include "Vector4.h"
#include "IntTypes.h"

#include <GL/glew.h>
#include <memory>

namespace vertex_buffers
{
    constexpr uintl8 VBO = 0;
    constexpr uintl8 EBO = 1;
}

class BasicRenderer
{
public:
    BasicRenderer() = delete;

    static void init();
    static void draw_rect(const GLuint& program, const Vector2& pos, const Vector2& scale, const Vector2& rotation, const Vector4& color);

private:
    // static std::unique_ptr<GLuint> _vaos;

    static GLuint _vao;
    static std::array<GLuint, 2> _buffers;
};