#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
#include "Vector2D.h"
#include "MapParser.h"
#include "GameObject.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 980

class Engine
{
public:
	static Engine* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Engine(); }
	inline SDL_Renderer* GetRenderer() { return _renderer; }
	GameMap* GetMap() { return _levelMap; }
	std::vector<GameObject*> GetGameObjects() { return _gameObjects; }

	inline bool IsRunning() { return _isRunning; }	

	void Init();
	void Clean();
	void Quit();

	void Render();
	void Update();
	void Events();	

private:
	Engine() {}
	bool _isRunning = false;

	static Engine* _instance;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	GameMap* _levelMap = nullptr;

	std::vector<GameObject*> _gameObjects;
};