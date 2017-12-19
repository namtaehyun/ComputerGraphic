#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <math.h>
GLvoid drawScene(GLvoid);
void ForkCrane();
void DrawCuboid(double x, double y, double z);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
void DrawCenter();
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
void DrawWheel();
void DrawTree1();
void DrawTree2();
void DrawBuilding1();
void DrawBuilding2();
void DrawDoor();

int time;
bool rl;
int rotateX, rotateY, rotateZ;
int wheelAngle;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
int angle; // 포크레인의 각도
int secondangleX; // 두번째 사각형의 각도
int secondangleZ; // 두번째 사각형의 각도
int thirdangleX; // 세번쨰 사각형의 각도
int thirdangleZ; // 세번쨰 사각형의 각도
double Fx; // 포크레인은 좌우로 왔다갔다해야한다.
int k;
double T1angle;
double T2num;
double B2num;
void main(int argc, char** argv)
{
	T1angle = 0;
	Fx = 0;
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	angle = 0;
	wheelAngle = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
	glClear(GL_COLOR_BUFFER_BIT);
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
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1, 1, 1);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(2, 0, -2);
	glVertex3f(2, 0, 2);
	glVertex3f(-2, 0, -2);
	glVertex3f(-2, 0, 2);
	glEnd();
	ForkCrane();
	DrawTree1();
	DrawTree2();
	DrawBuilding1();
	DrawBuilding2();
	DrawDoor();
	glPopMatrix();
	// 위의 두 줄은 아래의 두 줄과 같은 결과이다
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


void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Fx -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		Fx += 0.1;
		break;
	case GLUT_KEY_END:
		angle++;
		break;
	default:
		break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'n':
		secondangleX++;
		break;
	case 'N':
		secondangleX--;
		break;
	case 'm':
		secondangleZ++;
		break;
	case 'M':
		secondangleZ--;
		break;
	case 'b':
		thirdangleX++;
		break;
	case 'B':
		thirdangleX--;
		break;
	case 'l':
		thirdangleZ++;
		break;
	case 'L':
		thirdangleZ--;
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

	if (time <= 80)
	{
		rl = true;
		Fx += 0.05;
	}
	else if (time>80 && time <= 160) {
		rl = false;
		Fx -= 0.05;
	}
	else
	{
		time = 0;
	}
	if (rl == true)
	{
		wheelAngle += 10;
	}
	else
	{
		wheelAngle -= 10;
	}
	k++;
	T1angle+=3;
	if (k<10)
	{
		T2num = 1 + 0.05*k;
	}
	else if (10 <= k&&k < 15)
	{
		T2num -=0.05*(k-11);
	}
	else {
		k = 0;
	}

	if (k<10)
	{
		B2num =0.05*k;
	}
	else if (10 <= k&&k < 20)
	{
		B2num = -0.05*(k-10);
	}
	else {
		k = 0;
	}



	printf("%d", k);
	wheelAngle += 3;
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void ForkCrane()
{
	glPushMatrix();
	glTranslatef(Fx - 2, 0.25, 0);
	glRotatef(angle, 0, 1, 0);
	glColor3f(1, 0, 0);
	glutSolidCube(0.5);
	DrawWheel();
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-0.15, 0.2, -0.15);
	glRotatef(secondangleX, 1, 0, 0);
	glRotatef(secondangleZ, 0, 0, 1);
	DrawCuboid(0.3, 0.4, 0.3);
	glPushMatrix();
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0.075, 0.3, 0.075);
	glRotatef(thirdangleX, 1, 0, 0);
	glRotatef(thirdangleZ, 0, 0, 1);
	DrawCuboid(0.15, 0.6, 0.15);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void DrawCuboid(double x, double y, double z)
{
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, z); //1
	glVertex3f(x, 0, z); //3
	glVertex3f(x, 0, 0); //2
	glVertex3f(0, 0, 0); //4
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, y, z); //5
	glVertex3f(0, y, 0); //6
	glVertex3f(x, y, 0); //7
	glVertex3f(x, y, z); //8
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(x, 0, z); //3
	glVertex3f(x, 0, 0); //2
	glVertex3f(x, y, 0); //7
	glVertex3f(x, y, z); //8
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, z); //1
	glVertex3f(x, 0, z); //3
	glVertex3f(x, y, z); //8
	glVertex3f(0, y, z); //5
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, z); //1
	glVertex3f(0, 0, 0); //4
	glVertex3f(0, y, 0); //6
	glVertex3f(0, y, z); //5
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0); //4
	glVertex3f(0, y, 0); //6
	glVertex3f(x, y, 0); //7
	glVertex3f(x, 0, 0); //2
	glEnd();
}

void DrawWheel()
{
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(0, -0.25, 0.25);
	glRotatef(wheelAngle, 0, 0, 1);
	glutWireTorus(0.2, 0.2, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.25, -0.25);
	glRotatef(wheelAngle, 0, 0, 1);
	glutWireTorus(0.2, 0.2, 20, 20);
	glPopMatrix();
}

void DrawTree1()
{
	glPushMatrix();
	glTranslatef(1.5, 0, -1.5);
	glPushMatrix();
	glColor3f(0.60, 0.45, 0.12);
	glTranslatef(0, 0.5, 0);
		glScalef(1, 2, 1);
		glutSolidCube(0.5);
			glPushMatrix();
			glColor3f(0, 1, 0);
				glTranslatef(0,0.3,0);
				glRotatef(T1angle, 0, 1, 0);
				glScalef(2, 0.5, 1);
				glutWireCube(0.5);
			glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void DrawTree2()
{
	glPushMatrix();
	glTranslatef(-1.5, 0, -1.5);
		glPushMatrix();
			glColor3f(0.60, 0.45, 0.12);
			DrawCuboid(0.4, 0.6, 0.4);
				glPushMatrix();
					glTranslatef(0.2, 0.4, 0.2);  //신축
					glScalef(T2num, T2num, T2num);
					glColor3f(0, 1, 0);
					glutWireSphere(0.3,30,30);
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void DrawBuilding1()
{
	glPushMatrix();
	glTranslatef(1.5, 0, 1.5);
	glPushMatrix();
		glColor3f(0.60, 0.45, 0.12);
		DrawCuboid(0.4, 0.6, 0.4);
			glPushMatrix();
				glTranslatef(0.2, 0.5, 0.2); 
				glTranslatef(0, T2num-1, 0);
				glColor3f(0, 1, 0);
				glRotatef(90, 1, 0, 0);
				glutWireTorus(0.1, 0.3, 20, 20);
			glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void DrawBuilding2()
{
	glPushMatrix();
	glTranslatef(-1.5, 0, 1.5);
	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(270, 1, 0, 0);
	glScalef(1+B2num, 1 + B2num, 1 + B2num);
	glutWireCone(0.5, 0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1-B2num, 1-B2num, 1-B2num);
	glutWireCone(0.5, 0.5, 20, 20);
	glPopMatrix();
	glPopMatrix();
}
void DrawDoor()
{	glPushMatrix();
	glRotatef(T1angle, 0, 1, 0);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-0.2,0.2,0);
	glScalef(1, 2, 1);
	glutSolidCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0.2, 0.2, 0);
	glScalef(1, 2, 1);
	glutSolidCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 0.4, 0);
	glScalef(3, 1, 1);
	glutSolidCube(0.2);
	glPopMatrix();

	glPopMatrix();
}