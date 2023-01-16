#include "../include/Camera.h"
Camera* Camera::_instance = nullptr;

void Camera::Update(float dt)
{
	if (_target == nullptr)
		std::cout << "_target not initialized!" << std::endl;

	else
	{
		_viewBox.x = _target->X - SCREEN_WIDTH / 2;
		_viewBox.y = _target->Y - SCREEN_HEIGHT / 2;

		if (_viewBox.x < 0)
			_viewBox.x = 0;

		if (_viewBox.y < 0)
			_viewBox.y = 0;

		if (_viewBox.x > (2 * SCREEN_WIDTH - _viewBox.w))
			_viewBox.x = (2 * SCREEN_WIDTH - _viewBox.w);

		if (_viewBox.y > (SCREEN_HEIGHT - _viewBox.h))
			_viewBox.y = (SCREEN_HEIGHT - _viewBox.h);

		_position = Vector2D(_viewBox.x, _viewBox.y);
	}
}