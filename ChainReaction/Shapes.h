#pragma once
#include <GL\glew.h>
#include <GL\glut.h>
#include <GL\GL.h>
#include "size.h"

class Shapes
{
protected:
	int x;
	int y;
	Color* color;
public:
	Shapes();
	Shapes(int, int, Color*);
	virtual ~Shapes() {};
	virtual void Draw() = 0;
	int getX()
	{
		return x;
	}
	void setX(int x)
	{
		this->x = x;
	}
	int getY()
	{
		return y;
	}
	void setY(int y)
	{
		this->y = y;
	}
	Color* getColor()
	{
		return color;
	}
	void setColor(Color* color)
	{
		this->color = color;
	}
};

Shapes::Shapes()
{
	x = 0;
	y = 0;
	color = new Color();
}

Shapes::Shapes(int x, int y, Color* color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}

class Circle : public Shapes
{
	int r;
public:
	Circle();
	Circle(int, int, int, Color*);
	~Circle() {};
	int getR()
	{
		return r;
	}
	void setR(int r)
	{
		this->r = r;
	}
	void Draw();
};

Circle::Circle() : Shapes()
{
	r = 0;
}

Circle::Circle(int x, int y, int r, Color* color) : Shapes(x, y, color)
{
	this->r = r;
}

void Circle::Draw()
{
	double tmp;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color->red, color->green, color->blue);
	glVertex2d(x, y);
	for (int i = 0; i <= r; i++)
	{
		tmp = (double)i / r * 3.1415 * 2.0;
		glVertex2d(x + cos(tmp) * r, y + sin(tmp) * r);
	}
	glEnd();
}

class Square : public Shapes
{
	int side;
public:
	Square();
	Square(int, int, int, Color*);
	~Square() {};
	void Draw();
	int getSide()
	{
		return side;
	}
	void setSide(int side)
	{
		this->side = side;
	}
};

Square::Square() : Shapes()
{
	side = 0;
}

Square::Square(int x, int y, int side, Color* color) : Shapes(x, y, color)
{
	this->side = side;
}

void Square::Draw()
{
	glColor3f(color->red, color->green, color->blue);
	glBegin(GL_QUADS);
	glVertex2d(x, y);
	glVertex2d(x + side, y);
	glVertex2d(x + side, y + side);
	glVertex2d(x, y + side);
	glVertex2d(x, y);
	glEnd();
}

class Rectangl : public Shapes
{
	int width, height;
public:
	Rectangl();
	Rectangl(int, int, int, int, Color*);
	~Rectangl() {};
	void Draw();
};

Rectangl::Rectangl() : Shapes()
{
	width = 0;
	height = 0;
}

Rectangl::Rectangl(int x, int y, int width, int height, Color* color) : Shapes(x, y, color)
{
	this->width = width;
	this->height = height;
}

void Rectangl::Draw()
{
	glColor3f(color->red, color->green, color->blue);
	glBegin(GL_QUADS);
	glVertex2d(x, y);
	glVertex2d(x + width, y);
	glVertex2d(x + width, y + height);
	glVertex2d(x, y + height);
	glVertex2d(x, y);
	glEnd();
}