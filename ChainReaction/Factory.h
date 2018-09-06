#pragma once
#include "Shapes.h"

class Factory
{
protected:
	virtual Shapes* createShape(int, int, int, Color*) = 0;
};

class CircleFactory: public Factory
{
public:
	Shapes* createShape(int x, int y, int r, Color* color)
	{
		return new Circle(x, y, r, color);
	}
};

class SquareFactory : public Factory
{
public:
	Shapes* createShape(int x, int y, int side, Color* color)
	{
		return new Square(x, y, side, color);
	}
};