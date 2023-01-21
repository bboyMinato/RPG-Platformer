#pragma once
#include "SDL.h"

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.f;

class Timer
{
public:
	static Timer* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Timer(); }
	void Tick();
	inline float GetDeltaTime() { return _deltaTime; }

private:
	Timer() {}
	static Timer* _instance;
	float _deltaTime = 0.0f;
	float _lastTime = 0.0f;
};

