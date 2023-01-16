#pragma once
#include <string>
#include "SDL.h"

class Animation
{
public:
	Animation() {}

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_RendererFlip _flip = SDL_FLIP_NONE;

private:
	int _spriteRow = 0;
	int _spriteFrame = 0;
	int _animSpeed = 60;
	int _frameCount = 0;
	std::string _textureID;
};