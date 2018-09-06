#pragma once
#include "Field.h"
#include "Player.h"
#include "Menu.h"
#include "Stack.h"
#include "size.h"
#include "Singleton.h"

class Handle : public Singleton<Handle>
{
	int amount;
	int maxamount;
	int count;
	void check(Cell*, Cell*);
	void winner();
	void deletePlayer(int);
	Stack<Player>* st;
	friend class Singleton<Handle>;
	Handle();
public:
	Field field;
	Player** players;
	Field getField()
	{
		return field;
	}
	Stack<Player>* getStack()
	{
		return st;
	}
	void setStack(Stack<Player>* st)
	{
		this->st = st;
	}
	void setField(Field field)
	{
		this->field = field;
	}
	Player** getPlayers()
	{
		return players;
	}
	void setPlayers(Player** players)
	{
		this->players = players;
	}
	Player* getPlayer(int i)
	{
		return players[i];
	}
	void setPlayer(Player* player, int i)
	{
		this->players[i] = player;
	}
	int getAmount()
	{
		return amount;
	}
	void setAmount(int amount)
	{
		if (amount < maxamount)
		{
			this->amount = amount;
			players = new Player*[amount];
			switch (amount)
			{
			case 2:
				players[0] = new Player(red);
				players[1] = new Player(green);
				break;
			case 3:
				players[0] = new Player(red);
				players[1] = new Player(green);
				players[2] = new Player(blue);
				break;
			case 4:
				players[0] = new Player(red);
				players[1] = new Player(green);
				players[2] = new Player(blue);
				players[3] = new Player(white);
				break;
			}
		}
	}
	int getCount()
	{
		if (count < amount)
			return count;
	}
	void setCount(int count)
	{
		this->count = count;
	}
	void bang(int, int, int);
	void process();
	void createWindow();
	void createWindow1();
	void save();
	void load(Handle&);
};

void Handle::save()
{
	ofstream f;
	f.open("save.txt");
	f << amount << endl << count << endl;
	for (int i = 0; i < amount; i++)
		f << players[i]->getChips() << " ";
	f << "\n";
	field.saveField(f);
	f.close();
}

void Handle::load(Handle& handle)
{
	ifstream f;
	handle.maxamount = 4;
	f.open("save.txt");
	long file_size;
	f.seekg(0, ios::end);
	file_size = f.tellg();
	if (file_size != 0)
	{
		f.seekg(0, ios::beg);
		f >> handle.amount >> handle.count;
		handle.players = new Player*[handle.amount];
		switch (handle.amount)
		{
		case 2:
			handle.players[0] = new Player(red);
			handle.players[0]->setName(0);
			handle.players[1] = new Player(green);
			handle.players[1]->setName(1);
			break;
		case 3:
			handle.players[0] = new Player(red);
			handle.players[0]->setName(0);
			handle.players[1] = new Player(green);
			handle.players[1]->setName(1);
			handle.players[2] = new Player(blue);
			handle.players[2]->setName(2);
			break;
		case 4:
			handle.players[0] = new Player(red);
			handle.players[0]->setName(0);
			handle.players[1] = new Player(green);
			handle.players[1]->setName(1);
			handle.players[2] = new Player(blue);
			handle.players[2]->setName(2);
			handle.players[3] = new Player(white);
			handle.players[3]->setName(3);
			break;
		}
		for (int i = 0; i < handle.amount; i++)
		{
			int tmp;
			f >> tmp;
			handle.players[i]->setChips(tmp);
		}
		handle.field.loadField(f, field, count);
		handle.field.cells[0][0]->setColor(yellow, 0);
		handle.field.Draw();
	}
	else
	{
		cout << "Сохранений нет, поэтому начнется новая игра!" << endl;
		system("pause");
		system("cls");
	}
	f.close();
}

