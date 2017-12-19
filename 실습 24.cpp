#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <math.h>

struct Torus {
	double y; // y좌표를 가짐.
	bool isTrue; // isTrue값이 1일때 보여줌.
	bool stacked; // 쌓였음을 나타냄.
};

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
void DrawPan();
int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
bool RemoveHiddenSurface;
void RingDraw();

Torus T[10];

//은면제거 On/Off
//컬링 On/Off
//쉐이딩 flat/smooth
//뒷면 yes/No = 뒷면을 닫는다. 뒷면을 연다.
//앞면 yes/No = 앞면을 닫는다. 앞면을 연다.
int idx;
int angle = 0;
void main(int argc, char** argv)
{
	idx = 0;
	for (int i = 0; i < 10; i++)
	{
		T[i].y = 2;
		T[i].isTrue = false;
		T[i].stacked = false;
	}
	T[0].isTrue = true;
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	RemoveHiddenSurface = false;
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
	DrawPan();
	RingDraw();
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
		if (RemoveHiddenSurface == false)
		{
			RemoveHiddenSurface = true;
		}
		else
		{
			RemoveHiddenSurface = false;
		}
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_UP:
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
	angle += 1;
	for (int i = 0; i < 10; i++) {
		if (T[i].stacked == false && T[i].isTrue == true)
		{
			T[i].y -= 0.1;
		}
	} // 시간이 지날때마다 내려오게함. 
	if (T[idx].y<0.2*idx+0.1&&idx<10)
	{
		T[idx].stacked = true;
		idx++;
		T[idx].isTrue = true;
	}
	else if (idx > 9)
	{
		idx = 0;
		for (int i = 0; i < 10; i++)
		{
			T[i].stacked = false;
			T[i].isTrue = false;
			T[i].y = 2;
		}
		T[0].isTrue = true;
	}
	

	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void DrawPan()
{
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-2, 0, 2);
	glVertex3f(-2, 0, -2);
	glVertex3f(2, 0, -2);
	glVertex3f(2, 0, 2);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glEnd();
}

void RingDraw()
{
	for (int i = 0; i < 10; i++) {
		if (T[i].isTrue == true) {
			glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(0, T[i].y, 0);
			glRotatef(90, 1, 0, 0);
			if (T[i].stacked == false) {
				glTranslatef(0.5*sin(angle), 0.5*cos(angle), 0);
			}
			glutWireTorus(0.1, 0.5, 20, 20);
			glPopMatrix();
		}
	}
}