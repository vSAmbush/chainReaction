#pragma once
#include "Color.h"
#include "size.h"
#include <string>

class Player
{
	int chips;
	Color* color;
	bool course;
	string name;
	bool flag;
	string tname;
	int tchips;
public:
	Player();
	Player(Color*);
	Player(Player&);
	int getChips()
	{
		return chips;
	}
	void setChips(int chips)
	{
		this->chips = chips;
	}
	void setPlusChips(int chips)
	{
		this->chips += chips;
	}
	void setMinusChips(int chips)
	{
		this->chips -= chips;
	}
	Color* getColor()
	{
		return color;
	}
	void setColor(Color* color)
	{
		this->color = color;
	}
	bool getCourse()
	{
		return course;
	}
	void setCourse(bool course)
	{
		this->course = course;
	}
	bool operator!()
	{
		return flag;
	}
	bool operator>(Player& obj)
	{
		bool buf;
		if (this->chips < obj.chips)
			buf = true;
		else
			buf = false;
		return buf;
	}
	bool operator==(Player& obj)
	{
		bool buf;
		if (this->chips == obj.chips)
			buf = true;
		else
			buf = false;
		return buf;
	}
	friend ostream& operator<<(ostream& out, Player& obj)
	{
		out << obj.name << "\t" << obj.chips << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, Player& obj)
	{
		out << obj.name << " " << obj.chips;
		return out;
	}
	friend ifstream& operator>>(ifstream& out, Player& obj)
	{
		out >> obj.name >> obj.chips;
		if (obj.name != obj.tname && obj.chips != obj.tchips)
		{
			obj.flag = true;
			obj.tname = obj.name;
			obj.tchips = obj.chips;
		}
		else
			obj.flag = false;
		return out;
	}
	void setName(int count)
	{
		switch (count)
		{
		case 0:
			name = "Красный";
			break;
		case 1:
			name = "Зеленый";
			break;
		case 2:
			name = "Синий";
			break;
		case 3:
			name = "Белый";
			break;
		}
	}
	void setName1(string name)
	{
		this->name = name;
	}
};

Player::Player()
{
	chips = 0;
	course = false;
}

Player::Player(Color* color)
{
	chips = 0;
	course = false;
	this->color = color;
	name = new char[100];
	tname = name;
	tchips = chips;
}

Player::Player(Player& cpy)
{
	chips = cpy.chips;
	course = cpy.course;
	color = cpy.color;
	setName1(cpy.name);
}