Handle::Handle()
{
	field.Create();
	amount = 2;
	maxamount = 4;
	count = 0;
	players = new Player*[amount];
	switch (amount)
	{
	case 2:
		players[0] = new Player(red);
		players[0]->setName(0);
		players[1] = new Player(green);
		players[1]->setName(1);
		break;
	case 3:
		players[0] = new Player(red);
		players[0]->setName(0);
		players[1] = new Player(green);
		players[1]->setName(1);
		players[2] = new Player(blue);
		players[2]->setName(2);
		break;
	case 4:
		players[0] = new Player(red);
		players[0]->setName(0);
		players[1] = new Player(green);
		players[1]->setName(1);
		players[2] = new Player(blue);
		players[2]->setName(2);
		players[3] = new Player(white);
		players[4]->setName(3);
		break;
	}
}

void Handle::deletePlayer(int i)
{
	amount--;
	Player** temp = new Player*[amount];
	for (int j = 0; j < amount; j++)
		temp[j] = new Player();
	for (int j = i; j < amount; j++)
		players[j] = players[j + 1];
	for (int j = 0; j < amount; j++)
		temp[j] = players[j];
	players = new Player*[amount];
	for (int j = 0; j < amount; j++)
		players[j] = temp[j];
}

void Handle::check(Cell* cell1, Cell* cell2)
{
	if (cell1->getColor(1) != cell2->getColor(1) && cell2->getState() > 0)
	{
		players[count]->setPlusChips(cell2->getState() - 1);
		for (int i = 0; i < amount; i++)
		{
			if (cell2->getColor(1) == players[i]->getColor())
			{
				players[i]->setMinusChips(cell2->getState() - 1);
				if (players[i]->getChips() <= 0)
					deletePlayer(i);
			}
		}
		cell2->setColor(cell1->getColor(1), 1);
	}
	winner();
}

