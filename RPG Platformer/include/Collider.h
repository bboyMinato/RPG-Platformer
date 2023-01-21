#pragma once
#include "SDL.h"
#include "Camera.h"
#include "CollisionHandler.h"

class Collider
{
public:
	inline SDL_Rect GetBox() { return _box; }
	inline void SetBuffer(int x, int y, int w, int h)
	{
		_buffer = { x, y, w, h };
	}

	void Set(int x, int y, int w, int h)
	{
		_box = { x - _buffer.x, y - _buffer.y, w - _buffer.w, h - _buffer.h };
	}

	void Draw()
	{
		Vector2D cam = Camera::GetInstance()->GetPosition();

		SDL_Rect box = { (int)(_box.x - cam.X), (int)(_box.y - cam.Y), _box.w, _box.h };
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
	}

	bool CollidingWithMap()
	{
		return CollisionHandler::GetInstance()->MapCollision(_box);
	}

private:
	SDL_Rect _box;
	SDL_Rect _buffer;
};