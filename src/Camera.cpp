#include "Camera.h"


Camera::Camera()
{
    SPEED = 0.25f;
    _view = std::unique_ptr<Matrix4x4>(new Matrix4x4(1.0f));
}


void Camera::move_left()
{
    _view.get()->translate_by(SPEED, 0.0f, 0.0f);
}


void Camera::move_right()
{
    _view.get()->translate_by(-SPEED, 0.0f, 0.0f);
}


Matrix4x4* Camera::get_view_matrix()
{
    return _view.get();
}
