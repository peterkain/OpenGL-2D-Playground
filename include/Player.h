#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include "math/Vector2.h"


class Player : public Entity
{
public:
    Player(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
           const Vector2& vel, const Vector4& color);

    void update() = delete;
    void update(bool l, bool r);

private:

};


#endif // PLAYER_H
