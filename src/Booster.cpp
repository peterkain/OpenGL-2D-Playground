#include "Booster.h"

#include "BasicRenderer.h"


Booster::Booster(const Direction& dir, const Vector3& pos, const Vector2& size, const Vector4& color,
                 const int& border)
    :   _rotation   {0, 0, 1}
    ,   _pos        {pos}
    ,   _color      {color}
    ,   _size       {size}
{
    switch(dir)
    {
    case Direction::UP:     _angle = 0;
                            _border = pos.y - border;
        break;
    case Direction::RIGHT:  _angle = 90;
                            _border = pos.x + border;
        break;
    case Direction::DOWN:   _angle = 180;
                            _border = pos.y + border;
        break;
    case Direction::LEFT:   _angle = 270;
                            _border = pos.x - border;
        break;
    }
}


bool Booster::collides(const Entity& o)
{
    if(_pos.x < o._pos.x + o._size.x && _pos.x + _size.x > o._pos.x && o._pos.y > _border) return true;
    else return false;
}


void Booster::render(const GLuint& program)
{
    BasicRenderer::draw_rect(program, {_pos.x, _pos.y}, _angle, _rotation, _size, _color);
}
