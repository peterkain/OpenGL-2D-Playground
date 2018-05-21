#pragma once

#include "IntTypes.h"

#include <unordered_map>
#include <GL/glew.h>

class ShaderProgram;

class Application
{
public:
    Application() = delete;

    static void init();
    static void render();
    static void quit();

private:
    static std::unordered_map<std::string, GLuint> _programs;
};

