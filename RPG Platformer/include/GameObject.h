#pragma once
#include "SDL.h"
#include "Object.h"
#include "Transform.h"
#include "Point.h"

struct Properties
{
public:
	Properties(std::string textureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		X = x;
		Y = y;
		_width = width;
		_height = height;
		_flip = flip;		
		_textureID = textureID;
	}
		 
	float X, Y;
	int _width, _height;
	std::string _textureID;
	SDL_RendererFlip _flip;
};

class GameObject : public Object
{
public:
	GameObject() {}

	GameObject(Properties* props) : _textureID(props->_textureID), _width(props->_width), _height(props->_height),
		_flip(props->_flip)
	{
		_transform = new Transform(props->X, props->Y);	

		float px = props->X + props->_width / 2;
		float py = props->Y + props->_height / 2;
		_origin = new Point(px, py);
	}

	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

	inline Point* GetOrigin() { return _origin; }

protected:	
	Transform* _transform = nullptr;
	Point* _origin = nullptr;

	int _width = 50;
	int _height = 50;
	std::string _textureID;
	SDL_RendererFlip _flip = SDL_FLIP_NONE;
};
