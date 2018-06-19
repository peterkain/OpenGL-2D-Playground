#include "Camera.h"


Camera::Camera()
{
    SPEED = 0.25f;
    _view = std::unique_ptr<Matrix4x4>(new Matrix4x4(1.0f));
}


void Camera::move_left()
{
    _view.get()->translate_by(SPEED, 0.0f, 0.0f);
    std::cout << *_view.get() << std::endl;
}


void Camera::move_left_smooth(const Vector2& target)
{

}


void Camera::move_right()
{
    _view.get()->translate_by(-SPEED, 0.0f, 0.0f);
}


void Camera::move_right_smooth(const Vector2& target)
{

}


void Camera::move_up()
{
    _view.get()->translate_by(0.0f, SPEED, 0.0f);
}


void Camera::move_up_smooth(const Vector2& target)
{

}


void Camera::move_down()
{
    _view.get()->translate_by(0.0f, -SPEED, 0.0f);
}


void Camera::move_down_smooth(const Vector2& target)
{

}


void Camera::move_to(const Vector2& target)
{
    *_view.get() = Matrix::translation(-target.x + 480, (-target.y + 240) / 1.5f, 0.0f);
}


void Camera::move_to_smooth(const Vector2& target)
{
    Vector2 pos {_view.get()->x14, _view.get()->x24};
    Vector2 dist = Vector2::distance(pos, target);

    _view.get()->translate_by(dist.x, dist.y, 0.0f);
}


void Camera::move(const Vector2& dir)
{

    *_view.get() = Matrix::translation(-dir.x, -dir.y, 0.0f);
}


Matrix4x4* Camera::get_view_matrix()
{
    return _view.get();
}
