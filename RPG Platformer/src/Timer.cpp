#include "..\include\Timer.h"
Timer* Timer::_instance = nullptr;

void Timer::Tick()
{
    _deltaTime = (SDL_GetTicks() - _lastTime) * (TARGET_FPS / 1000.0f);

    if (_deltaTime > TARGET_DELTATIME)
        _deltaTime = 1.5f;

    _lastTime = SDL_GetTicks();
}
