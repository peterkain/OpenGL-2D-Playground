#ifndef BOOSTER_H
#define BOOSTER_H

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

#include "Entity.h"


enum class Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};


class Booster
{
public:
    Booster(const Direction& dir, const Vector3& pos, const Vector2& size, const Vector4& color, const int& border);

    void render(const GLuint& program);

    bool collides(const Entity& o);

private:
    Vector3 _pos;
    Vector4 _color;
    GLfloat _angle;
    Vector3 _rotation;
    Vector2 _size;
    int _border;
};


#endif // BOOSTER_H
