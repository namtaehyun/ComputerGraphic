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
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void DrawBall();
int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
void DrawArea();
bool RemoveHiddenSurface;
bool Curling;
void Collide();
bool click;
double X1, Y1;
double X2, Y2;
void MoveCube();
struct Cube {
	double x, y, z;
	double rad;
};
struct Ball {
	double x, y,z;
	double R, G, B;
	bool isTrue;
	double xMoveMent; //x�̵��Ÿ�
	double yMoveMent; //y�̵��Ÿ�
	double zMoveMent; //z�̵��Ÿ�
	double xdir;      //x����
	double ydir;	  //y����
	double zdir;	  //z����
	Ball()
	{
		R = rand() % 100*0.01;
		G = rand() % 100 * 0.01;
		B = rand() % 100 * 0.01;
		isTrue = false;
		x = rand() % 10;
		y = rand() % 10;
		z = rand() % 10;
		xMoveMent = (rand() % 10+1) * 0.1;
		yMoveMent = (rand() % 10 + 1) * 0.1;
		zMoveMent = (rand() % 10 + 1)*0.1;
		xdir = 1;
		ydir = 1;
		zdir = 1;
	}
};
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

int idx;
Ball B[5];
Cube C[3];

void main(int argc, char** argv)
{

	C[0].x = 1;
	C[0].y = 0.5;
	C[0].z = 5;
	C[0].rad = 0.5;
	C[1].x = 3;
	C[1].y = 1;
	C[1].z = 5;
	C[1].rad = 1;
	C[2].x = 7;
	C[2].y = 1.5;
	C[2].z = 5;
	C[2].rad = 1.5;
	idx = 0;
	B[idx].isTrue = true;
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
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
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
	DrawBall();
	DrawCube();
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
	case GLUT_KEY_LEFT:
		if (RemoveHiddenSurface == false)
			RemoveHiddenSurface = true;
		else
			RemoveHiddenSurface = false;
		break;
	case GLUT_KEY_RIGHT:
		if (Curling == false)
			Curling = true;
		else
			Curling = false;
		break;
	default:
		break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
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
	case 'b':
		idx++;
		B[idx].isTrue = true;
		break;
	case 'i':
		moveX = 0;
		moveY = 0;
		moveZ = 0;
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	Collide();
	if (click == true && X2 < X1)
	{
		zAngle+=3;
	}
	else if (click == true && X2 > X1)
	{
		zAngle-=3;
	}
	MoveCube();

	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void Collide()
{
	for (int i = 0; i < 5; ++i)
	{
		if (B[i].isTrue == true) 
		{
			B[i].x += B[i].xdir*B[i].xMoveMent;
			B[i].y += B[i].ydir*B[i].yMoveMent;
			B[i].z += B[i].zdir*B[i].zMoveMent;
			if (B[i].x > 9)
			{
				B[i].xdir = -1;
				B[i].xMoveMent = (rand() % 10+1) * 0.1;
			}
			if (B[i].x < 1)
			{
				B[i].xdir = 1;
				B[i].xMoveMent = (rand() % 10 + 1) * 0.1;
			}
			if (B[i].y < 1)
			{
				B[i].ydir = 1;
				B[i].yMoveMent = (rand() % 10 + 1) * 0.1;
			}
			if (B[i].y >9)
			{
				B[i].ydir = -1;
				B[i].yMoveMent = (rand() % 10 + 1) * 0.1;
			}
			if (B[i].z >9)
			{
				B[i].zdir = -1;
				B[i].zMoveMent = (rand() % 10 + 1) * 0.1;
			}
			if (B[i].z <0)
			{
				B[i].zdir = 1;
				B[i].zMoveMent = (rand() % 10 + 1) * 0.1;
			}
		}
	}
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
	glColor3f(0, 0.5, 0.5);
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

void DrawBall()
{
	for (int i = 0; i < 5; i++)
	{
		if (B[i].isTrue == true) {
			glPushMatrix();
			glColor3f(B[i].R, B[i].G, B[i].B);
			glTranslatef(B[i].x, B[i].y, B[i].z);
			glutSolidSphere(0.5, 50, 50);
			glPopMatrix();
		}
	}
}


//���鿡���� �߷¿
// x=mgsin(theta)
// y=mgcos(theta)
void DrawCube()
{
	glPushMatrix();
	{
		glPushMatrix();
		glTranslatef(C[0].x, C[0].y, C[0].z);
		glColor3f(1, 0.5, 1);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(C[1].x, C[1].y, C[1].z);
		glColor3f(0.5, 0.5, 0);
		glutSolidCube(2);
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(C[2].x, C[2].y, C[2].z);
		glColor3f(0.3, 0.2, 0);
		glutSolidCube(3);
		glPopMatrix();
	}
	glPopMatrix();
}
void MoveCube()
{
	
	if (zAngle>0&&zAngle < 90)
	{
		for (int i = 0; i < 3; i++)
		{
			if (C[i].x < 10) {
				C[i].x -= sin(zAngle);
			}
		}
	}

	if (zAngle<0 && zAngle > -90)
	{
		for (int i = 0; i < 3; i++)
		{
			if (C[i].x > 0) {
				C[i].x += sin(zAngle);
			}
		}
	}
	printf("%f", zAngle);
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		X1 = (double)(x - 350) / 350;
		Y1 = (double)(-y + 350) / 350;
		click = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		click = false;
	}
	glutPostRedisplay();

}
void Motion(int x, int y)
{
	if (click == true)
	{
		X2 = (double)(x - 350) / 350;
		Y2 = (double)(-y + 350) / 350;
	}
}