#include "Level.h"
#include "BasicRenderer.h"
#include "Player.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>


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
    //std::istream_iterator<uintl16> start{file}, end;
    //_data.insert(_data.end(), start, end);

    std::string line;
    bool parse_lang {false};
    while(std::getline(file, line))
    {
        std::istringstream iss {line};
        if(parse_lang)
        {
            std::string command;
            iss >> command;

            if(command == "end")
            {
                parse_lang = false;
                continue;
            }
            else if(command == "plc")
            {
                std::string type;
                iss >> type;
                if(type == "PL")
                {
                    float a;
                    Vector4 color;
                    Vector3 pos;
                    Vector3 rot;
                    Vector2 size;
                    Vector2 vel;

                    iss >> pos.x >> pos.y >> a >> rot.x >> rot.y >> rot.z >> size.x >> size.y >> vel.x >> vel.y >> color.x >> color.y >> color.z >> color.w;

                    pos.x *= 64;
                    pos.y *= 33.7;

                    _entities.emplace_back(Player{pos, a, rot, size, vel, color});
                }
            }
        }
        if(line != "beg")
        {
            std::copy(std::istream_iterator<uintl16>{iss},
                      std::istream_iterator<uintl16>{},
                      std::back_inserter(_data));
        }
        else
        {
            parse_lang = true;
        }
    }

    _count_cols = _data.size() / _line_length;
}


void Level::render(const GLuint& program, const uintl16& w, const uintl16& h)
{
    uintf32 line {0};
    _xoffset = 0;
    _yoffset = 0;
    for(const auto& e : _data)
    {
        if(e)  BasicRenderer::draw_rect(program, {(float)_xoffset, (float)_yoffset}, 0.0f, {0.0f, 0.0f, 0.0f},
                                        {32, (float)h / _count_cols / 2.0f}, {0.5f, 1.0f, 0.5f, 1.0f});
        ++line;
        _xoffset += 64;
        if(line == _line_length)
        {
            _yoffset += h / _count_cols;
            _xoffset = 0;
            line = 0;
        }
    }
}


void Level::render_entities(const GLuint& program)
{
    for(auto& e : _entities)
    {
        e.render(program);
    }
}
