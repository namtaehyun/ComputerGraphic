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
	Point p[200];
	bool isTrue;
	int m;
	Circle()
	{
		m = 0;
		isTrue = false;
		for (int i = 0; i < 200; i++)
		{
			p[i].isTrue = false;
		}
	}
};
int idx = 0; //원의 인덱스
Circle c[10];
Point p[10];
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d \n", idx);
		if (idx < 10) {
			for (int i = 0; i < 100; i++)
			{
				c[idx].p[i].angle = i*3.141592 / 10; //회오리를 위해 각도를 조정함
				c[idx].p[i].x = 1 / 100 * cos(c[idx].p[i].angle) + i * cos(c[idx].p[i].angle) + x;
				c[idx].p[i].y = 600 - (1 / 100 * sin(c[idx].p[i].angle) + i * sin(c[idx].p[i].angle) + y);
			}
			for (int i = 100; i < 200; i++)
			{
				c[idx].p[i].angle = c[idx].p[i-100].angle+3.141592/2; //반대편 회오리는 방향이 반대여야함.π/2만큼 더해줌
													 //				c[idx].p[i].x = 30 * cos(c[idx].p[i].angle) + x;
													 //				c[idx].p[i].y = 600 - (30 * sin(c[idx].p[i].angle) + y);
				c[idx].p[i].x = 1 / 100 * sin(-c[idx].p[i].angle) + (i - 100)* sin(-c[idx].p[i].angle)+ 2*c[idx].p[99].x-x;
				c[idx].p[i].y = 600 - (1 / 100 * cos(-c[idx].p[i].angle) + (i - 100) * cos(-c[idx].p[i].angle) + y);
			}

			c[idx].isTrue = true;
			idx++;
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				c[i].isTrue = false;
				c[i].m = 0;
				for (int k = 0; k < 200; k++)
				{
					c[i].p[k].isTrue = false;
				}
			}
			idx = 0;
		}
		//for (int i = 0; i < 10; i++)
		//{
		//	printf("%d %f %f \n",i ,p[i].x, p[i].y);
		//}
	}

	glutPostRedisplay();
}

GLvoid drawScene()
{
	int n = rand() % 5 + 1;
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (int t = 0; t < 10; t++) {
		if (c[t].isTrue == true) {
			for (int i = 0; i < 200; i++)
			{
				if (c[t].p[i].isTrue == true) {
					if (i < 99) {
						glVertex2f(c[t].p[i].x, c[t].p[i].y);
						glVertex2f(c[t].p[i + 1].x, c[t].p[i + 1].y);
					}
					else if (i == 99)
					{
						glVertex2f(c[t].p[99].x, c[t].p[99].y);
						glVertex2f(c[t].p[199].x, c[t].p[199].y);
					}
					else
					{
						glVertex2f(c[t].p[i].x, c[t].p[i].y);
						glVertex2f(c[t].p[i - 1].x, c[t].p[i - 1].y);
					}
				}
			}
		}
	}

	glEnd();
	glFinish();

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
	glutPostRedisplay();   // 화면 재 출력 
	for (int i = 0; i < 10; i++)
	{
		if (c[i].isTrue == true && c[i].m < 200)
		{
			c[i].m++;
			if (c[i].m < 100)
			{
				c[i].p[c[i].m].isTrue = true;
			}
			else if (c[i].m > 100 && c[i].m < 200)
			{
					c[i].p[c[i].m-100].isTrue = false;
					c[i].p[300 - c[i].m].isTrue = true;
			}
			else{}
		}
	}




	glutTimerFunc(100, Timerfunction, 1);
}