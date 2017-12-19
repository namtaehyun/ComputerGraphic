#include <glut.h>  
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

struct Rect {
	int x1, y1, x2, y2;
	bool isTrue;
	double r, g, b;
	Rect()
	{
		isTrue = false;
		r = (rand() % 10);
		g = (rand() % 10);
		b = (rand() % 10);
	}
};

int idx=0;
bool click;
Rect mouse;
Rect rect[10];


void main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);    // 설정된 색으로 젂체를 칠하기 
	if (click == true)
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
		glRectf(mouse.x1, mouse.y1, mouse.x2, mouse.y2);
	}
	for (int i = 0; i < 10; i++)
	{
		glColor4f(rect[i].r/10, rect[i].g/10, rect[i].b/10, 1.0f);  // 바탕색을 'blue' 로 지정  
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
	}

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
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

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		click = true;
		mouse.x1 = x-50;
		mouse.y1 = 600-(y-50);
		mouse.x2 = x + 50;
		mouse.y2 = 600-(y + 50);
		glutTimerFunc(100, Timerfunction, 1);
	}
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		if (idx < 10) {
			rect[idx].isTrue = true;
			rect[idx].x1 = x - 25;
			rect[idx].y1 = 600 - (y - 25);
			rect[idx].x2 = x + 25;
			rect[idx].y2 = 600 - (y + 25);
			idx++;
		}
		else
		{
			idx = 0;
		}

	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (click == true)
	{
		//click = true;
		mouse.x1 = x - 50;
		mouse.y1 = 600 - (y - 50);
		mouse.x2 = x + 50;
		mouse.y2 = 600 - (y + 50);
	}
	glutPostRedisplay();
}

void Timerfunction(int value) {
	glutPostRedisplay();   // 화면 재 출력 
	for (int i = 0; i < 10; i++)
	{
		if (rect[i].isTrue == true)
		{
			if (rect[i].x1 < mouse.x1)
			{
				rect[i].x1 += 10;
				rect[i].x2 += 10;
			}
			else 
			{
				rect[i].x1 -= 10;
				rect[i].x2 -= 10;
			}
			if (rect[i].y1 < mouse.y1)
			{
				rect[i].y1 += 10;
				rect[i].y2 += 10;
			}
			else
			{
				rect[i].y1 -= 10;
				rect[i].y2 -= 10;
			}
		}
	}
	glutTimerFunc(100, Timerfunction, 1);
}