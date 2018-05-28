#include "Level.h"
#include "BasicRenderer.h"

#include <fstream>
#include <iterator>
#include <iostream>


Level::Level()
    :   _line_length    {0}
{
}


Level::Level(conststr& path)
    :   _line_length    {0}
{
    set_level(path);
}


Level::~Level()
{
}


void Level::set_level(conststr& path)
{
    std::ifstream file {path};
    file >> _line_length;
    std::istream_iterator<uintl16> start{file}, end;
    _data.insert(_data.end(), start, end);
}


void Level::render(const GLuint& program, const uintl16& w, const uintl16& h)
{
    uintf32 line {0};
    _xoffset = 0;
    _yoffset = 0;
    for(const auto& e : _data)
    {
        if(e == 1)  BasicRenderer::draw_rect(program, {(float)_xoffset, (float)_yoffset}, 0.0f, {0.0f, 0.0f, 0.0f},
                                             {16, 16}, {0.5f, 1.0f, 0.5f, 1.0f});
        ++line;
        _xoffset += 32;
        if(line == _line_length)
        {
            std::cout << '\n';
            _yoffset += 32;
            _xoffset = 0;
            line = 0;
        }
    }
}
