#include<glut.h>
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void SetupRC(); //초기회
void RenderScene(void);
void ChangeSize(int w, int h);
void keyboard(unsigned char key, int x, int y);//키보드
float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;//로테이션
float xSolidRotation = 0.0f, ySolidRotation = 0.0f, zSolidRotation = 0.0f;//솔리드 로테이션
float xWireRotation = 0.0f, yWireRotation = 0.0f, zWireRotation = 0.0f;//와이어 로테이션
float xTranslation = 0.0f;//이동
float Scale = 1.0f;//크기

void WireCone();
void SolidCone();
void WireSphere();
void SolidSphere();
void WireTeapot();
void SolidTeapot();

int randNum = 0;//랜덤숫자
void coordinate();//좌표축
void solidCube();
void wireCube();
int shape;


int main(int argc, char* argv[])
{
	shape = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(500, 500); // 윈도우의 크기 지정
	glutCreateWindow("실습-16");
	//콜백함수
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyboard);
	SetupRC();//초기화
	glutMainLoop();
	return 0;
}

void SetupRC()//초기화
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear 색상을 검정색으로 설정
}
void RenderScene()//그리기
{
	glClear(GL_COLOR_BUFFER_BIT);
	coordinate();//좌표축 그리기
	glPushMatrix();//전체 좌표계
		glTranslated(0.0, 0.0, -300.0);//모델좌표계 이동 
		glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
		glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
		glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
		//회전
			glPushMatrix();//바닥 
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
	glPopMatrix();//전체 좌표계
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)//키보드
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
void ChangeSize(int w, int h)//윈도위 크기 변경
{
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);
	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 500.0);
	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void coordinate()//좌표축
{
	//X축
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.1f, 0.0f, -1.0f);
	glEnd();
	//Y축
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.1f, -1.0f);
	glEnd();
	//Z축
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();
}
void solidCube()
{
	glPushMatrix();//왼쪽 상자 
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
	glPushMatrix();//오른쪽 상자 
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

	glPushMatrix();//오른쪽 상자 
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

	glPushMatrix();//오른쪽 상자 
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
	glPushMatrix();//왼쪽 상자 
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
	glPushMatrix();//오른쪽 상자 
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
