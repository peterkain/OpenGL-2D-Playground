#include "Player.h"


Player::Player(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
               const Vector2& vel, const Vector4& color)
    :   Entity(pos, angle, rotation, size, vel, color)
{

}

void Player::update(bool l, bool r)
{
    if(l)       _pos.x -= _vel.x;
    else if(r)  _pos.x += _vel.x;
}
