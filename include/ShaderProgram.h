#pragma once

#include "ShaderFile.h"

#include <vector>
#include <GL/glew.h>


#define set_vec4_bind(x, y, z) glUseProgram(x); set_vec4(x, y, z); glUseProgram(0);


struct Vector4;
struct Matrix4x4;

class ShaderProgram
{
public:
    ShaderProgram();

    void create(const ShaderSource& source);

    GLuint id() const { return _program; }

    static void set_vec4(const GLuint& program, conststr& name, const Vector4& v);
    static void set_mat4(const GLuint& program, conststr& name, const Matrix4x4& v);

private:
    std::vector<GLuint> _shaders;
    GLuint _program;
};

