//�������� ȸ��+�̵�
//�ؿ����� �̵���
//ȸ���� ���϶��� �����ص���.

/*
ȭ���� xy���� uz��鿡 �ﰢ���� �׸���
�λﰢ���� �׵θ��� ���� �����ﰢ���� �̵��Ѵ�
Ư��Ű���带 ������ �ΰ��� ū�ﰢ���� y���� �������� ȸ���Ѵ�
*/

#include "Conversion.h"
#include <gl\GL.h>
#include <glut.h>
#include <stdio.h>    // �Ǵ� <GL/freeglut.h>


GLvoid KeyBoardInput(unsigned char key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);

int k = 0;

void main(int argc, char** argv) {
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutTimerFunc(100, Timer, 1);
	glutKeyboardFunc(KeyBoardInput);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()     // ��� �Լ� 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // �������� 'blue' �� ����       
	glClear(GL_COLOR_BUFFER_BIT);   // ������ ������ ��ü�� ĥ�ϱ�      
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(0, 1, 0);
	//XY��� �ﰢ��
	glVertex3f(0, -1, 0);
	glVertex3f(0, -1, 1);
	glVertex3f(0, -1, 1);
	glVertex3f(0, 1, 0);
	//YZ��� �ﰢ��
	glEnd();

	glPushMatrix();
	if (k < 100) {
		glTranslatef(1 - 0.01*k, -1 + 0.02*k, 0);
	}
	else if (k >= 100 && k < 200)
	{
		glTranslatef(0, 1 - 0.02*(k - 100), 0);
	}
	else if (k >= 200 && k < 300)
	{
		glTranslatef(0.01*(k - 200), -1, 0);
	}
	else
	{
		glTranslatef(1, -1, 0);
		k = 0;
	}
	glRotatef(k, 0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.1, -0.1);
	glVertex2d(0.1, -0.1);
	glVertex2d(0, 0.1);
	glEnd();
	glPopMatrix();
	//YZ�� �ﰢ��
	glPushMatrix();
	if (k < 100) {
		glTranslatef(0, 1 - 0.02*k, 0.01*k);
	}
	else if (k >= 100 && k < 200)
	{
		glTranslatef(0, -1, 1 - 0.01*(k - 100));
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
	glRotatef(k, 0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.1, -0.1);
	glVertex2d(0.1, -0.1);
	glVertex2d(0, 0.1);
	glEnd();
	glPopMatrix();


	glFlush();
}  // gl���� ������ 3���� �׷��ȿ� ����

GLvoid reshape(int w, int h)    // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
}
//GL������ ��ǥ���� ��� -1~1�����̴�. ������ ��ǥ��� �ٲ� �� �ִ�. ������ �����̴�.

GLvoid Timer(int value)
{
	k += 5;
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