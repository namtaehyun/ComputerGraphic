#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <math.h>
GLvoid drawScene(GLvoid);

void DrawSphere();
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void DrawCenter();
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
int x;
int goState;
int angle;
int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double ex, ey, ez;
int angle1, angle2, angle3;
double movex, movey, movez;
double moveX, moveY, moveZ;
void main(int argc, char** argv)
{
	goState = 5;
	movex = 0;
	movey = 0;
	movez = 0;
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	x = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, Timer, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
	gluLookAt(
		0,0,0,
		0.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1, 1, 1);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(2,0,-2);
	glVertex3f(2, 0, 2);
	glVertex3f(-2, 0, -2);
	glVertex3f(-2, 0, 2);
	glEnd();
	glPopMatrix();
	DrawSphere();
	// 위의 두 줄은 아래의 두 줄과 같은 결과이다.
	// glRotatef (45.0, 0.0, 0.0, 1.0);과 같은 결과                  // glutWireTeapot (1.0); 
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
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'l':
		// -100~100
		rotateX = 0;
		rotateY = 0;
		rotateZ = 1;
		goState = 1;
		break;
	case 'L':
		rotateX = 0;
		rotateY = 0;
		rotateZ = 1;
		goState = 2;
		break;
	case 'm':
		rotateX = 0;
		rotateY = 1;
		rotateZ = 0;
		goState = 0;
		break;
	case 'N':
		rotateX = 1;
		rotateY = 0;
		rotateZ = 0;
		goState = 3;
		break;
	case 'n':
		rotateX = 1;
		rotateY = 0;
		rotateZ = 0;
		goState = 4;
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
		moveX = 0;
		moveY = 0;
		moveZ = 0;
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
		break;
	}
	printf("%f %f %f\n", xAngle, yAngle, zAngle);
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	printf("%f", movez);
	if (goState == 1)
	{
		if (movex > -2)
		{
			movex -= 2 * 3.141592 * 0.5 / 180;
		}
		angle -= 10;
	}
	else if (goState == 2)
	{
		if (movex < 2)
		{
			movex += 2 * 3.141592 * 0.5 / 180;
		}
		angle += 10;
	}
	else if (goState == 3)
	{
		if (movez < 2)
		{
			movez += 2 * 3.141592 * 0.5 / 180;
		}
		angle += 10;
	}
	else if (goState == 4)
	{
		if (movez > -2)
		{
			movez -= 2 * 3.141592 * 0.5 / 180;
		}
		angle -= 10;
	}
	else if (goState == 0)
	{
		angle -= 10;
	}
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}


void DrawSphere()
{
	glPushMatrix();
	glTranslatef(movex, 0.5, movez);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glColor3f(1, 0, 0);
	GLUquadricObj * obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluSphere(obj, 0.5, 20, 20);
	glPopMatrix();
}