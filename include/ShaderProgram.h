#pragma once

#include "ShaderFile.h"

#include <vector>
#include <GL/glew.h>

class ShaderProgram
{
public:
    ShaderProgram();

    void create(const ShaderSource& source);

    GLuint id() const { return _program; }

private:
    std::vector<GLuint> _shaders;
    GLuint _program;
};