void Handle::bang(int i, int j, int position)
{
	switch (position)
	{
	case 0:
		field.cells[i][j]->setState(0);
		field.cells[i + 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i + 1][j]);
		field.cells[i][j + 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j + 1]);
		if (field.cells[i + 1][j]->getState() > field.cells[i + 1][j]->getMaxState())
			bang(i + 1, j, field.cells[i + 1][j]->getPos());
		if (field.cells[i][j + 1]->getState() > field.cells[i][j + 1]->getMaxState())
			bang(i, j + 1, field.cells[i][j + 1]->getPos());
		break;
	case 1:
		field.cells[i][j]->setState(0);
		field.cells[i + 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i + 1][j]);
		field.cells[i][j - 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j - 1]);
		if (field.cells[i + 1][j]->getState() > field.cells[i + 1][j]->getMaxState())
			bang(i + 1, j, field.cells[i + 1][j]->getPos());
		if (field.cells[i][j - 1]->getState() > field.cells[i][j - 1]->getMaxState())
			bang(i, j - 1, field.cells[i][j - 1]->getPos());
		break;
	case 2:
		field.cells[i][j]->setState(0);
		field.cells[i - 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i - 1][j]);
		field.cells[i][j - 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j - 1]);
		if (field.cells[i - 1][j]->getState() > field.cells[i - 1][j]->getMaxState())
			return bang(i - 1, j, field.cells[i - 1][j]->getPos());
		if (field.cells[i][j - 1]->getState() > field.cells[i][j - 1]->getMaxState())
			return bang(i, j - 1, field.cells[i][j - 1]->getPos());
		break;
	case 3:
		field.cells[i][j]->setState(0);
		field.cells[i - 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i - 1][j]);
		field.cells[i][j + 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j + 1]);
		if (field.cells[i - 1][j]->getState() > field.cells[i - 1][j]->getMaxState())
			bang(i - 1, j, field.cells[i - 1][j]->getPos());
		if (field.cells[i][j + 1]->getState() > field.cells[i][j + 1]->getMaxState())
			bang(i, j + 1, field.cells[i][j + 1]->getPos());
		break;
	case 4:
		field.cells[i][j]->setState(0);
		field.cells[i][j + 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j + 1]);
		field.cells[i + 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i + 1][j]);
		field.cells[i][j - 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j - 1]);
		if (field.cells[i][j + 1]->getState() > field.cells[i][j + 1]->getMaxState())
			bang(i, j + 1, field.cells[i][j + 1]->getPos());
		if (field.cells[i + 1][j]->getState() > field.cells[i + 1][j]->getMaxState())
			bang(i + 1, j, field.cells[i + 1][j]->getPos());
		if (field.cells[i][j - 1]->getState() > field.cells[i][j - 1]->getMaxState())
			bang(i, j - 1, field.cells[i][j - 1]->getPos());
		break;
	case 5:
		field.cells[i][j]->setState(0);
		field.cells[i][j + 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j + 1]);
		field.cells[i - 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i - 1][j]);
		field.cells[i][j - 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j - 1]);
		if (field.cells[i][j + 1]->getState() > field.cells[i][j + 1]->getMaxState())
			bang(i, j + 1, field.cells[i][j + 1]->getPos());
		if (field.cells[i - 1][j]->getState() > field.cells[i - 1][j]->getMaxState())
			bang(i - 1, j, field.cells[i - 1][j]->getPos());
		if (field.cells[i][j - 1]->getState() > field.cells[i][j - 1]->getMaxState())
			bang(i, j - 1, field.cells[i][j - 1]->getPos());
		break;
	case 6:
		field.cells[i][j]->setState(0);
		field.cells[i + 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i + 1][j]);
		field.cells[i][j + 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j + 1]);
		field.cells[i - 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i - 1][j]);
		if (field.cells[i + 1][j]->getState() > field.cells[i + 1][j]->getMaxState())
			bang(i + 1, j, field.cells[i + 1][j]->getPos());
		if (field.cells[i][j + 1]->getState() > field.cells[i][j + 1]->getMaxState())
			bang(i, j + 1, field.cells[i][j + 1]->getPos());
		if (field.cells[i - 1][j]->getState() > field.cells[i - 1][j]->getMaxState())
			bang(i - 1, j, field.cells[i - 1][j]->getPos());
		break;
	case 7:
		field.cells[i][j]->setState(0);
		field.cells[i + 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i + 1][j]);
		field.cells[i][j - 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j - 1]);
		field.cells[i - 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i - 1][j]);
		if (field.cells[i + 1][j]->getState() > field.cells[i + 1][j]->getMaxState())
			bang(i + 1, j, field.cells[i + 1][j]->getPos());
		if (field.cells[i][j - 1]->getState() > field.cells[i][j - 1]->getMaxState())
			bang(i, j - 1, field.cells[i][j - 1]->getPos());
		if (field.cells[i - 1][j]->getState() > field.cells[i - 1][j]->getMaxState())
			bang(i - 1, j, field.cells[i - 1][j]->getPos());
		break;
	case 8:
		field.cells[i][j]->setState(0);
		field.cells[i][j + 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j + 1]);
		field.cells[i - 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i - 1][j]);
		field.cells[i][j - 1]->setPlusState(1);
		check(field.cells[i][j], field.cells[i][j - 1]);
		field.cells[i + 1][j]->setPlusState(1);
		check(field.cells[i][j], field.cells[i + 1][j]);
		if (field.cells[i][j + 1]->getState() > field.cells[i][j + 1]->getMaxState())
			bang(i, j + 1, field.cells[i][j + 1]->getPos());
		if (field.cells[i - 1][j]->getState() > field.cells[i - 1][j]->getMaxState())
			bang(i - 1, j, field.cells[i - 1][j]->getPos());
		if (field.cells[i][j - 1]->getState() > field.cells[i][j - 1]->getMaxState())
			bang(i, j - 1, field.cells[i][j - 1]->getPos());
		if (field.cells[i + 1][j]->getState() > field.cells[i + 1][j]->getMaxState())
			bang(i + 1, j, field.cells[i + 1][j]->getPos());
		break;
	}
}

void Handle::process()
{
	if (players[count]->getCourse())
	{
		if (field.cells[field.getI()][field.getJ()]->getState() < field.cells[field.getI()][field.getJ()]->getMaxState())
		{
			field.cells[field.getI()][field.getJ()]->setPlusState(1);
			players[count]->setPlusChips(1);
		}
		else
		{
			players[count]->setPlusChips(1);
			bang(field.getI(), field.getJ(), field.cells[field.getI()][field.getJ()]->getPos());
		}
		field.setColor(players[((count + 1) >= amount) ? 0 : count + 1]->getColor());
		count++;
		if (count >= amount)
			count = 0;
	}
}

