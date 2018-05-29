#ifndef CAMERA_H
#define CAMERA_H

#include "math/Matrix4x4.h"

#include <memory>


class Camera
{
public:
    Camera();

    float SPEED;

    void move_left();
    void move_right();
    Matrix4x4* get_view_matrix();

private:
    std::unique_ptr<Matrix4x4> _view;
};

#endif // CAMERA_H
