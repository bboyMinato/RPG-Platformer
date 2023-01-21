#pragma once
#include <string>
#include "SDL.h"

class Animation
{
public:
	Animation(bool repeat = true) : _repeat(repeat) { _isEnded = false; }

	virtual void Update() = 0;
	inline bool IsEnded() { return _isEnded; }

protected:
	bool _repeat = true;
	bool _isEnded = false;
	int _currentFrame = 0;
};