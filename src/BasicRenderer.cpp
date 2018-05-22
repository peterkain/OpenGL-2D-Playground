#include "BasicRenderer.h"
#include "types/IntTypes.h"
#include "ShaderProgram.h"
#include "math/Matrix4x4.h"

#include <array>
#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// std::unique_ptr<GLuint> BasicRenderer::_vaos {new GLuint[2]};
// std::unique_ptr<GLuint> BasicRenderer::_vbos;
// std::unique_ptr<GLuint> BasicRenderer::_ebos;

GLuint BasicRenderer::_vao;
std::array<GLuint, 2> BasicRenderer::_buffers;
Matrix4x4 BasicRenderer::_projection = Matrix::orthographic(0, 960, 0, 540, -5, 5);


const std::array<GLfloat, 8> QUAD_VERTEX_POSITIONS = 
{
     1.0f,  1.0f,
     1.0f, -1.0f,
    -1.0f, -1.0f,
    -1.0f,  1.0f
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

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void BasicRenderer::draw_rect(const GLuint& program, const Vector2& pos, const GLfloat& angle, const Vector2& rotation, const Vector2& scale, const Vector4& color)
{
    glUseProgram(program);

    Matrix4x4 model {1.0f};
    model.translate_by(pos.x, pos.y, 0.0f);
    model.rotate_by(angle, rotation.x, rotation.y, 0);
    model.scale_by(scale.x, scale.y, 1);


    Matrix4x4 view {1.0f};
    view.translate_by(0.0f, 0.0f, 0.0f);

    Matrix4x4 mvp {1.0f};
    mvp *= _projection;
    mvp *= view;
    mvp *= model;

    ShaderProgram::set_vec4(program, "u_color", color);
    ShaderProgram::set_mat4(program, "u_mvp", mvp);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
    glBindVertexArray(0);
}