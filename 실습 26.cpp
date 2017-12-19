#include <glut.h>
#include <stdio.h>    // �Ǵ� <GL/freeglut.h>
#include <cmath>
#include <stdlib.h>
#define Gravity 0.98
#define PI 3.141592
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void DrawCube();
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
void Draw_Door();
void DrawBall();
int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
void DrawArea();
bool RemoveHiddenSurface;
bool Curling;
void Collide();
int Door_angle;
bool Open;
double swingAngle;
bool swing;
int robot_dir;
int robot_angle;
double rx, ry;
bool jump;
int jtime;
double jumpY;
/*�ǽ� 25
3���� ��ƨ���
- ��������/��������/�ø��� ����Ѵ�.
- ���� Ƣ�� ������ ����� �̿��Ͽ� ������ü�� ���¸� �����.
�� ���� �ٸ� ����� ǥ���Ѵ�.
���� ������ �Ʒ��� ���� ������ ���� �׸���.
�ǽ� 23�� ����ü�� �ٱ���, �ǽ������� ������ ���̴� ���̴�.
���� ���ο��� ���� �̵��Ѵ�.
������ü�� �鿡 ���� ������ ������ �ٲ㼭 �̵��� �Ѵ�.
�ٴڿ� z�� ���� �Ϸķ� �پ��� ũ���� ����ü�� 3���̻� ���´�.
- z�� ���� ȸ���ϸ� �׿� ���� ����ü�� �̵��Ѵ�.
- Ű���� ���
z/Z z������ ��/�� �������� �̵�
y/Y y�࿡ �ð�/�ݽð�������� ȸ��
B : ���� ���� ���ܼ� ƨ��� �����Ѵ�. ( �ִ� 5��)
m/M : ������ �ٴڸ��� ��ĭ�� ��/���������� �ٲ۴�.
- ���콺���
���콺�� �������� �ű��
����ü�� z����� �������� ȸ��
���콺�� ���������� �ű�� ����ü�� z����� ���������� ȸ��
����ü�� �ٴڸ��� ���� �̵�
*/

