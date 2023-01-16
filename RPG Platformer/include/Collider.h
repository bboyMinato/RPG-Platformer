#pragma once
#include "SDL.h"

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

private:
	SDL_Rect _box;
	SDL_Rect _buffer;
};