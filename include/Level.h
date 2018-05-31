#ifndef LEVEL_H
#define LEVEL_H

#pragma once

#include "types/StringTypes.h"
#include "types/IntTypes.h"
#include "Entity.h"
#include "Player.h"

#include <vector>
#include <memory>

#include <GL/glew.h>

class Level
{
public:
    Level();
    Level(conststr& path);
    ~Level();

    void render(const GLuint& program);
    void process_entities(const GLuint& program);
    void set_level(conststr& path);
    void set_height(const uintl16& h);
    uintl16 get_tile(const Vector2& pos) const;

private:
    std::vector<uintl16> _data;
    std::vector<Entity> _entities;
    std::unique_ptr<Player> _player;

    uintl32 _line_length;
    uintf64 _xoffset;
    uintf64 _yoffset;
    uintl16 _count_cols;

    static float X_SIZE;
    static float Y_SIZE;
};

#endif // LEVEL_H
