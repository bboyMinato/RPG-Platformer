#include "../include/Animation.h"
#include "../include/TextureManager.h"

void Animation::Update()
{
	_spriteFrame = (SDL_GetTicks() / _animSpeed) % _frameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(_textureID, x, y, spriteWidth, spriteHeight, _spriteRow, _spriteFrame, 3, flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
	_textureID = textureID;
	_spriteRow = spriteRow;
	_frameCount = frameCount;
	_animSpeed = animSpeed;	
}