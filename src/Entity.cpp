#include "Entity.h"

#include "BasicRenderer.h"


Entity::Entity(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
               const Vector2& vel, const Vector4& color)
    :   _pos        {pos}
    ,   _angle      {angle}
    ,   _rotation   {rotation}
    ,   _size       {size}
    ,   _vel        {vel}
    ,   _color      {color}
{
}


bool Entity::collides(const Entity& o)
{
    if(_pos.x < o._pos.x + o._size.x && _pos.x + _size.x > o._pos.x &&
       _pos.y < o._pos.y + o._size.y && _pos.y + _size.y > o._pos.y)
       return true;
    else return false;
}


void Entity::update()
{
    _pos.x += _vel.x;
    _pos.y += _vel.y;
}


void Entity::render(const GLuint& program)
{
    BasicRenderer::draw_rect(program, {_pos.x, _pos.y}, _angle, _rotation, _size, _color);
}
