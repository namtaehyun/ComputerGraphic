/*
마우스를 찍어서 2차원 화면에 곡선을 그린다.
-3차곡선을 그린다. (제어점 4개를 한 구간으로 설정)
-마우스를 찍은 곳에 제어점을 표시한다.
-glOrtho를 사용하여 2차원 평면으로 설정
-r/R 그린 곡선을 지우고 새로운 곡선을 그릴 수 있도록 한다.
*/
#include <math.h>
#include "Conversion.h"
#include <gl\GL.h>
#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>


void Mouse(int button, int state, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);

void keyboard(unsigned char key, int x, int y);
GLfloat ctrlpoints[5][4][3]; // 5개의 컨트롤포인트 셋트 4개의 컨트롤포인트 2개의 컨트롤포인트의 좌표값들
//GLfloat ctrlpoints[4][3] = {
	//{ 40.0, 40.0, 0.0 },{ 20.0, 80.0, 0.0 },{ 60.0, 60.0, 0.0 } ,{ 80.0, 0.0, 0.0 } };
bool click =false;
int yidx;
int xidx;
int Width, Height;
void main(int argc, char** argv) {
	yidx = 0;
	xidx = 0;
	Width = 700;
	Height = 700;
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutTimerFunc(100, Timer, 1);
	glutKeyboardFunc(keyboard);
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
	glPointSize(5.0);
	{
		for (int k = 0; k < 5; k++) {
			glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpoints[k][0][0]);
			glEnable(GL_MAP1_VERTEX_3);
			{	
			glBegin(GL_LINE_STRIP);
			if(ctrlpoints[k][3][0]!=0)
			for (int i = 0; i <= 10; i++)
				glEvalCoord1f((GLfloat)i / 10);
			glEnd();
			}
			glDisable(GL_MAP1_VERTEX_3);
		}
		glBegin(GL_POINTS);
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 4; i++)
				if(ctrlpoints[k][i][0]!=0)
				glVertex3f(ctrlpoints[k][i][0], ctrlpoints[k][i][1], ctrlpoints[k][i][2]);
		}
		glEnd();
	}
	glColor3f(1, 1, 0);
	glFlush();
}  // gl에서 가져옴 3차원 그래픽에 관련

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	Width = w;
	Height = h;
	glOrtho(0, 700, 0, 700, -1, 1);
	glViewport(0, 0, w, h);
}
//GL에서의 좌표값은 모두 -1~1까지이다. 하지만 좌표계는 바꿀 수 있다. 원점이 중점이다.

GLvoid Timer(int value)
{
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}


void Mouse(int button, int state, int x, int y)
{
	int Y = Height - y;
	printf("%d ", xidx);
	printf("%d \n", yidx);

	if (button == GLUT_LEFT_BUTTON&& state == GLUT_DOWN)
	{
		if (xidx < 5) {
			if (yidx < 4) {
				ctrlpoints[xidx][yidx][0] = (GLfloat)x;
				ctrlpoints[xidx][yidx][1] = (GLfloat)Y;
				ctrlpoints[xidx][yidx][2] = 0;
				yidx++;
			} //xidx를 +해주고, 
			else
			{
				xidx++;
				ctrlpoints[xidx][0][0] = ctrlpoints[xidx-1][3][0];
				ctrlpoints[xidx][0][1] = ctrlpoints[xidx-1][3][1];
				ctrlpoints[xidx][0][2] = 0;
				yidx = 1;
			}
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'r':
		xidx = 0;
		yidx = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				ctrlpoints[i][k][0] = 0;
				ctrlpoints[i][k][1] = 0;
				ctrlpoints[i][k][2] = 0;
			}
		}
		break;
	}
	glutPostRedisplay();
}