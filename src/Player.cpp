#include "Player.h"
#include "Input.h"
#include "Level.h"

#include <iostream>


Player::Player(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
               const Vector2& vel, const Vector4& color)
    :   Entity(pos, angle, rotation, size, vel, color)
    ,   _jump_timer {0}
    ,   _jump       {false}
    ,   _adjust_y   {true}
    ,   _size2      {size.x * 2, size.y * 2}
    ,   no_y_mod    {false}
{
    Input::camera.move_to({_pos.x, _pos.y / 2});
    Input::camera.SPEED = vel.x;
}


bool Player::collision(const uintl8& tile)
{
    if(tile == 1 || tile == 2) return true;
    else return false;
}


void Player::update(bool l, bool r, bool jump, const Level& lvl)
{
    static float JUMP_SPEED = -0.3f;
    static float FALL_SPEED = 0.45f;
    static float Y_MODIFIER = FALL_SPEED;
    static float jump_height = 0.0f;

    float prev_x = _pos.x;

    if(l)       _pos.x -= _vel.x;
    else if(r)  _pos.x += _vel.x;


    _collision_corners[UP_LEFT] = collision(lvl.get_tile({_pos.x, _pos.y}));
    _collision_corners[UP_RIGHT] = collision(lvl.get_tile({_pos.x + _size2.x, _pos.y}));
    _collision_corners[UP_LEFT_PLUS_ONE] = collision(lvl.get_tile({_pos.x + 1, _pos.y}));
    _collision_corners[UP_RIGHT_MINUS_ONE] = collision(lvl.get_tile({_pos.x + _size2.x - 1, _pos.y}));
    _collision_corners[DOWN_LEFT] = collision(lvl.get_tile({_pos.x, _pos.y + _size2.y}));
    _collision_corners[DOWN_RIGHT] = collision(lvl.get_tile({_pos.x + _size2.x, _pos.y + _size2.y}));
    _collision_corners[DOWN_LEFT_PLUS_ONE] = collision(lvl.get_tile({_pos.x + 1, _pos.y + _size2.y}));
    _collision_corners[DOWN_RIGHT_MINUS_ONE] = collision(lvl.get_tile({_pos.x + _size2.x - 1, _pos.y + _size2.y}));

    //for(const auto& e : _collision_corners) std::cout << e << " ";
    //std::cout << '\n';

    if(l)
    {
        if(_collision_corners[UP_LEFT])     _pos.x = prev_x;
        else Input::camera.move_left();
    }


    if(r)
    {
        if(_collision_corners[UP_RIGHT])    _pos.x = prev_x;
        else Input::camera.move_right();
    }


    if(jump && (_collision_corners[DOWN_LEFT_PLUS_ONE] || _collision_corners[DOWN_RIGHT_MINUS_ONE]))
    {
        _jump = true;
        jump_height = _pos.y - 150.0f;
        Y_MODIFIER = JUMP_SPEED;
    }

    if(_jump)
    {
        _pos.y += Y_MODIFIER;
        if(_pos.y < jump_height || (_collision_corners[UP_LEFT_PLUS_ONE] || _collision_corners[UP_RIGHT_MINUS_ONE]))
        {
            _jump = false;
            _adjust_y = true;
            Y_MODIFIER = FALL_SPEED;
        }

        //if(_collision_corners[DOWN_LEFT] || _collision_corners[DOWN_RIGHT]) _pos.x = prev_x;
    }

    if(_adjust_y)
    {
        Input::camera.move_to(_pos.xy());
    }

    if(!_collision_corners[DOWN_LEFT] && !_collision_corners[DOWN_RIGHT] && ! no_y_mod)   _pos.y += Y_MODIFIER;
    else if(no_y_mod)   _pos.y += _vel.y;
}
