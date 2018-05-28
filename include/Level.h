#pragma once

#include "types/StringTypes.h"
#include "types/IntTypes.h"

#include <vector>

#include <GL/glew.h>

class Level
{
public:
    Level();
    Level(conststr& path);
    ~Level();

    void render(const GLuint& program, const uintl16& w, const uintl16& h);
    void set_level(conststr& path);

private:
    std::vector<uintl16> _data;
    uintl32 _line_length;
    uintf64 _xoffset;
    uintf64 _yoffset;
};

