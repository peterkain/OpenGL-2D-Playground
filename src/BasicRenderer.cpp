#include "BasicRenderer.h"
#include "IntTypes.h"

#include <array>
#include <iostream>


// std::unique_ptr<GLuint> BasicRenderer::_vaos {new GLuint[2]};
// std::unique_ptr<GLuint> BasicRenderer::_vbos;
// std::unique_ptr<GLuint> BasicRenderer::_ebos;

GLuint BasicRenderer::_vao;
std::array<GLuint, 2> BasicRenderer::_buffers;


const std::array<GLfloat, 8> QUAD_VERTEX_POSITIONS = 
{
     0.5f,  0.5f,
     0.5f, -0.5f,
    -0.5f, -0.5f,
    -0.5f,  0.5f
};


const std::array<uintl8, 6> QUAD_VERTEX_ORDER =
{
    0, 1, 2,
    2, 3, 0
};


void BasicRenderer::init()
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(2, _buffers.data());

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[vertex_buffers::VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_VERTEX_POSITIONS), QUAD_VERTEX_POSITIONS.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[vertex_buffers::EBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_VERTEX_ORDER), QUAD_VERTEX_ORDER.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}


void BasicRenderer::draw_rect(const GLuint& program, const Vector2& pos, const Vector2& scale, const Vector2& rotation, const Vector4& color)
{
    glUseProgram(program);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
    glBindVertexArray(0);
}