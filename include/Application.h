#pragma once

#include "types/IntTypes.h"
#include "Level.h"

#include <unordered_map>
#include <map>
#include <GL/glew.h>

class ShaderProgram;

class Application
{
public:
    Application();

    void init();
    void render();
    void quit();

private:
    void init_shaders();
    void load_levels();

private:
    std::unordered_map<std::string, GLuint> _programs;
    std::unordered_map<uintl16, Level> _levels;

    uintl16 _curr_lvl;
};

