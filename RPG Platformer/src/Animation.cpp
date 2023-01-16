#include "../include/Animation.h"
#include "../include/TextureManager.h"

void Animation::Update()
{
	_spriteFrame = (SDL_GetTicks() / _animSpeed) % _frameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
	TextureManager::GetInstance()->DrawFrame(_textureID, x, y, spriteWidth, spriteHeight, _spriteRow, _spriteFrame, 3, _flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
	_textureID = textureID;
	_spriteRow = spriteRow;
	_frameCount = frameCount;
	_animSpeed = animSpeed;
	_flip = flip;
}