/*
• 이동, 회전, 신축 하기
– 화면에 마우스를 클릭하면 그 자리에 임의의 도형이 그려진다. 
– 그 도형이 반 시계방향으로 회전하며 점점 커진다. 
– 다른 곳에 클릭하면 또 다른 도형이 그려지고 회전하며 점점 커진다. 
– 종료 명령을 입력할 때까지 계속된다. 
*/
#include <math.h>
#include "Conversion.h"
#include <gl\GL.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>

struct Point
{
	bool isTrue;
	double x, y;
	int k;
	int Shape;
	Point() {
		k = 0;
		Shape = rand() % 4;
		isTrue = false;
	}
};

void Mouse(int button, int state, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
GLvoid KeyBoardInput(unsigned char key, int x, int y);

bool click = false;
int idx;
int Width, Height;

Point p[20]; // 다섯점을 잇는 직선그릴꺼임
void main(int argc, char** argv) {
	Width = 700;
	Height = 700;
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutKeyboardFunc(KeyBoardInput);
	glutTimerFunc(100, Timer, 1);
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()     // 출력 함수 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색을 'blue' 로 지정       
	glClear(GL_COLOR_BUFFER_BIT);   // 설정된 색으로 젂체를 칠하기      
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1, 1, 1);
	//glutWireSphere (GLdouble radius, GLint slices, GLint stacks); 
	//void glutSolidCube (GLdouble size); 
	// void glutWireCone (GLdouble base, GLdouble height, GLint slices, GLint stacks); 
	//void glutWireTeapot (GLdouble size);
	glBegin(GL_LINES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glEnd();

	glColor3f(1, 1, 0);

	for (int i = 0; i < 20; i++) {
		if (p[i].isTrue == true) {
			if (p[i].Shape == 0) {
				glPushMatrix();
				glRotatef(p[i].k, 0, 0, 1);
				glTranslatef(p[i].x, p[i].y, 0.0);
				glScalef(p[i].k*0.1, p[i].k*0.1, p[i].k*0.1);
				glutWireCone(0.2, 0.3, 5, 5);
				glPopMatrix();
			}
			else if (p[i].Shape == 1)
			{
				glPushMatrix();
				glRotatef(p[i].k, 0, 0, 1);
				glTranslatef(p[i].x, p[i].y, 0.0);
				glScalef(p[i].k*0.1, p[i].k*0.1, p[i].k*0.1);
				glutSolidCube(0.05);
				glPopMatrix();
			}
			else if (p[i].Shape == 2)
			{
				glPushMatrix();
				glRotatef(p[i].k, 0, 0, 1);
				glTranslatef(p[i].x, p[i].y, 0.0);
				glScalef(p[i].k*0.1, p[i].k*0.1, p[i].k*0.1);
				glutWireTeapot(0.05);
				glPopMatrix();
			}
			else if (p[i].Shape == 3)
			{
				glPushMatrix();
				glRotatef(p[i].k, 0, 0, 1);
				glTranslatef(p[i].x, p[i].y, 0.0);
				glScalef(p[i].k*0.1, p[i].k*0.1, p[i].k*0.1);
				glutWireSphere(0.05, 5, 5);
				glPopMatrix();
			}
		}
	}

	//좌표계
	glFlush();
}  // gl에서 가져옴 3차원 그래픽에 관련

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
}
//GL에서의 좌표값은 모두 -1~1까지이다. 하지만 좌표계는 바꿀 수 있다. 원점이 중점이다.

GLvoid Timer(int value)
{
	for (int i = 0; i < 20; i++)
	{
		if (p[i].isTrue == true)
		{
			p[i].k++;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (p[i].k > 50)
		{
			p[i].k = 0;
			p[i].isTrue = false;
		}
	}
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	int Y = Height - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (idx < 20) {
			p[idx].x = (double)(x - Width / 2) / (Width / 2);
			p[idx].y = (double)(Y - Height / 2) / (Height / 2);
			p[idx].isTrue = true;
			idx++;
		}
		else
		{
			idx = 0;
		}
	}
	glutPostRedisplay();
}

GLvoid KeyBoardInput(unsigned char key, int x, int y) 
{
	switch (key)
	{
	case 'a':
		glRotatef(10, 0, 1, 0);
		break;
	}
	glutPostRedisplay();
}