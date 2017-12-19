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
void DrawOrbit(int rad); //궤도 그리기
void keyboard(unsigned char key, int x, int y);
bool SphereCollide(double x1, double y1, double z1, double x2, double y2, double z2, double rad1, double rad2);
void DrawWheel();
void DrawTree1();
void DrawTree2();
void DrawBuilding1();
void DrawBuilding2();
void DrawDoor();
void Plane();
int rotateX, rotateY, rotateZ;
int wheelAngle;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
int secondangleX; // 두번째 사각형의 각도
int secondangleZ; // 두번째 사각형의 각도
int thirdangleX; // 세번쨰 사각형의 각도
int thirdangleZ; // 세번쨰 사각형의 각도
int k;
double T1angle;
double T2num;
double B2num;
int p2angle;
int Pangle;
int p1angle;
struct Coordinates {
	double x, y, z;
	double rad;
};

Coordinates B[5]; // 건물들의 좌표값
Coordinates F; // 포크레인의 좌표값
Coordinates S; // 구의 좌표값

void main(int argc, char** argv)
{
	F.x = -2;
	F.y = 0;
	F.z = 0;
	F.rad = 0.2;
	B[0].x = 1.5;
	B[0].y = 0;
	B[0].z = -1.5;
	B[0].rad = 0.1;
	B[1].x = -1.5;
	B[1].y = 0;
	B[1].z = -1.5;
	B[1].rad = 0.1;
	B[2].x = 1.5;
	B[2].y = 0;
	B[2].z = 1.5;
	B[2].rad = 0.1;
	B[3].x = -1.5;
	B[3].y = 0;
	B[3].z = 1.5;
	B[3].rad = 0.1;
	B[4].x = 0;
	B[4].y = 0;
	B[4].z = 0;
	B[4].rad = 0.1;

	T1angle = 0;
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
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
	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	DrawOrbit(3);
	glPopMatrix();
	ForkCrane();
	DrawTree1();
	DrawTree2();
	DrawBuilding1();
	DrawBuilding2();
	DrawDoor();
	Plane();
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
		for (int i = 0; i < 5; i++)
		{
			if (SphereCollide(B[i].x, B[i].y, B[i].z, F.x, F.y, F.z, B[i].rad, F.rad))
			{
				F.x += 0.5;
			}
		}
		F.x -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		for (int i = 0; i < 5; i++)
		{
			if (SphereCollide(B[i].x, B[i].y, B[i].z, F.x, F.y, F.z, B[i].rad, F.rad))
			{
				F.x -= 0.5;
			}
		}
		F.x += 0.1;
		break;
	case GLUT_KEY_UP:
		for (int i = 0; i < 5; i++)
		{
			if (SphereCollide(B[i].x, B[i].y, B[i].z, F.x, F.y, F.z, B[i].rad, F.rad))
			{
				F.z += 0.5;
			}
		}
		F.z -= 0.1;
		break;
	case GLUT_KEY_DOWN:
		for (int i = 0; i < 5; i++)
		{
			if (SphereCollide(B[i].x, B[i].y, B[i].z, F.x, F.y, F.z, B[i].rad, F.rad))
			{
				F.z -= 0.5;
			}
		}
		F.z += 0.1;
		break;
	case GLUT_KEY_END:
		break;
	default:
		break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'k':
		p1angle++;
		break;
	case 'K':
		p1angle--;
		break;
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
	k+=5;
	Pangle+=5;
	p2angle += 15;
	T1angle += 3;
	if (k<10)
	{
		T2num = 1 + 0.05*k;
	}
	else if (10 <= k&&k < 15)
	{
		T2num -= 0.05*(k - 11);
	}
	else {
		k = 0;
	}

	if (k<10)
	{
		B2num = 0.05*k;
	}
	else if (10 <= k&&k < 20)
	{
		B2num = -0.05*(k - 10);
	}
	else {
		k = 0;
	}
	wheelAngle += 3;
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void ForkCrane()
{
	glPushMatrix();
	glTranslatef(F.x, 0.25, F.z);
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
	glutWireTorus(0.05, 0.1, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.25, -0.25);
	glRotatef(wheelAngle, 0, 0, 1);
	glutWireTorus(0.05, 0.1, 10, 10);
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
	glTranslatef(0, 0.3, 0);
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
	glutWireSphere(0.3, 30, 30);
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
	glTranslatef(0, T2num - 1, 0);
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
	glColor3f(0, 1, 0);
	glRotatef(270, 1, 0, 0);
	glScalef(1 + B2num, 1 + B2num, 1 + B2num);
	glutWireCone(0.5, 0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1 - B2num, 1 - B2num, 1 - B2num);
	glutWireCone(0.5, 0.5, 20, 20);
	glPopMatrix();
	glPopMatrix();
}
void DrawDoor()
{
	glPushMatrix();
	glRotatef(T1angle, 0, 1, 0);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-0.2, 0.2, 0);
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

bool SphereCollide(double x1, double y1, double z1, double x2, double y2, double z2, double rad1, double rad2) //구와 구의 충돌
{
	if (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2)) < rad1 + rad2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Plane()
{
	glPushMatrix();
	glTranslatef(3 * sin(Pangle*3.141592 / 180), 0, 3 * cos(Pangle*3.141592 / 180));
	glRotatef(Pangle, 0, 1, 0); //y축으로 빙글빙글 돔
	glColor3f(1, 0, 0);
	glPushMatrix(); {
		glTranslatef(0, 2.5, 0);
		glRotatef(p1angle, 1, 0, 0);
		glScalef(0.5, 0.25, 0.25);
		glutSolidCube(1.5);
	}
	glPopMatrix();

	glColor3f(0, 0, 1);
	glPushMatrix(); {
		glTranslatef(0.4, 2.5, 0);
		glScalef(0.1, 0.1, 0.1);
		glutSolidCube(1.5);
	}
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix(); {
		glTranslatef(0.5, 2.5, 0);
		glRotatef(p2angle, 1, 0, 0);
		glScalef(0.1, 0.1, 0.5);
		glutSolidCube(1.5);
	}
	glPopMatrix();

	glPushMatrix(); {
		glTranslatef(-0.4, 2.5, 0);
		glRotatef(p1angle, 1, 0, 0);
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslatef(-0.3, 0, 0.3);
		glScalef(0.2 + B2num, 0.2 + B2num, 0.2 + B2num);
		glutSolidCube(0.5);
	}
	glPopMatrix();

	glPushMatrix(); {
		glColor3f(1, 0, 1);
		glTranslatef(-0.6, 0, 0.3);
		glScalef(0.1 + B2num, 0.1 + B2num, 0.1 + B2num);
		glutSolidCube(0.5);
		}
	glPopMatrix();

		glPushMatrix(); {
			glColor3f(1, 0, 1);
			glTranslatef(-0.3, 0, -0.3);
			glScalef(0.2 + B2num, 0.2 + B2num, 0.2 + B2num);
			glutSolidCube(0.5);
		}
		glPopMatrix();

		glPushMatrix(); {
			glColor3f(1, 0, 1);
			glTranslatef(-0.6, 0, -0.3);
			glScalef(0.1 + B2num, 0.1 + B2num, 0.1 + B2num);
			glutSolidCube(0.5);
		}
		glPopMatrix();

	glScalef(0.1, 0.1, 0.5);
	glColor3f(1, 1, 0);
	glutSolidCube(1.5);
	glPopMatrix();

	glPopMatrix();
}


void DrawOrbit(int rad) //궤도 그리기
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	for (int i = 0; i < 360; i++)
	{
		glVertex3f(rad*sin(i*3.141592 / 180), 0, rad*cos(i*3.141592 / 180));
	}
	glEnd();
}


