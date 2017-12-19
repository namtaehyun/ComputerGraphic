#include<glut.h>
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void SetupRC(); //�ʱ�ȸ
void RenderScene(void);
void ChangeSize(int w, int h);
void keyboard(unsigned char key, int x, int y);//Ű����
float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;//�����̼�
float xSolidRotation = 0.0f, ySolidRotation = 0.0f, zSolidRotation = 0.0f;//�ָ��� �����̼�
float xWireRotation = 0.0f, yWireRotation = 0.0f, zWireRotation = 0.0f;//���̾� �����̼�
float xTranslation = 0.0f;//�̵�
float Scale = 1.0f;//ũ��

void WireCone();
void SolidCone();
void WireSphere();
void SolidSphere();
void WireTeapot();
void SolidTeapot();

int randNum = 0;//��������
void coordinate();//��ǥ��
void solidCube();
void wireCube();
int shape;


int main(int argc, char* argv[])
{
	shape = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(500, 500); // �������� ũ�� ����
	glutCreateWindow("�ǽ�-16");
	//�ݹ��Լ�
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyboard);
	SetupRC();//�ʱ�ȭ
	glutMainLoop();
	return 0;
}

void SetupRC()//�ʱ�ȭ
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear ������ ���������� ����
}
void RenderScene()//�׸���
{
	glClear(GL_COLOR_BUFFER_BIT);
	coordinate();//��ǥ�� �׸���
	glPushMatrix();//��ü ��ǥ��
		glTranslated(0.0, 0.0, -300.0);//����ǥ�� �̵� 
		glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
		glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
		glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
		//ȸ��
			glPushMatrix();//�ٴ� 
				glTranslatef(0.0f, -50.0f, 0.0f);
				glColor3f(1.0f, 1.0f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(-100.0f, 0.0f, 100.0f);
				glVertex3f(100.0f, 0.0f, 100.0f);
				glVertex3f(100.0f, 0.0f, -100.0f);
				glVertex3f(-100.0f, 0.0f, -100.0f);
				glEnd();
			glPopMatrix();

		if (shape == 1)
		{
			solidCube();
			wireCube();
		}
		else if (shape == 2)
		{
			SolidCone();
			WireCone();
		}
		else if (shape == 3)
		{
			SolidSphere();
			WireSphere();
		}
		else if (shape == 4)
		{
			SolidTeapot();
			WireTeapot();
		}
	glPopMatrix();//��ü ��ǥ��
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)//Ű����
{
	switch (key)
	{
	case 'x':
		xRotation += 3.0f;
		break;
	case 'y':
		yRotation += 3.0f;
		break;
	case 'z':
		zRotation += 3.0f;
		break;
	case 'l':
		srand((unsigned)time(NULL));
		randNum = 1;
		switch (randNum)
		{
		case 0:
			xSolidRotation += 3.0f;
			break;
		case 1:
			ySolidRotation += 3.0f;
			break;
		case 2:
			zSolidRotation += 3.0f;
			break;
		}
		break;
	case 'r':
		srand((unsigned)time(NULL));
		randNum = 2;
		switch (randNum)
		{
		case 0:
			xWireRotation += 3.0f;
			break;
		case 1:
			yWireRotation += 3.0f;
			break;
		case 2:
			zWireRotation += 3.0f;
			break;
		}
		break;
	case '1':
		shape = 1;
		break;
	case '2':
		shape = 2;
		break;
	case '3':
		shape = 3;
		break;
	case '4':
		shape = 4;
		break;
	}
	glutPostRedisplay();
}
void ChangeSize(int w, int h)//������ ũ�� ����
{
	// �������� ���� ���� ����
	glViewport(0, 0, w, h);
	// ���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 500.0);
	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void coordinate()//��ǥ��
{
	//X��
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.1f, 0.0f, -1.0f);
	glEnd();
	//Y��
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.1f, -1.0f);
	glEnd();
	//Z��
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();
}
void solidCube()
{
	glPushMatrix();//���� ���� 
	glColor3f(1, 0, 0);
	glTranslatef(-30.0f, -30.0f, 0.0f);
	glRotatef(xSolidRotation, 1, 0, 0);
	glRotatef(ySolidRotation, 0, 1, 0);
	glRotatef(zSolidRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	glutSolidCube(50);
	glPopMatrix();
}
void wireCube()
{
	glPushMatrix();//������ ���� 
	glColor3f(0, 1, 0);
	glTranslatef(60.0f, -30.0f, 0.0f);
	glRotatef(xWireRotation, 1, 0, 0);
	glRotatef(yWireRotation, 0, 1, 0);
	glRotatef(zWireRotation, 0, 0, 1);

	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	glutWireCube(50);
	glPopMatrix();
}


void WireSphere()
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	glPushMatrix();//������ ���� 
	glColor3f(0, 1, 0);
	glTranslatef(60.0f, -30.0f, 0.0f);
	glRotatef(xWireRotation, 1, 0, 0);
	glRotatef(yWireRotation, 0, 1, 0);
	glRotatef(zWireRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluSphere(qobj, 25, 20, 20);
	glPopMatrix();
}

void SolidSphere()
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	glPushMatrix();//������ ���� 
	glColor3f(0, 1, 0);
	glTranslatef(-30.0f, -30.0f, 0.0f);
	glRotatef(xSolidRotation, 1, 0, 0);
	glRotatef(ySolidRotation, 0, 1, 0);
	glRotatef(zSolidRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	gluSphere(qobj, 25, 20, 20);
	glPopMatrix();
}

void WireCone()
{
	glPushMatrix(); 
	glColor3f(0, 1, 0);
	glTranslatef(60.0f, -50.0f, 0.0f);
	glRotatef(270, 1, 0, 0);
	glRotatef(xWireRotation, 1, 0, 0);
	glRotatef(yWireRotation, 0, 1, 0);
	glRotatef(zWireRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	glutWireCone(25, 50, 20, 20);
	glPopMatrix();
}

void SolidCone()
{
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-30.0f, -50.0f, 0.0f);
	glRotatef(270, 1, 0, 0);
	glRotatef(xSolidRotation, 1, 0, 0);
	glRotatef(ySolidRotation, 0, 1, 0);
	glRotatef(zSolidRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);

	glutSolidCone(25, 50, 20, 20);
	glPopMatrix();
}


void SolidTeapot()
{
	glPushMatrix();//���� ���� 
	glColor3f(1, 0, 0);
	glTranslatef(-30.0f, -30.0f, 0.0f);
	glRotatef(xSolidRotation, 1, 0, 0);
	glRotatef(ySolidRotation, 0, 1, 0);
	glRotatef(zSolidRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(50);
	glPopMatrix();
}
void WireTeapot()
{
	glPushMatrix();//������ ���� 
	glColor3f(0, 1, 0);
	glTranslatef(60.0f, -30.0f, 0.0f);
	glRotatef(xWireRotation, 1, 0, 0);
	glRotatef(yWireRotation, 0, 1, 0);
	glRotatef(zWireRotation, 0, 0, 1);
	glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
	glutWireTeapot(50);
	glPopMatrix();
}
