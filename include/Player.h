#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include "Entity.h"
#include "math/Vector2.h"
#include "types/IntTypes.h"


class Level;


class Player : public Entity
{
public:
    Player(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
           const Vector2& vel, const Vector4& color);

    void update() = delete;
    void update(bool l, bool r, bool jump, const Level& lvl);

private:
    bool collision(const uintl8& tile);

private:
    uintf16 _jump_timer;
    float _start;
    bool _jump;
};


#endif // PLAYER_H