void Draw_Robot();
void main(int argc, char** argv)
{
	swing = false;
	Open = false;
	Door_angle = 0;
	moveX = -5;
	moveY = 0;
	moveZ = -70;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	RemoveHiddenSurface = false;
	Curling = false;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, Timer, 1);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
	gluLookAt(
		0, 0, 0,
		0.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);
	if (RemoveHiddenSurface == true) {
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	if (Curling == true)
	{
		glEnable(GL_CULL_FACE);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
	DrawArea();
	Draw_Door();
	Draw_Robot();
	glutSwapBuffers();

}

GLvoid reshape(int w, int h)    // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	// ���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- ������ ���� ���� �Ǵ� ���� ���� �� �� ���� �����Ѵ�. // 1. Ŭ���� ���� ����: ���� ������ ��� 
	gluPerspective(10.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -50.0); // ���� ������ ȭ�� �������� �̵��Ͽ� �þ߸� Ȯ���Ѵ�. 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		robot_dir = 1;
		break;
	case GLUT_KEY_LEFT:
		robot_dir = 3;
		break;
	case GLUT_KEY_DOWN:
		robot_dir = 2;
		break;
	case GLUT_KEY_UP:
		robot_dir = 4;
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (Open == false) {
			Open = true;
		}
		else
		{
			Open = false;
		}
		break;
	case 'j':
		jump = true;
		break;
	case 'h':
		if (RemoveHiddenSurface == false)
			RemoveHiddenSurface = true;
		else
			RemoveHiddenSurface = false;
		break;
	case 'w':
		moveZ++;
		break;
	case 's':
		moveZ--;
		break;
	case 'a':
		moveX++;
		break;
	case 'd':
		moveX--;
		break;
	case '-':
		moveY++;
		break;
	case '=':
		moveY--;
		break;
	case 'x':
		xAngle++;
		break;
	case 'y':
		yAngle++;
		break;
	case 'z':
		zAngle++;
		break;
	case 'X':
		xAngle--;
		break;
	case 'Y':
		yAngle--;
		break;
	case 'Z':
		zAngle--;
		break;
	case 'i':
		moveX = -5;
		moveY = 0;
		moveZ = -70;
		xAngle = 10;
		yAngle = 0;
		zAngle = 0;
		robot_dir = 0;
		robot_angle = 0;
		rx = 0;
		ry = 0;
		Open = false;
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	if (jump == true)
	{
		jtime++;
		if (jtime <= 10)
		{
			jumpY+=0.3;
		}
		else if (jtime>10&&jtime<=20)
		{
			jumpY -= 0.3;
		}
		else
		{
			jtime = 0;
			jump = false;
		}
	}
	if (robot_dir == 1)
	{
		robot_angle = 90;
		if(rx<4.5)
			rx += 0.1;
	}
	else if (robot_dir == 4)
	{
		robot_angle = 180;
		if (ry>-4.5)
			ry -= 0.1;
	}
	else if (robot_dir == 3)
	{
		robot_angle = 270;
		if(rx>-4.5)
		rx -= 0.1;
	}
	else if (robot_dir == 2)
	{
		robot_angle = 360;
		if (ry<4.5)
			ry += 0.1;
	}
	if (Open == true) {
		if (Door_angle < 90)
		{
			Door_angle +=5;
		}
	}
	else
	{
		if (Door_angle > 0)
		{
			Door_angle -= 5;
		}
	}
	if (swing == false) {
			swingAngle+=5;
		if (swingAngle > 45)
		{
			swing = true;
		}
	}
	else
	{
			swingAngle-=5;
		if (swingAngle < -45)
		{
			swing = false;
		}
	}
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}
void DrawArea()
{
	glBegin(GL_QUADS);
	glColor3f(0.5, 0, 0);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 0, 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 10, 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(0, 10, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5, 0.2, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 10, 10);
	glVertex3f(0, 10, 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0.3, 0.1);
	glVertex3f(0, 0, 10);
	glVertex3f(10, 0, 10);
	glVertex3f(10, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();
}

void Draw_Door()
{
	glPushMatrix();
	glTranslatef(0, 0, 10);
	glRotatef(Door_angle, 1, 0, 0);
	glTranslatef(0, 0, -10);
	glBegin(GL_QUADS);
	glColor3f(1, 0.5, 0.5);
	glVertex3f(0, 0, 10);
	glVertex3f(10, 0, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(0, 10, 10);
	glEnd();

	glPopMatrix();
}

void Draw_Robot()
{
	glPushMatrix();
	glTranslatef(rx, 0, ry);
	glTranslatef(5, jumpY, 5);
	glRotatef(robot_angle, 0, 1, 0);
	glTranslatef(-5, 0, -5);
	{	glPushMatrix(); //����

		glColor3f(1, 0, 0);
		glTranslatef(5, 1.5, 5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{	
	glPushMatrix(); //����
	glColor3f(1, 0, 1);
	glTranslatef(4.2, 1.5, 5);
	glTranslatef(0, 0.5, 0);
	glRotatef(swingAngle, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	glScalef(0.5, 1, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	}
	{
		glPushMatrix(); //������
		glColor3f(1, 1, 0);
		glTranslatef(5.8, 1.5, 5);
		glTranslatef(0, 0.5, 0);
		glRotatef(-swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //�޴ٸ�
		glColor3f(1, 0, 1);
		glTranslatef(4.5, 0.5, 5);
		glTranslatef(0, 0.5, 0);
		glRotatef(-swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //�����ٸ�
		glColor3f(1, 1, 0);
		glTranslatef(5.5, 0.5, 5);
		glTranslatef(0, 0.5, 0);
		glRotatef(swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{	
	glPushMatrix(); //��
	glColor3f(0, 0, 1);
	glTranslatef(5, 2.5, 5);
	glScalef(0.7, 0.7, 0.7);
	glutSolidCube(1);
	glPopMatrix();
	}
	{
		glPushMatrix(); //��
		glColor3f(0.3, 1, 0);
		glTranslatef(5, 2.5, 5.5);
		glScalef(0.2, 0.2, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
}