/*
화면 전체에 사인, 코사인, 스프링, 직사각형 그리기
– XY 평면에 위의 곡선 또는 직선을 위에서 아래로 순서대로 그린다.
– 스프링을 그릴 때, GL_LINE_STRIP으로 설정
– 스프링의 색은 그라데이션 (예, 빨강 → 파랑)을 넣기
– (좌측 그림은 스프링 곡선, 우측 그림은 사인곡선)
– 다음의 명령어를 수행한다.
• x/y/z: x/y/z축에 대하여 회전
• S/s: 제자리에서 확대/축소
• 좌측 화살표/우측 화살표: x축을 따라 좌측/우측 이동
• A/a: 애니메이션 시작/종료
• i: 제자리로 리셋
• q/Q: 프로그램 종료
*/
#include <math.h>
#include <stdlib.h>
#include "Conversion.h"
#include <gl\GL.h>
#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
GLvoid KeyBoardInput(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);

struct point {
	double angle[100];
	point()
	{
		for (int i = 0; i < 100; i++)
		{
			angle[i]= 3.141592 / 7 * i;
		}
	};
};


point Cos;
point Sin;
point Spring;
double X, Y; //확대용 변수
bool start=false;
bool big = false;

void main(int argc, char** argv) {
	X = 0;
	Y = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutTimerFunc(100, Timer, 1);

	glutSpecialFunc(SpecialKeyboard);
	glutKeyboardFunc(KeyBoardInput);
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

	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glBegin(GL_LINES);
	for (int i = 0; i < 99; i++) {
		glVertex3f(-0.5 + i*0.01 + X, sin(Sin.angle[i])*0.1 + 0.4 - Y, 0);
		glVertex3f(-0.5 + (i + 1)*0.01 + X, sin(Sin.angle[i + 1])*0.1 + 0.4 + Y, 0);

		glVertex3f(-0.5 + i*0.01 + X, cos(Sin.angle[i])*0.1 + 0.2 - Y, 0);
		glVertex3f(-0.5 + (i + 1)*0.01 + X, cos(Sin.angle[i + 1])*0.1 + 0.2 + Y, 0);
	}
	glEnd();
	for (int i = 0; i < 10; i++) {
		glRectf(-0.5 + 0.11*i + X, -0.4, -0.5 + 0.1 + 0.11*i + X, -0.5 - Y);
	}
	glBegin(GL_LINES);

	for (int i = 0; i < 99; i++) {
		if (i < 50) {
			glColor3f(1, 0, 0);
			glVertex3f(cos(Spring.angle[i])*0.1 + i*0.01 + X - 0.5, sin(Spring.angle[i])*0.1 - 0.2 - Y, 0);
			glVertex3f(cos(Spring.angle[i + 1])*0.1 + X + (i + 1)*0.01 - 0.5, sin(Spring.angle[i + 1])*0.1 - 0.2 + Y, 0);
		}
		else if (i > 50 && i < 55)
		{
			glColor3f(0.5, 0, 0.5);
			glVertex3f(cos(Spring.angle[i])*0.1 + i*0.01 + X - 0.5, sin(Spring.angle[i])*0.1 - 0.2 - Y, 0);
			glVertex3f(cos(Spring.angle[i + 1])*0.1 + X + (i + 1)*0.01 - 0.5, sin(Spring.angle[i + 1])*0.1 - 0.2 + Y, 0);
		}
		else
		{
			glColor3f(0, 0, 1);
			glVertex3f(cos(Spring.angle[i])*0.1 + i*0.01 + X - 0.5, sin(Spring.angle[i])*0.1 - 0.2 - Y, 0);
			glVertex3f(cos(Spring.angle[i + 1])*0.1 + X + (i + 1)*0.01 - 0.5, sin(Spring.angle[i + 1])*0.1 - 0.2 + Y, 0);
		}
	}

	glEnd();
	glPopMatrix();
	//좌표계
	//glFlush();
	glutSwapBuffers();
}  // gl에서 가져옴 3차원 그래픽에 관련

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
}
//GL에서의 좌표값은 모두 -1~1까지이다. 하지만 좌표계는 바꿀 수 있다. 원점이 중점이다.

GLvoid Timer(int value)
{
	if (start == true) {
		for (int i = 0; i < 100; i++)
		{
			Sin.angle[i] += 3.141592 / 10;
			Spring.angle[i] += 3.141592 / 10;
			Cos.angle[i] += 3.141592 / 10;
		}
	}
	glutTimerFunc(100, Timer, 1);
	
	glutPostRedisplay();
}

GLvoid KeyBoardInput(unsigned char key,int x,int y)
{
	switch (key)
	{
	case 's':
		if (big == false) {
			glLoadIdentity();
			glScalef(1.5f, 1.5f, 0.0f);
			big = true;
		}
		else
		{
			glLoadIdentity();
			big = false;
		}
		break;
	case 'a':
		if (start == true)
		{
			start = false;
			printf("false");
		}
		else
		{
			start = true;
			printf("true");
		}
		break;
	case 'i':
		glLoadIdentity();
		break;
	case 'q':
		exit(0);
		break;
	case 'x':
		glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
		break;
	case 'y':
		glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
		break;
	case 'z':
		glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y) 
{ 
	switch (key)
	{
	case GLUT_KEY_LEFT:
		X -= 0.01;
		break;
	case GLUT_KEY_RIGHT:
		X += 0.01;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
