#include "Level.h"
#include "BasicRenderer.h"
#include "Player.h"
#include "Input.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>


float Level::X_SIZE = 64.0f;
float Level::Y_SIZE;


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
    std::string line;
    bool parse_lang {false};
    file >> _line_length;
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

                    _player.reset(new Player{pos, a, rot, size, vel, color});
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


uintl16 Level::get_tile(const Vector2& pos) const
{
    intl16 xoffset = pos.x / X_SIZE;
    intl16 yoffset = pos.y / Y_SIZE;

    return _data[xoffset + yoffset * _line_length];
}


void Level::set_height(const uintl16& h)
{
    Y_SIZE = h / _count_cols;
}


void Level::render(const GLuint& program)
{
    uintf32 line {0};
    _xoffset = 0;
    _yoffset = 0;

    for(const auto& e : _data)
    {
        if(e)  BasicRenderer::draw_rect(program, {(float)_xoffset, (float)_yoffset}, 0.0f, {0.0f, 0.0f, 0.0f},
                                        {X_SIZE / 2, Y_SIZE / 2}, {0.5f, 1.0f, 0.5f, 1.0f});
        ++line;
        _xoffset += X_SIZE;
        if(line == _line_length)
        {
            _yoffset += Y_SIZE;
            _xoffset = 0;
            line = 0;
        }
    }
}


void Level::process_entities(const GLuint& program)
{
    _player->update(Input::keys()[GLFW_KEY_A], Input::keys()[GLFW_KEY_D], Input::keys()[GLFW_KEY_SPACE], *this);
    _player->render(program);
    for(auto& e : _entities)
    {
        e.update();
        e.render(program);
    }
}

