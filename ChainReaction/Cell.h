#pragma once
#include "size.h"
#include "Factory.h"

class Cell
{
	Shapes** shapes;
	int state;
	int x, y;
	Color** color;
	int position;
	int maxstate;
public:
	Cell();
	Cell(int, int, int, int, int);
	~Cell();
	int getState()
	{
		return state;
	}
	void setPlusState(int state)
	{
		this->state += state;
	}
	void setState(int state)
	{
		this->state = state;
	}
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
	Color* getColor(int i)
	{
		return color[i];
	}
	void setColor(Color* color, int i)
	{
		if (i < 2)
			this->color[i] = color;
	}
	int getPos()
	{
		return position;
	}
	void setPos(int position)
	{
		this->position = position;
	}
	int getMaxState()
	{
		return maxstate;
	}
	void setMaxState(int maxstate)
	{
		this->maxstate = maxstate;
	}
	void Draw();
	void saveCell(ofstream&);
	void loadCell(ifstream&, Cell*&);
};

void Cell::loadCell(ifstream& f, Cell*& cell)
{
	int x, y, state, position, maxstate, count;
	f >> x >> y >> state >> position >> maxstate >> count;
	cell = new Cell(x, y, state, position, maxstate);
	cell->setColor(black, 0);
	switch (count)
	{
	case 0:
		cell->setColor(red, 1);
		break;
	case 1:
		cell->setColor(green, 1);
		break;
	case 2:
		cell->setColor(blue, 1);
		break;
	case 3:
		cell->setColor(white, 1);
		break;
	default:
		cell->setColor(black, 1);
		break;
	}
}

void Cell::saveCell(ofstream& f)
{
	int t;
	if (color[1] == red)
		t = 0;
	else
		if (color[1] == green)
			t = 1;
		else
			if (color[1] == blue)
				t = 2;
			else
				if (color[1] == white)
					t = 3;
				else
					t = -1;
	f << x << " " << y << " " << state << " " << position << " " << maxstate << " " << t << endl;
}

Cell::Cell()
{
	state = 0;
	shapes = NULL;
	x = 0;
	y = 0;
	position = 0;
	color = new Color*[2];
	color[0] = black;
}

Cell::Cell(int x, int y, int state, int position, int maxstate)
{
	this->color = new Color*[2];
	this->x = x;
	this->y = y;
	this->state = state;
	this->color[0] = black;
	this->color[1] = black;
	this->position = position;
	this->maxstate = maxstate;
}

Cell::~Cell()
{
	switch (state)
	{
	case 0:
		delete shapes[0];
		break;
	case 1:
		for (int i = 0; i < 2; i++)
			delete shapes[i];
		break;
	case 2:
		for (int i = 0; i < 3; i++)
			delete shapes[i];
		break;
	case 3:
		for (int i = 0; i < 4; i++)
			delete shapes[i];
		break;
	}
	delete[] shapes;
}

void Cell::Draw()
{
	SquareFactory* sq = new SquareFactory;
	CircleFactory* cr = new CircleFactory;
	int side = (int)(WIDTH - 15) / 10;
	switch (state)
	{
	case 0:
		shapes = new Shapes*[1];
		shapes[0] = sq->createShape(x, y, side, color[0]);
		shapes[0]->Draw();
		break;
	case 1:
		shapes = new Shapes*[2];
		shapes[0] = sq->createShape(x, y, side, color[0]);
		shapes[1] = cr->createShape(x + side / 2, y + side / 2, side / 4, color[1]);
		for (int i = 0; i < 2; i++)
			shapes[i]->Draw();
		break;
	case 2:
		shapes = new Shapes*[3];
		shapes[0] = sq->createShape(x, y, side, color[0]);
		shapes[1] = cr->createShape(x + side / 3, y + side / 2, side / 4, color[1]);
		shapes[2] = cr->createShape(x + side - side / 3, y + side - side / 2, side / 4, color[1]);
		for (int i = 0; i < 3; i++)
			shapes[i]->Draw();
		break;
	case 3:
		shapes = new Shapes*[4];
		shapes[0] = sq->createShape(x, y, side, color[0]);
		shapes[1] = cr->createShape(x + side / 3, y + side / 2 + side / 8, side / 4, color[1]);
		shapes[2] = cr->createShape(x + side - side / 3, y + side / 2 + side / 8, side / 4, color[1]);
		shapes[3] = cr->createShape(x + side / 2, y + side / 3, side / 4, color[1]);
		for (int i = 0; i < 4; i++)
			shapes[i]->Draw();
		break;
	}
}