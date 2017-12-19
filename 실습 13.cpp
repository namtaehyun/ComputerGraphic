//위에꺼는 회전+이동
//밑에꺼는 이동만
//회전은 원일때만 적용해도됨.

/*
화면의 xy평면과 uz평면에 삼각형을 그린다
두삼각형의 테두리를 따라 작은삼각형이 이동한다
특정키보드를 누르면 두개의 큰삼각형이 y축을 기준으로 회전한다
*/
#include <math.h>
#include "Conversion.h"
#include <gl\GL.h>
#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>


GLvoid KeyBoardInput(unsigned char key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);

int k = 0;

void main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutTimerFunc(100, Timer, 1);
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

	glBegin(GL_LINES);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(0, 1, 0);
	//XY평면 삼각형
	glVertex3f(0, -1, 0);
	glVertex3f(0, -1, 1);
	glVertex3f(0, -1, 1);
	glVertex3f(0, 1, 0);
	//YZ평면 삼각형
	glEnd();



	glPushMatrix();
		if (k < 100) {
			glTranslatef(1-0.01*k, -1+0.02*k, 0);
		}
		else if (k >= 100 && k < 200)
		{
			glTranslatef(0, 1-0.02*(k-100), 0);
		}
		else if (k >= 200 && k < 300)
		{
			glTranslatef(0.01*(k-200),-1, 0);
		}
		else
		{
			glTranslatef(1,-1,0);
			k = 0;
		}
		glBegin(GL_TRIANGLES);
		glVertex2d(-0.1, -0.1);
		glVertex2d(0.1, -0.1);
		glVertex2d(0, 0.1);
		glEnd();
	glPopMatrix();
	//YZ축 삼각형
	glPushMatrix();
	if (k < 100) {
		glTranslatef(0, 1-0.02*k, 0.01*k);
	}
	else if (k >= 100 && k < 200)
	{
		glTranslatef(0, -1, 1-0.01*(k-100));
	}
	else if (k >= 200 && k < 300)
	{
		glTranslatef(0, -1 + 0.02*(k - 200), 0);
	}
	else
	{
		glTranslatef(0, 1, 0);
		k = 0;
	}
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.1, -0.1);
	glVertex2d(0.1, -0.1);
	glVertex2d(0, 0.1);
	glEnd();
	glPopMatrix();
	
	glutSwapBuffers();
}  // gl에서 가져옴 3차원 그래픽에 관련

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
}
//GL에서의 좌표값은 모두 -1~1까지이다. 하지만 좌표계는 바꿀 수 있다. 원점이 중점이다.

GLvoid Timer(int value)
{
	k+=5;
	glutTimerFunc(100, Timer, 1);
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