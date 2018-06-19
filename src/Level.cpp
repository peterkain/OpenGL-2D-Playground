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
    _entities.clear();
    _boosters.clear();
    _coins.clear();
    _player.release();

    std::ifstream file {path};
    std::string line;
    bool parse_lang {false};
    file >> _line_length >> X_SIZE >> Y_SIZE;
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
                if(type == "Player")
                {
                    float a;
                    Vector4 color;
                    Vector3 pos;
                    Vector3 rot;
                    Vector2 size;
                    Vector2 vel;

                    iss >> pos.x >> pos.y >> pos.z >> a >> rot.x >> rot.y >> rot.z >> size.x >> size.y >> vel.x >> vel.y >> color.x >> color.y >> color.z >> color.w;

                    pos.x *= X_SIZE;
                    pos.y *= Y_SIZE;

                    _player.reset(new Player{pos, a, rot, size, vel, color});
                }
                else if(type == "Coin")
                {
                    float a;
                    Vector4 color;
                    Vector3 pos;
                    Vector3 rot;
                    Vector2 size;
                    Vector2 vel;

                    iss >> pos.x >> pos.y >> pos.z >> a >> rot.x >> rot.y >> rot.z >> size.x >> size.y >> vel.x >> vel.y >> color.x >> color.y >> color.z >> color.w;

                    pos.x *= X_SIZE;
                    pos.y *= Y_SIZE;

                    _coins.emplace_back(Coin{pos, a, rot, size, vel, color});
                }
                else if(type == "Booster")
                {
                    int dir;
                    Vector3 pos;
                    Vector2 size;
                    Vector4 color;
                    int border;

                    iss >> dir >> pos.x >> pos.y >> pos.z >> size.x >> size.y >> color.x >> color.y >> color.z >> color.w >> border;

                    pos.x *= X_SIZE;
                    pos.y *= Y_SIZE;
                    border *= Y_SIZE;

                    _boosters.emplace_back(Booster{(Direction)dir, pos, size, color, border});
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

    for(uintf16 i {0}; i < _coins.size(); ++i)
    {
        if(_coins[i].collides(*_player.get()))
        {
            _coins.erase(_coins.begin());
        }
        _coins[i].update();
        _coins[i].render(program);
    }

    for(auto& e : _boosters)
    {
        if(e.collides(*_player.get()))
        {
            _player->no_y_mod = true;
            _player->_vel.y = -1.0f;
        } else _player->no_y_mod = false;
        e.render(program);
    }
}

