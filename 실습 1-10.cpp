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
	int x, y;
	int speed;
	int dir;
	int rad;
	bool isTrue;
	int m;
	double R, G, B;
	Circle()
	{
		R = rand() % 10*0.1;
		G = rand() % 10 * 0.1;
		B = rand() % 10 * 0.1;
		speed = rand() % 3+1;
		dir = rand()%7+1;
		m = 0;
		isTrue = false;
		rad = 50;
	}
};

Circle c[20];
int idx = 0;
int a[20];
int b[20];
int kk[20];
void main(int argc, char *argv[]) {
	for (int i = 0; i < 20; i++)
	{
		kk[i] = 0;
		a[i] = 0;
		b[i] = 0;
	}
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
	for (int i = 0; i < 20; i++)
	{
		if (c[i].isTrue == true)
		{
			glColor3f(c[i].R,c[i].G,c[i].B);
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
		if (c[i].dir < 4) {
			a[i] += 10;
			b[i] += 10;
		}
		else if(c[i].dir>=4&&c[i].dir<6)
		{
			a[i] += 10;
		}
		else if (c[i].dir >= 6 && c[i].dir<=7)
		{
			b[i] += 10;
		}
		if (c[i].isTrue == true)
		{
			if (c[i].rad > 10) {
				c[i].rad -= 3;
			}
			for (int k = 0; k < 50; k++)
			{
				if (kk[i] == 1) {
					if (c[i].dir == 0) {
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x + a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) + b[i];
					}
					else if (c[i].dir == 1)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x + a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) - b[i];
					}
					else if (c[i].dir == 2)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x - a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) - b[i];
					}
					else if (c[i].dir == 3)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x - a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) + b[i];
					}
					else if (c[i].dir == 4)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x - a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y)-2*b[i];
					}
					else if (c[i].dir == 5)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x + a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) - 2 * b[i];
					}
					else if (c[i].dir == 6)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x -2* a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) + b[i];
					}
					else if (c[i].dir == 7)
					{
						c[i].p[k].x = c[i].rad * cos(c[i].p[k].angle) + c[i].x - 2 * a[i];
						c[i].p[k].y = 600 - (c[i].rad * sin(c[i].p[k].angle) + c[i].y) - b[i];
					}
				}
			}
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
	printf("=============================\n");
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
				c[idx].p[i].x = c[idx].rad * cos(c[idx].p[i].angle) + x;
				c[idx].p[i].y = 600 - (c[idx].rad * sin(c[idx].p[i].angle) + y);
			}
			c[idx].x = x;
			c[idx].y = y;
			a[idx] = 0;
			b[idx] = 0;
			kk[idx] = 1;
			c[idx].isTrue = true;
			idx++;
		}
		else
		{
			for (int k = 0; k < 20; k++)
			{
				kk[k] = 0;
				a[k] = 0;
				b[k] = 0;
				c[k].rad = 50;
				for (int i = 0; i < 50; i++)
				{
					c[k].p[i].angle = 0;
					c[k].p[i].x = 0;
					c[k].p[i].y = 0;
				}
				c[k].isTrue = false;
			}
			idx = 0;
		}
	}

	glutPostRedisplay();
}