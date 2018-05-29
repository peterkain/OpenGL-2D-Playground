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


void Entity::update()
{
    _pos.x += _vel.x;
    _pos.y += _vel.y;
}


void Entity::render(const GLuint& program)
{
    BasicRenderer::draw_rect(program, {_pos.x, _pos.y}, _angle, _rotation, _size, _color);
}
