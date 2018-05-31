#include "Player.h"
#include "Input.h"
#include "Level.h"

#include <iostream>


Player::Player(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
               const Vector2& vel, const Vector4& color)
    :   Entity(pos, angle, rotation, size, vel, color)
    ,   _jump_timer {0}
    ,   _start      {pos.y}
    ,   _jump       {false}
{

}


bool Player::collision(const uintl8& tile)
{
    if(tile == 1) return true;
    else return false;
}


void Player::update(bool l, bool r, bool jump, const Level& lvl)
{
    static float JUMP_SPEED = -0.7f;
    static float FALL_SPEED = 0.3f;
    static float Y_MODIFIER = FALL_SPEED;

    Vector3 prev_pos = _pos;

    if(l)           _pos.x -= _vel.x;
    else if(r)      _pos.x += _vel.x;

    if(collision(lvl.get_tile({_pos.x, _pos.y})))    _pos = prev_pos;

    if(jump && !_jump_timer)
    {
        _jump = true;
        _jump_timer = 900;
        Y_MODIFIER = JUMP_SPEED;
    }

    if(_jump)
    {
        static float jump_height = _pos.y - 100.0f;
        _pos.y += Y_MODIFIER;
        if(_pos.y < jump_height || collision(lvl.get_tile({_pos.x, _pos.y})))
        {
            _jump = false;
            Y_MODIFIER = FALL_SPEED;
        }
    }
    else
    {
        if(_pos.y < _start) _pos.y += Y_MODIFIER;
    }

    if(_jump_timer > 0) --_jump_timer;
}
