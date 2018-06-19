#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include "Entity.h"
#include "math/Vector2.h"
#include "types/IntTypes.h"

#include <array>

class Level;


enum Corner
{
    UP_LEFT,
    UP_RIGHT,
    UP_LEFT_PLUS_ONE,
    UP_RIGHT_MINUS_ONE,
    DOWN_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT_PLUS_ONE,
    DOWN_RIGHT_MINUS_ONE
};


class Player : public Entity
{
public:
    Player(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
           const Vector2& vel, const Vector4& color);

    void update() = delete;
    void update(bool l, bool r, bool jump, const Level& lvl);

    bool no_y_mod;

private:
    bool collision(const uintl8& tile);

private:
    uintf16 _jump_timer;
    bool _jump;
    bool _adjust_y;
    Vector2 _size2;
    std::array<bool, 8> _collision_corners;
};


#endif // PLAYER_H
