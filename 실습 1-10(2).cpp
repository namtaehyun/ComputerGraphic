#include <glut.h>   
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Mouse(int button, int state, int x, int y);

struct Point {
	double x, y;
	double angle;
};
struct Circle {
	Point p[50];
	int speed;
	int dir[50];
	bool isTrue;
	int m;
	Circle()
	{
		speed = rand() % 3 + 1;
		for (int i = 0; i < 50; i++)
		{
			dir[i] = rand() % 8;
		}
		m = 0;
		isTrue = false;
	}
};

void move(Circle c[]);
Circle c[20];
int idx = 0;

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ����  
	glutInitWindowSize(800, 600);    // �������� ũ�� ����
	glutCreateWindow("Example2");    // ������ ���� (������ �̸�)  
	glutMouseFunc(Mouse);
	glutTimerFunc(100, Timerfunction, 1);
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // �������� 'blue' �� ����  
	glClear(GL_COLOR_BUFFER_BIT);    // ������ ������ ��ü�� ĥ�ϱ� 
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(100, 100, 500, 500); // ���

	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 20; i++)
	{
		if (c[i].isTrue == true)
		{
			for (int k = 0; k < 50; k++) {
				glVertex2i(c[i].p[k].x, c[i].p[k].y);
			}
		}
	}
	glEnd();
	glFlush(); // ȭ�鿡 ����ϱ� 
	glutPostRedisplay();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600, -1, 1);
	glutPostRedisplay();
}

void Timerfunction(int value)
{
	for (int i = 0; i < 20; i++)
	{
		if (c[i].isTrue == true)
		{
			move(c);
		}
	}
	glutTimerFunc(100, Timerfunction, 1);
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (idx < 20) {
			for (int i = 0; i < 50; i++)
			{
				c[idx].p[i].angle = i*3.141592 / 25;
				c[idx].p[i].x = 30 * cos(c[idx].p[i].angle) + x;
				c[idx].p[i].y = 600 - (30 * sin(c[idx].p[i].angle) + y);
			}
			c[idx].isTrue = true;
			idx++;
		}
		else
		{
			idx = 0;
		}
	}

	glutPostRedisplay();
}


void move(Circle c[])
{
	for (int i = 0; i < 20; i++)
	{
		for (int k = 0; k < 50; k++) {
			if (c[i].dir[k] == 1)
			{
				c[i].p[k].x++;
				c[i].p[k].y++;
			}
			else if (c[i].dir[k] == 2)
			{
				c[i].p[k].x++;
				c[i].p[k].y--;
			}
			else if (c[i].dir[k] == 3)
			{
				c[i].p[k].x--;
				c[i].p[k].y++;
			}
			else if (c[i].dir[k] == 4)
			{
				c[i].p[k].y++;
			}
			else if (c[i].dir[k] == 5)
			{
				c[i].p[k].x++;
			}
			else if (c[i].dir[k] == 6)
			{
				c[i].p[k].x--;
			}
			else if (c[i].dir[k] == 7)
			{
				c[i].p[k].y--;
			}

		}
		//�������� ����
		for (int k = 0; k < 50; k++) {
			if (c[i].p[k].x > 100 && c[i].p[k].x < 500 && c[i].p[k].y>100 && c[i].p[k].y < 500)
			{

			}
			else
			{
				c[i].isTrue = false;
			}
		}
	}
}