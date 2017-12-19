/*
실습 21 (다양한 객체) 배경에서 가운데에 피라미드(삼각형을 이용하여 그리기)를 그리고 그 주위를 지구가, 지구 주위를 달이 공전한다.
–화면의 좌우에 조명을 각각 1개씩 놓는다.
•각각의 조명의 색을 다르게 설정한다.
–명령어
•A/a: 광원의 ambient light를 높게 / 낮게
•D/d: 광원의 diffuse light를 높게 / 낮게
•S/s: 광원의 specular light를 높게 / 낮게

•1: 1번 조명을 켠다 / 끈다.
•2: 2번 조명을 켠다 / 끈다.
–조명의 위치에 작은 콘을 그려 조명을 표시한다.
*/
#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

struct Snow {
	double x, y, z;
	double speed;
};

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void Draw_Light();
void keyboard(unsigned char key, int x, int y);
void DrawPyramid();
void Draw_Snow();
void Earth();
int rotateX, rotateY, rotateZ;
int wheelAngle;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
int angle;
int angle2;

//애니메이션 관련 변수들
int ani_time;//애니메이션의 주된 타임

bool normalOn;
bool On1, On2,On3,On4;

GLfloat AmbientLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명

GLfloat lightPos1[] = { -2.5,2,-2.5,1 }; // 조명위치 1
GLfloat lightPos2[] = { 2.5,2,-2.5,1}; // 조명위치 2
GLfloat lightPos3[] = { -2.5,2,2.5,1 }; // 조명위치 3
GLfloat lightPos4[] = { 2.5,2,2.5,1 }; // 조명위치 4
Snow s[300];
void main(int argc, char** argv)
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 300; i++)
	{
		s[i].x = rand() % 1000 * 0.004-2;
		s[i].y = rand() % 1000 * 0.001+1;
		s[i].z = rand() % 1000 * 0.004-2;
		s[i].speed = rand()%1000*0.0001+0.01;
	}
	On1 = false;
	On2 = false;
	On3 = false;
	On4 = false;
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	angle = 0;
	wheelAngle = 0;
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
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);

	glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos4);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// 조명
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix(); {
		glMatrixMode(GL_MODELVIEW);
		glColor3f(1, 1, 0);
		/*
		glBegin(GL_QUAD_STRIP);
		glVertex3f(2, 0, -2);
		glVertex3f(2, 0, 2);
		glVertex3f(-2, 0, -2);
		glVertex3f(-2, 0, 2);
		glEnd();
		*/
		glPushMatrix();
		glScalef(3, 0.01, 3);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1, 0, 0);
		DrawPyramid(); 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(1, 0, 0);
		DrawPyramid();
		glPopMatrix();
		Draw_Snow();

	}
	glPopMatrix();
	// 위의 두 줄은 아래의 두 줄과 같은 결과이다
	// glRotatef (45.0, 0.0, 0.0, 1.0);과 같은 결과                  // glutWireTeapot (1.0); 
	glDisable(GL_DEPTH_TEST);
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
	default:
		break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'n':
		if (normalOn == false) {
			normalOn = true;
			printf("On\n");
		}
		else {
			normalOn = false;
			printf("OFF\n");
		}
		break;
	case '1':
		if (On1 == false) {
			glEnable(GL_LIGHT0);
			On1 = true;
		}
		else {
			glDisable(GL_LIGHT0);
			On1 = false;
		}
		break;
	case '2':
		if (On2 == false) {
			glEnable(GL_LIGHT1);
			On2 = true;
		}
		else {
			glDisable(GL_LIGHT1);
			On2 = false;
		}
		break;
	case '3':
		if (On3 == false) {
			glEnable(GL_LIGHT2);
			On3 = true;
		}
		else {
			glDisable(GL_LIGHT2);
			On3 = false;
		}
		break;
	case '4':
		if (On4 == false) {
			glEnable(GL_LIGHT3);
			On4 = true;
		}
		else {
			glDisable(GL_LIGHT3);
			On4 = false;
		}
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
		moveZ = 10;
		xAngle = 10;
		yAngle = 0;
		zAngle = 0;
		ani_time = 0;
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	for (int i = 0; i < 300; i++)
	{
		s[i].y-=s[i].speed;
	}
	for (int i = 0; i < 300; i++)
	{
		if (s[i].y < 0)
		{
			s[i].y = 2;
		}
	}
	angle += 10;
	angle2 += 15;

	ani_time++;
	if (ani_time < 50)
	{
		moveZ += 0.3;
	}
	else if (ani_time > 50 && ani_time<411)
	{
		yAngle += 3;
	}
	else if (ani_time >= 411 && ani_time < 460)
	{
		moveZ -= 0.3;
	}
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}
void DrawPyramid()
{
	glPushMatrix(); {
		glTranslatef(0, 0.5, 0);
		glScalef(0.5, 0.5, 0.5);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 1.0f);
		if (normalOn == true) {
			glNormal3f(0, 1, 0);
			glEnable(GL_NORMALIZE);
		}
		else
		{
			glDisable(GL_NORMALIZE);
		}
		glVertex3f(0.0f, 1.0f, 0.0f); // { Front }
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
		glVertex3f(1.0f, -1.0f, 1.0f); // { Front }

		if (normalOn == true) {
			glNormal3f(0, 1, 0);
			glEnable(GL_NORMALIZE);
		}
		else
		{
			glDisable(GL_NORMALIZE);
		}

		glVertex3f(0.0f, 1.0f, 0.0f); // { Right }
		glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
		glVertex3f(1.0f, -1.0f, -1.0f); // { Right }

		if (normalOn == true) {
			glNormal3f(0, 1, 0);
			glEnable(GL_NORMALIZE);
		}
		else
		{
			glDisable(GL_NORMALIZE);
		}

		glVertex3f(0.0f, 1.0f, 0.0f); // { Back }
		glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }

		if (normalOn == true) {
			glNormal3f(0, 1, 0);
			glEnable(GL_NORMALIZE);
		}
		else
		{
			glDisable(GL_NORMALIZE);
		}

		glVertex3f(0.0f, 1.0f, 0.0f); // { Left }
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }
		glEnd();
		glPopMatrix();
	}
	Earth();
}

void Earth()
{
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glTranslatef(1 * sin(2 * angle*3.141592 / 180), 0, 1 * cos(2 * angle*3.141592 / 180));
	glColor3f(0, 1, 0);
	glutSolidSphere(0.2, 20, 20);

	glPushMatrix(); {
		glColor3f(0, 0, 1);
		glTranslatef(0.3 * sin(2 * angle2*3.141592 / 180), 0, 0.3 * cos(2 * angle2*3.141592 / 180));
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
}

void Draw_Snow()
{
	for (int i = 0; i < 300; i++) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(s[i].x, s[i].y, s[i].z);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
}