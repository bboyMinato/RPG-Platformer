#pragma once
#include <iostream>
#include <string>

class Vector2D
{
public:
	float X, Y;

	Vector2D(float x = 0, float y = 0) :X(x), Y(y) {}

	//addition
	Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	//substraction
	Vector2D operator-(const Vector2D& v2) const
	{
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	//mupltiplication	
	Vector2D operator*(const float scalar) const
	{
		return Vector2D(X * scalar, Y * scalar);
	}

	void Log(std::string msg = "")
	{
		std::cout << msg << "(X, Y) = (" << X << " " << Y << ")" << std::endl;
	}

private:

};