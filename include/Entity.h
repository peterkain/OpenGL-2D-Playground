#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>

#include "math/Vector4.h"
#include "math/Vector3.h"
#include "math/Vector2.h"


class Entity
{
public:
    Entity(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
           const Vector2& vel, const Vector4& color);

    void update();
    void render(const GLuint& program);
    bool collides(const Entity& o);

    Vector3 _pos;
    float _angle;
    Vector3 _rotation;
    Vector2 _size;
    Vector2 _vel;
    Vector4 _color;
};


#endif // ENTITY_H