Handle& handle = Handle::Instance();
int k = 0, t = 0;

#define enter 13
#define esc 27

void Keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		t--;
		if (t < 0)
			t = handle.field.getAmountinColumn() - 1;
		handle.field.cells[k][t]->setColor(yellow, 0);
		if (t == handle.field.getAmountinColumn() - 1)
			handle.field.cells[k][0]->setColor(black, 0);
		else
			handle.field.cells[k][t + 1]->setColor(black, 0);
		break;
	case GLUT_KEY_RIGHT:
		t++;
		if (t > handle.field.getAmountinColumn() - 1)
			t = 0;
		handle.field.cells[k][t]->setColor(yellow, 0);
		if (t == 0)
			handle.field.cells[k][handle.field.getAmountinColumn() - 1]->setColor(black, 0);
		else
			handle.field.cells[k][t - 1]->setColor(black, 0);
		break;
	case GLUT_KEY_UP:
		k++;
		if (k > handle.field.getAmountinRow() - 1)
			k = 0;
		handle.field.cells[k][t]->setColor(yellow, 0);
		if (k == 0)
			handle.field.cells[handle.field.getAmountinRow() - 1][t]->setColor(black, 0);
		else
			handle.field.cells[k - 1][t]->setColor(black, 0);
		break;
	case GLUT_KEY_DOWN:
		k--;
		if (k < 0)
			k = handle.field.getAmountinRow() - 1;
		handle.field.cells[k][t]->setColor(yellow, 0);
		if (k == handle.field.getAmountinRow() - 1)
			handle.field.cells[0][t]->setColor(black, 0);
		else
			handle.field.cells[k + 1][t]->setColor(black, 0);
		break;
	}
	glutPostRedisplay();
}

void Enter(unsigned char key, int x, int y)
{
	switch (key)
	{
	case enter:
		if (handle.field.cells[k][t]->getColor(1) != handle.field.getColor() && handle.field.cells[k][t]->getState() > 0)
			break;
		else
		{
			handle.players[handle.getCount()]->setCourse(true);
			handle.field.cells[k][t]->setColor(handle.players[handle.getCount()]->getColor(), 1);
			handle.field.setI(k);
			handle.field.setJ(t);
			handle.field.cells[k][t]->setColor(black, 0);
			k = t = 0;
			handle.field.cells[k][t]->setColor(yellow, 0);
			handle.process();
			break;
		}
	case esc:
		handle.save();
		cout << "Игра сохранена!" << endl;
		system("pause");
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	handle.field.Draw();
	glutSwapBuffers();
}


void Handle::winner()
{
	system("cls");
	if (amount == 1)
	{
		if (players[0]->getColor() == red)
			cout << "Выграл игрок №" << 1 << endl;
		if (players[0]->getColor() == green)
			cout << "Выграл игрок №" << 2 << endl;
		if (players[0]->getColor() == blue)
			cout << "Выграл игрок №" << 3 << endl;
		if (players[0]->getColor() == white)
			cout << "Выграл игрок №" << 4 << endl;
		display();
		st = new Stack<Player>();
		for (int i = 0; i < amount; i++)
		{
			st->push(*players[i]);
			st->save();
		}
		system("pause");
		exit(0);
	}
}

void Timer(int)
{
	display();
	glutTimerFunc(1, Timer, 0);
}

void Handle::createWindow()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("ChainReaction");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glutDisplayFunc(display);
	//glutTimerFunc(1, Timer, 0);
	glutSpecialFunc(Keyboard);
	glutKeyboardFunc(Enter);

	glutMainLoop();
}

void Handle::createWindow1()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	int num = glutCreateWindow("ChainReaction");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glutDisplayFunc(display);
	glutTimerFunc(1, Timer, 0);
	glutSpecialFunc(Keyboard);
	glutKeyboardFunc(Enter);

	glutDestroyWindow(num);
	glutMainLoop();
}