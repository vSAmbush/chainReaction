#pragma once
#include "Singleton.h"

class Menu : public Singleton<Menu>
{
	int width;
	int height;
	int amount;
	int cur;
	friend class Singleton<Menu>;
	Menu();
public:
	Shapes** buttons;
	Menu(int, int, int);
	Menu(Menu&);
	~Menu();
	void create();
	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
	int getAmount()
	{
		return amount;
	}
	int getCur()
	{
		return cur;
	}
	void setWidth(int width)
	{
		this->width = width;
	}
	void setHeight(int height)
	{
		this->height = height;
	}
	void setAmount(int amount)
	{
		this->amount = amount;
	}
	void setCur(int cur)
	{
		this->cur = cur;
	}
};

Menu::Menu()
{
	width = 600;
	height = 500;
	amount = 4;
	buttons = new Shapes*[amount];
	for (int i = 0; i < amount; i++)
		buttons[i] = new Rectangl();
	cur = amount - 1;
}

Menu::Menu(int width, int height, int amount)
{
	this->width = width;
	this->height = height;
	this->amount = amount;
	buttons = new Shapes*[amount];
	cur = amount - 1;
}

Menu::Menu(Menu& cpy)
{
	this->width = cpy.width;
	this->height = cpy.height;
	this->amount = cpy.amount;
	this->buttons = new Shapes*[this->amount];
	this->cur = amount - 1;
}

Menu::~Menu()
{
	for (int i = 0; i < amount; i++)
		delete buttons[i];
	delete[] buttons;
}