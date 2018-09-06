#pragma once
class Color
{
public:
	float red;
	float green;
	float blue;
	Color();
	Color(float, float, float);
	Color(Color& cpy);
};

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}

Color::Color(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Color::Color(Color& cpy)
{
	red = cpy.red;
	green = cpy.green;
	blue = cpy.blue;
}

namespace colors
{
	Color* yellow = new Color(1, 1, 0);
	Color* black = new Color(0, 0, 0);
	Color* red = new Color(1, 0, 0);
	Color* green = new Color(0, 1, 0);
	Color* blue = new Color(0, 0, 1);
	Color* white = new Color(1, 1, 1);
}

using namespace colors;