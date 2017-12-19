#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <glut.h>
void Timerfunction(int value);
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);

struct Point {
	double x, y;
	double angle;
	bool isTrue;
};
struct Circle {
	Point p[100];
	bool isTrue;
	int m;
	Circle()
	{
		for (int i = 0; i < 100; i++)
		{
			p[i].isTrue = false;
		}
		m = 0;
		isTrue = false;
	}
};
int idx = 0; //원의 인덱스
Point t[10][50];
Circle c[10];
int main(int argc, char** argv)
{
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
	return 0;
}


void Mouse(int button, int state, int x, int y)
{
	double temp;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (idx < 10) {
			for (int i = 0; i < 50; i++)
			{
				c[idx].p[i].angle = i*3.141592 / 5;
				c[idx].p[i].x = 1/100 * cos(c[idx].p[i].angle) + i * cos(c[idx].p[i].angle) + x;
				c[idx].p[i].y = 600 - (1/100 * sin(c[idx].p[i].angle)+ i * sin(c[idx].p[i].angle) + y);
			}
			for (int i = 50; i < 100; i++)
			{
				c[idx].p[i].angle = 3.141592 - c[idx].p[i-50].angle+0.35;
				c[idx].p[i].x = 1/100 * sin(c[idx].p[i].angle) + (i - 50) *sin(c[idx].p[i].angle) + x+2*(c[idx].p[49].x-x);
				c[idx].p[i].y = 600 - (1/100 * cos(c[idx].p[i].angle) + (i - 50) * cos(c[idx].p[i].angle) + y);
			}
			c[idx].isTrue = true;
		}
		else
		{
			idx = 0;
			for (int i = 0; i < 10; i++) {
				c[i].m = 0;
				c[i].isTrue=false;
			}
		}
		idx++;
	}

	glutPostRedisplay();
}

GLvoid drawScene()
{
	int n = rand() % 5 + 1;
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	for (int t = 0; t < 10; t++) {
		if (c[t].isTrue == true) {
			for (int i = 0; i < 100; i++)
			{
				if (i < 50) {
					if (c[t].p[i].isTrue == true) {
						glVertex2f(c[t].p[i].x, c[t].p[i].y);
						glVertex2f(c[t].p[i + 1].x, c[t].p[i + 1].y);
					}
				}
				else
				{
					if (c[t].p[i].isTrue == true) {
						glVertex2f(c[t].p[i].x, c[t].p[i].y);
						glVertex2f(c[t].p[i - 1].x, c[t].p[i - 1].y);
					}
				}
			}
		}
	}
	glEnd();
	glFinish();
	glutPostRedisplay();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);     // 그리기 색을 'green' 으로 지정 
	glFlush(); // 화면에 출력하기 
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glutPostRedisplay();
	glutPostRedisplay();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Timerfunction(int value) {
	printf("-----------------------\n");
	for (int i = 0; i < 10; i++) {
		if(c[i].isTrue==true&&c[i].m<100)
		c[i].m++;
	}
	for (int i = 0; i<10; i++)
	{
		if (c[i].m < 50) {
			for (int k = 0; k < c[i].m; k++)
			{
				c[i].p[k].isTrue = true;
			}
		}
		else if (c[i].m > 50 && c[i].m < 100)
		{
			for (int k = 0; k < c[i].m-50; k++)
			{
				c[i].p[k].isTrue = false;
				c[i].p[100-k].isTrue = true;
			}
		}
		else
		{
		}
		printf("%d \n", c[i].m);
	}
	glutTimerFunc(100, Timerfunction, 1);
	glutPostRedisplay();   // 화면 재 출력 
}