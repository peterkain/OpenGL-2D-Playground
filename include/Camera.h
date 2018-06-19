#ifndef CAMERA_H
#define CAMERA_H

#include "math/Matrix4x4.h"
#include "math/Vector2.h"

#include <memory>


class Camera
{
public:
    Camera();

    float SPEED;

    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void move_left_smooth(const Vector2& target);
    void move_right_smooth(const Vector2& target);
    void move_up_smooth(const Vector2& target);
    void move_down_smooth(const Vector2& target);

    void move_to(const Vector2& target);
    void move_to_smooth(const Vector2& target);

    void move(const Vector2& dir);

    Matrix4x4* get_view_matrix();

private:
    std::unique_ptr<Matrix4x4> _view;
};

#endif // CAMERA_H
