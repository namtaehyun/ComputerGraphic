#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
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
/*실습 25
3차원 공튕기기
- 원근투영/은먼제거/컬링을 사용한다.
- 공을 튀길 공간을 평면을 이용하여 직육면체의 형태르 만든다.
각 면은 다른 색깔로 표현한다.
왼쪽 오른쪽 아래쪽 위쪽 뒤쪽의 면을 그린다.
실습 23은 육면체의 바깥쪽, 실습에서는 안쪽이 보이는 면이다.
공간 내부에서 공이 이동한다.
직육면체의 면에 공이 맞으면 방향을 바꿔서 이동을 한다.
바닥에 z축 따라 일렬로 다양한 크기의 육면체를 3개이상 갖는다.
- z축 따라서 회전하면 그에 따라서 육면체도 이동한다.
- 키보드 명령
z/Z z축으로 양/음 방향으로 이동
y/Y y축에 시계/반시계방향으로 회전
B : 볼이 새로 생겨서 튕기기 시작한다. ( 최대 5개)
m/M : 공간의 바닥면을 한칸씩 양/음방향으로 바꾼다.
- 마우스명령
마우스를 왼쪽으로 옮기면
육면체가 z축따라 왼쪽으로 회전
마우스를 오른쪽으로 옮기면 육면체가 z축따라 오른쪽으로 회전
육면체도 바닥면을 따라 이동
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

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. // 1. 클리핑 공간 설정: 원근 투영인 경우 
	gluPerspective(10.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -50.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다. 
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
	{	glPushMatrix(); //몸통

		glColor3f(1, 0, 0);
		glTranslatef(5, 1.5, 5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{	
	glPushMatrix(); //왼팔
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
		glPushMatrix(); //오른팔
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
		glPushMatrix(); //왼다리
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
		glPushMatrix(); //오른다리
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
	glPushMatrix(); //얼굴
	glColor3f(0, 0, 1);
	glTranslatef(5, 2.5, 5);
	glScalef(0.7, 0.7, 0.7);
	glutSolidCube(1);
	glPopMatrix();
	}
	{
		glPushMatrix(); //코
		glColor3f(0.3, 1, 0);
		glTranslatef(5, 2.5, 5.5);
		glScalef(0.2, 0.2, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
}