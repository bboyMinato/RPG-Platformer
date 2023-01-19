#pragma once
#include <string>
#include <map>
#include "SDL.h"


class TextureManager
{
public:
	static TextureManager* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new TextureManager(); }

	SDL_Texture* LoadTexture(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Drop(std::string id);
	void Clean();
	
	void Draw(std::string id, int x, int y, int width, int height, float scroll = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	static TextureManager* _instance;

	SDL_Texture* _texture = nullptr;
	std::map<std::string, SDL_Texture*> _textureMap;
};