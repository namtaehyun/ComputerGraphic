#include <glut.h>
#include <stdio.h>    // �Ǵ� <GL/freeglut.h>
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

int rotateX, rotateY, rotateZ;
int time;
int wheelAngle;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
bool rl;
int angle; // ��ũ������ ����
int secondangleX; // �ι�° �簢���� ����
int secondangleZ; // �ι�° �簢���� ����
int thirdangleX; // ������ �簢���� ����
int thirdangleZ; // ������ �簢���� ����
double Fx; // ��ũ������ �¿�� �Դٰ����ؾ��Ѵ�.
void main(int argc, char** argv)
{
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
	glPopMatrix();
	// ���� �� ���� �Ʒ��� �� �ٰ� ���� ����̴�.
	// glRotatef (45.0, 0.0, 0.0, 1.0);�� ���� ���                  // glutWireTeapot (1.0); 
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
		xAngle = 10;
		yAngle = 0;
		zAngle = 0;
		break;
	}
	printf("%f %f %f\n", xAngle, yAngle, zAngle);
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	time++;
	if (time<=80)
	{
		rl = true;
		Fx+=0.05;
	}
	else if(time>80&&time<=160) {
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
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void ForkCrane()
{
			glPushMatrix();
			glTranslatef(Fx-2, 0.25, 0);
			glRotatef(angle, 0, 1, 0);
			glColor3f(1, 0, 0);
			glutSolidCube(0.5);
			DrawWheel();
				glPushMatrix();
					glColor3f(0, 1, 0);
					glTranslatef(-0.15, 0.2, -0.15);
					glRotatef(secondangleX, 1, 0, 0);
					glRotatef(secondangleZ, 0, 0, 1);
					DrawCuboid(0.3,0.4,0.3);
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
	glTranslatef(0,-0.25,0.25);
	glRotatef(wheelAngle, 0, 0, 1);
	glutWireTorus(0.2, 0.2, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.25, -0.25);
	glRotatef(wheelAngle, 0, 0, 1);
	glutWireTorus(0.2, 0.2, 20, 20);
	glPopMatrix();
}