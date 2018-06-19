#ifndef COIN_H
#define COIN_H

#pragma once

#include "Entity.h"


class Coin : public Entity
{
public:
    Coin(const Vector3& pos, const GLfloat& angle, const Vector3& rotation, const Vector2& size,
               const Vector2& vel, const Vector4& color);
};


#endif // COIN_H
