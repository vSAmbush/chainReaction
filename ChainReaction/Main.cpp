#include "Handle.h"

#define enter 13
#define esc 27

Menu& menu = Menu::Instance();

void drawText(const char *text, int length, int x, int y, bool flag)
{
	glMatrixMode(GL_PROJECTION);
	glColor3d(1, 1, 1);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	gluOrtho2D(0, menu.getWidth(), 0, menu.getHeight());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	if (flag)
		for (int i = 0; i < length; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	else
		for (int i = 0; i < length; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int x = menu.getWidth() / 3;
	int y = menu.getHeight() / 8;
	drawText("Chain Reaction", 15, menu.getWidth() / 4 + menu.getWidth() / 8, menu.getHeight() - menu.getHeight() / 6, true);
	char text[4][20] = { "New Game", "Load Game", "Information", "Exit" };
	for (int i = 0; i < menu.getAmount(); i++)
	{
		menu.buttons[i] = new Rectangl(x, y, 200, 50, red);
		y += 70;
	}
	y = menu.getHeight() / 8;
	for (int i = 0; i < menu.getAmount(); i++)
	{
		if (i == menu.getCur())
			menu.buttons[i]->setColor(red);
		else
			menu.buttons[i]->setColor(black);
		menu.buttons[i]->Draw();
		drawText(text[4 - i - 1], strlen(text[4 - i - 1]), x + 20, y + 20, false);
		y += 70;
	}
	glutSwapBuffers();
}

void key(int key, int x, int y)
{
	int k = menu.getCur();
	switch (key)
	{
	case GLUT_KEY_DOWN:
		menu.setCur(--k);
		if (k < 0)
			menu.setCur(menu.getAmount() - 1);
		break;
	case GLUT_KEY_UP:
		menu.setCur(++k);
		if (k >= menu.getAmount())
			menu.setCur(0);
		break;
	}
	glutPostRedisplay();
}

void Entr(unsigned char key, int x, int y)
{
	Stack<Player>* st = new Stack<Player>();
	if (key == enter)
	{
		switch (menu.getCur())
		{
		case 3:
			glutDestroyWindow(1);
			handle.createWindow();
			break;
		case 2:
			glutDestroyWindow(1);
			handle.load(handle);
			handle.createWindow();
			break;
		case 1:
			system("cls");
			st->load();
			st->sort();
			cout << "\t\t\tТаблица рекордов" << endl;
			if (st->getTop() != NULL)
				st->show();
			else
			{
				cout << "Таблица рекордор пуста!" << endl;
				system("pause");
			}
			break;
		case 0:
			handle.createWindow1();
			exit(0);
			break;
		}
	}
	glutPostRedisplay();
}

void tim(int)
{
	draw();
	glutTimerFunc(1, tim, 0);
}

void Menu::create()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("ChainReaction");
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	glutDisplayFunc(draw);
	glutKeyboardFunc(Entr);
	glutSpecialFunc(key);
	//glutTimerFunc(1, tim, 0);
		
	glutMainLoop();
}

int main(int argc, char** argv)
{
	setlocale(0, "");
	glutInit(&argc, argv);
	menu.create();
	return 0;
}