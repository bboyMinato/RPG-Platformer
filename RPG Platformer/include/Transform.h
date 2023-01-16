#pragma once
#include "Vector2D.h"

class Transform
{
public:
	float X = 0, Y = 0;

	Transform(float x = 0, float y = 0) :X(x), Y(y) {}

	void TranslateX(float x) { X += x; }
	void TranslateY(float y) { Y += y; }
	void Translate(Vector2D v) { X += v.X; Y += v.Y; }

private:

};
