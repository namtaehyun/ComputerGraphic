#include <glut.h>
#include <stdio.h>    // �Ǵ� <GL/freeglut.h>
#include <math.h>
GLvoid drawScene(GLvoid);

void DrawBallOne();
void DrawBallTwo();
void DrawBallThree();
void DrawOrbit(int rad); //�˵� �׸���
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void DrawCenter();
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
int x;
double xAngle, yAngle, zAngle;
int angle1,angle2,angle3;
double moveX, moveY, moveZ;
void main(int argc, char** argv)
{
	moveX = 0;
	moveY = 0;
	moveZ = 0;
	xAngle = 0;
	yAngle = 0;
	zAngle = 0;
	x = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);
	glutTimerFunc(100,Timer,1);
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
		0, 0, 0,
		0.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);
	glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		DrawCenter();
		DrawOrbit(3);
		DrawBallOne();
		DrawBallTwo();
		DrawBallThree();
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
	//-- ������ ���� ���� �Ǵ� ���� ���� �� �� ���� �����Ѵ�.  
	gluPerspective(10.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -50.0); // ���� ������ ȭ�� �������� �̵��Ͽ� �þ߸� Ȯ���Ѵ�. 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	angle1++;
	angle2 += 2;
	angle3 += 3;
	glutTimerFunc(10, Timer, 1);
	glutPostRedisplay();
}

void DrawCenter()
{
	obj = gluNewQuadric();   // ��ü �����ϱ�
	glColor3f(1, 0, 0);
	gluQuadricDrawStyle( obj, GLU_LINE );     
	gluQuadricNormals( obj, GLU_SMOOTH );   // ���� ���� 
	gluSphere( obj, 1, 50, 50 ); 
}


void DrawOrbit(int rad) //�˵� �׸���
{
	glBegin(GL_LINE_STRIP);
	glColor4f(1, 1, 1, 1.0f);
	for (int i = 0; i < 360; i++)
	{
		glVertex3f(rad*sin(i*3.141592 / 180), 0, rad*cos(i*3.141592 / 180));
	}
	glEnd();
}



void DrawBallOne()
{
	glPushMatrix();
		DrawOrbit(3);
		glColor3f(0, 0.5,0.3);
		glRotatef(angle1, 0, 1, 0);
		glTranslatef(3 * sin(angle1*3.141592 / 180), 0, 3 * cos(angle1*3.141592 / 180));
		obj = gluNewQuadric();   // ��ü �����ϱ�    
		gluQuadricDrawStyle(obj, GLU_LINE);
		gluQuadricNormals(obj, GLU_SMOOTH);   // ���� ���� 
		gluSphere(obj, 0.5, 30, 30);
		DrawOrbit(1);
		glPushMatrix();
		glColor3f(0.5, 0.3, 0.1);
			glTranslatef(1 * sin(2 * angle1*3.141592 / 180), 0, 1* cos(2 * angle1*3.141592 / 180));
			obj = gluNewQuadric();   // ��ü �����ϱ�    
			gluQuadricDrawStyle(obj, GLU_LINE);
			gluQuadricNormals(obj, GLU_SMOOTH);   // ���� ���� 
			gluSphere(obj, 0.25, 30, 30);
		glPopMatrix();
	glPopMatrix();
}


void DrawBallTwo()
{
	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	DrawOrbit(3);
	glColor3f(1, 0, 1);
	glRotatef(angle2, 0, 1, 0);
	glTranslatef(3 * sin(angle2*3.141592 / 180), 0, 3 * cos(angle2*3.141592 / 180));
	obj = gluNewQuadric();   // ��ü �����ϱ�    
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluQuadricNormals(obj, GLU_SMOOTH);   // ���� ���� 
	gluSphere(obj, 0.5, 30, 30);
	DrawOrbit(1);
	glPushMatrix();
	glColor3f(0.6, 0.2, 0.3);
	glTranslatef(1 * sin(2 * angle2*3.141592 / 180), 0, 1 * cos(2 * angle2*3.141592 / 180));
	obj = gluNewQuadric();   // ��ü �����ϱ�    
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluQuadricNormals(obj, GLU_SMOOTH);   // ���� ���� 
	gluSphere(obj, 0.25, 30, 30);
	glPopMatrix();
	glPopMatrix();
}


void DrawBallThree()
{
	glPushMatrix();
	glRotatef(-45, 0, 0, 1);
	DrawOrbit(3);
	glColor3f(1, 1, 0);
	glRotatef(angle3, 0, 1, 0);
	glTranslatef(3 * sin(angle3*3.141592 / 180), 0, 3 * cos(angle3*3.141592 / 180));
	obj = gluNewQuadric();   // ��ü �����ϱ�    
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluQuadricNormals(obj, GLU_SMOOTH);   // ���� ���� 
	gluSphere(obj, 0.5, 30, 30);
	DrawOrbit(1);
	glPushMatrix();
	glColor3f(0.5, 0.3, 0.8);
	glTranslatef(1 * sin(2 * angle3*3.141592 / 180), 0, 1 * cos(2 * angle3*3.141592 / 180));
	obj = gluNewQuadric();   // ��ü �����ϱ�    
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluQuadricNormals(obj, GLU_SMOOTH);   // ���� ���� 
	gluSphere(obj, 0.25, 30, 30);
	glPopMatrix();
	glPopMatrix();
}