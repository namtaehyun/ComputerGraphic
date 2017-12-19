#include <glut.h>  
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define RECT true
#define TRIANGLE false
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void move();
void Mouse(int button, int state, int x, int y);
void MenuFunc(int button);
void Keyboard(unsigned char key, int x, int y);

struct Rect {
	int x1, y1, x2, y2;
	int dir;
	bool isTrue;
	Rect()
	{
		isTrue = false;
		dir = rand() % 4+1;
	}
};
bool Shape=RECT;
int k = 0;
int speed=10;
int i = 0;
Rect rect[10];

void main(int argc, char *argv[]) {
	int SubMenu1;
	int MainMenu;

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	SubMenu1 = glutCreateMenu(MenuFunc);  
	glutAddMenuEntry("Rect", 1);
	glutAddMenuEntry("Triangle", 2); 
	MainMenu = glutCreateMenu(MenuFunc); 
	glutAddSubMenu("Shape", SubMenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, Timerfunction, 1);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);    // 설정된 색으로 젂체를 칠하기 
									 //glOrtho(left,right,bottom,top)
	if (Shape == RECT) {
		if (k % 2 == 0) {
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			for (int i = 0; i < 10; i++)
			{
				if (rect[i].isTrue == true) {
					glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
				}
			}
		}
		else
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 10; i++)
			{
				if (rect[i].isTrue == true) {
					glRectf(rect[i].x1 + 50, rect[i].y1 - 50, rect[i].x2 - 50, rect[i].y2 + 50);
				}
			}
		}
	}
	else
	{
		if (k % 2 == 0) {
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			for (int i = 0; i < 10; i++)
			{
				if (rect[i].isTrue == true) {
					glBegin(GL_TRIANGLES);
					glVertex2f(rect[i].x1, rect[i].y1);
					glVertex2f(rect[i].x2, rect[i].y1);
					glVertex2f((rect[i].x2 + rect[i].x1) / 2, rect[i].y2);
					glEnd();
				}
			}
		}
		else
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 10; i++)
			{
				if (rect[i].isTrue == true) {
					glBegin(GL_TRIANGLES);
					glVertex2f(rect[i].x1, rect[i].y1);
					glVertex2f(rect[i].x2, rect[i].y1);
					glVertex2f((rect[i].x2 + rect[i].x1) / 2, rect[i].y2-50);
					glEnd();
				}
			}
		}
	}
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

void Mouse(int button, int state, int x, int y)
{
	int size = rand() % 100 + 100;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (i < 10) {
			rect[i].x1 = x;
			rect[i].y1 = 600 - y;
			rect[i].x2 = x + size;
			rect[i].y2 = 600 - y + size;
			rect[i].isTrue = true;
			i++;
		}
		else
		{
			i = 0;
			rect[i].x1 = x;
			rect[i].y1 = 600 - y ;
			rect[i].x2 = x + size;
			rect[i].y2 = 600 - y + size;
		}
	}
	glutPostRedisplay();
}

void Timerfunction(int value) {
	move();
	k++;
	glutPostRedisplay();   // 화면 재 출력 
	glutTimerFunc(100, Timerfunction, 1); // 타이머함수 재 설정 
}

void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		Shape = RECT;
		break;
	case 2:
		Shape = TRIANGLE;
		break;
	}
	glutPostRedisplay();
}

void move()
{
	//1 ↗
	//2 ↙
	//3 ↘
	//4 ↖

	for (int i = 0; i < 10; i++) {
		if (rect[i].isTrue == true) {
			if (rect[i].dir == 1 && (rect[i].x1 + rect[i].x2) / 2 < 800 && (rect[i].y1 + rect[i].y2) / 2 > 600)
			{
				rect[i].dir = 3;
			}
			if (rect[i].dir == 3 && (rect[i].x1 + rect[i].x2) / 2 > 800 && (rect[i].y1 + rect[i].y2) / 2 < 600)
			{
				rect[i].dir = 2;
			}
			if (rect[i].dir == 2 && (rect[i].x1 + rect[i].x2) / 2 > 0 && (rect[i].y1 + rect[i].y2) / 2 < 0)
			{
				rect[i].dir = 4;
			}
			if (rect[i].dir == 4 && (rect[i].x1 + rect[i].x2) / 2 < 0 && (rect[i].y1 + rect[i].y2) / 2 < 600)
			{
				rect[i].dir = 1;
			}

			if (rect[i].dir == 4 && (rect[i].x1 + rect[i].x2) / 2 > 0 && (rect[i].y1 + rect[i].y2) / 2 > 600)
			{
				rect[i].dir = 2;
			}
			if (rect[i].dir == 2 && (rect[i].x1 + rect[i].x2) / 2 < 0 && (rect[i].y1 + rect[i].y2) / 2 > 0)
			{
				rect[i].dir = 3;
			}
			if (rect[i].dir == 3 && (rect[i].x1 + rect[i].x2) / 2 < 800 && (rect[i].y1 + rect[i].y2) / 2 < 0)
			{
				rect[i].dir = 1;
			}
			if (rect[i].dir == 1 && (rect[i].x1 + rect[i].x2) / 2 > 800 && (rect[i].y1 + rect[i].y2) / 2 < 600)
			{
				rect[i].dir = 3;
			}
			//x<0


			if (rect[i].dir == 1)
			{
				rect[i].x1 += speed;
				rect[i].x2 += speed;
				rect[i].y1 += speed;
				rect[i].y2 += speed;
			}
			else if (rect[i].dir == 2)
			{
				rect[i].x1 -= speed;
				rect[i].x2 -= speed;
				rect[i].y1 -= speed;
				rect[i].y2 -= speed;
			}
			else if (rect[i].dir == 3)
			{
				rect[i].x1 += speed;
				rect[i].x2 += speed;
				rect[i].y1 -= speed;
				rect[i].y2 -= speed;
			}
			else if (rect[i].dir == 4)
			{
				rect[i].x1 -= speed;
				rect[i].x2 -= speed;
				rect[i].y1 += speed;
				rect[i].y2 += speed;
			}
		}
	}
}
void Keyboard(unsigned char key, int x, int y) 
{
	if (key == '+')
	{
		speed++;
	}
	else if (key == '-')
	{
		speed--;
	}
}