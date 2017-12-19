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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	glutMouseFunc(Mouse);
	glutTimerFunc(100, Timerfunction, 1);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);    // 설정된 색으로 젂체를 칠하기 
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(100, 100, 500, 500); // 경계

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
	glFlush(); // 화면에 출력하기 
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
		//없어지는 조건
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