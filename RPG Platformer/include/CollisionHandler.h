#pragma once
#include "SDL.h"
#include <vector>
#include "../include/TileLayer.h"
#include "../include/GameMap.h"
#include "../include/Engine.h"

class CollisionHandler
{
public:
	inline static CollisionHandler* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new CollisionHandler(); }

	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);

private:
	CollisionHandler();

	static CollisionHandler* _instance;
	TileMap _collisionTileMap;
	TileLayer* _collisionLayer = nullptr;
};

