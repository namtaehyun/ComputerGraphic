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
};
struct Circle {
	Point p[50];
	bool aorb; // a일 경우 반지름이 초기화되지 않고 쭉 퍼져나감, b일 경우 반지름이 일정수준 초과되면 다시 원점으로 돌아옴
	bool isTrue;
	int m;
	Circle()
	{
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (idx < 10) {
			for (int i = 0; i < 50; i++)
			{
				c[idx].p[i].angle = i*3.141592 / 25;
				c[idx].p[i].x = 30 * cos(c[idx].p[i].angle) + x;
				c[idx].p[i].y = 600 - (30 * sin(c[idx].p[i].angle) + y);
				c[idx].aorb = rand()%2;
				t[idx][i].x = c[idx].p[i].x;
				t[idx][i].y = c[idx].p[i].y;
			}
			c[idx].isTrue = true;
			idx ++;
		}
		else
		{
			idx = 0;
		}
	}

	glutPostRedisplay();
}

GLvoid drawScene()
{
	int n = rand() % 5 + 1;
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int t = 0; t < 10; t++) {
		if (c[t].isTrue == true) {
			for (int i = 0; i < 50; i++)
			{
				glVertex2f(c[t].p[i].x, c[t].p[i].y);
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
	printf("-----------------------\n");
	for (int i = 0;i<10;i++)
	{
		printf("%d \n", c[i].m);
	}
	for (int k = 0; k < 10; k++) {
		if (c[k].aorb == true && c[k].isTrue == true) {
			for (int i = 0; i < 50; i++)
			{
				c[k].p[i].x += 10*sin(c[k].p[i].angle);
				c[k].p[i].y += 10*cos(c[k].p[i].angle);
			}
		}
		else
		{
			if (c[k].aorb == false&&c[k].isTrue==true)  // m이 동시다발적으로 적용됨 -> m은 타이머고 m이 10일때 처음으로 돌아감
			{
				if (c[k].m < 10) {
					for (int i = 0; i < 50; i++)
					{
						c[k].p[i].x += 10 * sin(c[k].p[i].angle);
						c[k].p[i].y += 10 * cos(c[k].p[i].angle);
					}
					c[k].m++;
				}
				else
				{
					for (int i = 0; i < 50; i++)
					{
						c[k].m = 0;
						c[k].p[i].x = t[k][i].x;
						c[k].p[i].y = t[k][i].y;
					}
				}
			}
		}
	}
	glutTimerFunc(100, Timerfunction, 1);
}			