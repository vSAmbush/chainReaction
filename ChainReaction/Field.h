#pragma once
#include "Cell.h"
#include "size.h"

class Field
{
	Color* color;
	int amount;
	int maxamount;
	int amountinrow;
	int amountincolumn;
	int i;
	int j;
public:
	Cell*** cells;
	Field();
	Field(Field&);
	~Field();
	Color* getColor()
	{
		return color;
	}
	void setColor(Color* color)
	{
		this->color = color;
	}
	int getAmount()
	{
		return amount;
	}
	void setAmount(int amount)
	{
		if (amount > maxamount)
			cerr << "Overload";
		else
			this->amount = amount;
	}
	int getAmountinRow()
	{
		return amountinrow;
	}
	int getAmountinColumn()
	{
		return amountincolumn;
	}
	int getI()
	{
		return i;
	}
	void setI(int i)
	{
		this->i = i;
	}
	int getJ()
	{
		return j;
	}
	void setJ(int j)
	{
		this->j = j;
	}
	void Create();
	void Draw();
	void saveField(ofstream&);
	void loadField(ifstream&, Field&, int count);
};

Field::Field(Field& cpy)
{
	this->color = cpy.color;
	this->maxamount = cpy.maxamount;
	this->amount = cpy.amount;
}

void Field::saveField(ofstream& f)
{
	f << amount << endl;
	for (int i = 0; i < amountinrow; i++)
		for (int j = 0; j < amountincolumn; j++)
			cells[i][j]->saveCell(f);
}

void Field::loadField(ifstream& f, Field& field, int count)
{
	switch (count)
	{
	case 0:
		color = red;
		break;
	case 1:
		color = green;
		break;
	case 2:
		color = blue;
		break;
	case 3:
		color = white;
		break;
	}
	field.maxamount = 625;
	f >> field.amount;
	field.amountinrow = field.amountincolumn = (int)sqrtf(amount);
	field.cells = new Cell**[amountinrow];
	for (int i = 0; i < field.amountinrow; i++)
		field.cells[i] = new Cell*[amountincolumn];
	for (int i = 0; i < field.amountinrow; i++)
		for (int j = 0; j < field.amountincolumn; j++)
			field.cells[i][j]->loadCell(f, cells[i][j]);
}

Field::Field()
{
	color = red;
	maxamount = 625;
	amount = 100;
	amountinrow = amountincolumn = (int)sqrtf(amount);
	cells = new Cell**[amountinrow];
	for (int i = 0; i < amountinrow; i++)
		cells[i] = new Cell*[amountincolumn];
}

Field::~Field()
{
	for (int i = 0; i < amountinrow; i++)
		for (int j = 0; j < amountincolumn; j++)
			delete cells[i][j];
	for (int i = 0; i < amountinrow; i++)
		delete cells[i];
	delete[] cells;
	delete[] color;
}

void Field::Create()
{
	int x = 5, y = 5;
	float side = (WIDTH - 15) / 10;
	for (int i = 0; i < amountinrow; i++)
	{
		for (int j = 0; j < amountincolumn; j++)
		{
			if (i == 0 && j == 0)
				cells[i][j] = new Cell(x, y, 0, 0, 1);
			else
				if (i == 0 && j == amountincolumn - 1)
					cells[i][j] = new Cell(x, y, 0, 1, 1);
				else
					if (i == amountinrow - 1 && j == amountincolumn - 1)
						cells[i][j] = new Cell(x, y, 0, 2, 1);
					else
						if (i == amountinrow - 1 && j == 0)
							cells[i][j] = new Cell(x, y, 0, 3, 1);
						else
							if (i == 0)
								cells[i][j] = new Cell(x, y, 0, 4, 2);
							else
								if (i == amountinrow - 1)
									cells[i][j] = new Cell(x, y, 0, 5, 2);
								else
									if (j == 0)
										cells[i][j] = new Cell(x, y, 0, 6, 2);
									else
										if (j == amountincolumn - 1)
											cells[i][j] = new Cell(x, y, 0, 7, 2);
										else
											cells[i][j] = new Cell(x, y, 0, 8, 3);
			x += side + 1;
		}
		x = 5;
		y += side + 1;
	}
	cells[0][0]->setColor(yellow, 0);
}

void Field::Draw()
{
	Shapes* a = new Rectangl(4, 4, WIDTH - 9, HEIGHT - 9, color);
	a->Draw();
	for (int i = 0; i < amountinrow; i++)
		for (int j = 0; j < amountincolumn; j++)
			cells[i][j]->Draw();
}