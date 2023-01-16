#pragma once
#include "SDL.h"

class Input
{
public:
	static Input* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Input(); }

	bool GetKeyDown(SDL_Scancode key);
	void HandleEvents();

private:
	Input();
	static Input* _instance;

	void KeyUp();
	void KeyDown();

	const Uint8* _keystates;
};
