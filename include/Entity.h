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

protected:
    float _angle;

    Vector4 _color;
    Vector3 _pos;
    Vector3 _rotation;
    Vector2 _size;
    Vector2 _vel;
};


#endif // ENTITY_H
