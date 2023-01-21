#pragma once
#include <string>
#include "SDL.h"
#include "Animation.h"

class SpriteAnimation : public Animation
{
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);
	
	inline int GetCurrentFrame() { return _currentFrame; }
	inline int GetCurrentSpriteRow() { return _spriteRow; }

	void SetSpriteRow(int row) { _spriteRow = row; }
	void IncreaseSpriteRow() { _spriteRow++; }
	void DecreaseSpriteRow() { _spriteRow--; }

private:
	int _animSpeed;
	int _spriteRow;
	int _frameCount; 
	std::string _textureID;
};