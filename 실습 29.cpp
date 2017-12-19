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
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void Draw_Light();
void keyboard(unsigned char key, int x, int y);
void DrawTree1();
void DrawTree2();
void DrawBuilding1();
void DrawBuilding2();
void DrawPyramid();

void Earth();
int time;
int rotateX, rotateY, rotateZ;
int wheelAngle;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
int angle; 
int angle2;
int k;
double T1angle;
double T2num;
double B2num;

double amb_UPDOWN;
double dif_UPDOWN;
double spe_UPDOWN;

bool On1,On2;

GLfloat AmbientLight1[] = { 0.0f, 0.0f, 1.0f, 1.0f }; 
GLfloat DiffuseLight1[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명

GLfloat AmbientLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f }; 
GLfloat DiffuseLight2[] = { 1.0f, 0.0f, 1.0f, 1.0f }; 
GLfloat SpecularLight2[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명

GLfloat lightPos1[] = {-3,1,0,1}; // 조명위치 1
GLfloat lightPos2[] = { 3,1,0,1 }; // 조명위치 2

void main(int argc, char** argv)
{
	On1 = false;
	On2 = false;
	T1angle = 0;
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	amb_UPDOWN = 0;
	dif_UPDOWN = 0;
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
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	Draw_Light();
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1, 1, 1);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(2, 0, -2);
	glVertex3f(2, 0, 2);
	glVertex3f(-2, 0, -2);
	glVertex3f(-2, 0, 2);
	glEnd();
	DrawTree1();
	DrawTree2();
	DrawBuilding1();
	DrawBuilding2();
	DrawPyramid();
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
	case 'j':
		AmbientLight1[0] = amb_UPDOWN+= 0.1;
		AmbientLight2[0] = amb_UPDOWN+= 0.1;
		AmbientLight1[1] = amb_UPDOWN+= 0.1;
		AmbientLight2[1] = amb_UPDOWN+= 0.1;
		AmbientLight1[2] = amb_UPDOWN+= 0.1;
		AmbientLight2[2] = amb_UPDOWN+= 0.1;
		break;
	case 'k':
		DiffuseLight1[0] = dif_UPDOWN+=0.1;
		DiffuseLight1[1] = dif_UPDOWN+=0.1;
		DiffuseLight2[0] = dif_UPDOWN+=0.1;
		DiffuseLight2[1] = dif_UPDOWN+=0.1;
		break;
	case 'l':
		SpecularLight1[0] = spe_UPDOWN+=0.1;
		SpecularLight1[1] = spe_UPDOWN+=0.1;
		SpecularLight1[2] = spe_UPDOWN+=0.1;
		SpecularLight2[0] = spe_UPDOWN+= 0.1;
		SpecularLight2[1] = spe_UPDOWN+= 0.1;
		SpecularLight2[2] = spe_UPDOWN+= 0.1;
		break;
	case 'J':
		AmbientLight1[0] = amb_UPDOWN -= 0.1;
		AmbientLight2[0] = amb_UPDOWN -= 0.1;
		AmbientLight1[1] = amb_UPDOWN -= 0.1;
		AmbientLight2[1] = amb_UPDOWN -= 0.1;
		AmbientLight1[2] = amb_UPDOWN -= 0.1;
		AmbientLight2[2] = amb_UPDOWN -= 0.1;
		break;
	case 'K':
		DiffuseLight1[0] = dif_UPDOWN -= 0.1;
		DiffuseLight1[1] = dif_UPDOWN -= 0.1;
		DiffuseLight2[0] = dif_UPDOWN -= 0.1;
		DiffuseLight2[1] = dif_UPDOWN -= 0.1;
		break;
	case 'L':
		SpecularLight1[0] = spe_UPDOWN-= 1;
		SpecularLight1[1] = spe_UPDOWN-= 1;
		SpecularLight1[2] = spe_UPDOWN-= 1;
		SpecularLight2[0] = spe_UPDOWN-= 1;
		SpecularLight2[1] = spe_UPDOWN-= 1;
		SpecularLight2[2] = spe_UPDOWN-= 1;
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
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	k++;
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
	angle+=10;
	angle2 += 15;
	wheelAngle += 3;
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
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
	glPushMatrix(); {
		glTranslatef(1.5, 0, -1.5);
		glPushMatrix(); {
			glColor3f(0.60, 0.45, 0.12);
			glTranslatef(0, 0.5, 0);
			glScalef(1, 2, 1);
			glutSolidCube(0.5);
			glPushMatrix(); {
				glColor3f(0, 1, 0);
				glTranslatef(0, 0.3, 0);
				glRotatef(T1angle, 0, 1, 0);
				glScalef(2, 0.5, 1);
				glutSolidCube(0.5);
				glPopMatrix();
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void DrawTree2()
{
	glPushMatrix(); {
		glTranslatef(-1.5, 0, -1.5);
		glPushMatrix(); {
			glColor3f(0.60, 0.45, 0.12);
			glPushMatrix();
			{
				glTranslatef(0, 0.5, 0);
				glScalef(0.25, 1, 0.25);
				glutSolidCube(1);
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 1,0);  //신축
				glScalef(T2num, T2num, T2num);
				glColor3f(0, 1, 0);
				glutSolidSphere(0.3, 30, 30);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void DrawBuilding1()
{
	glPushMatrix(); {
		glTranslatef(1.5, 0, 1.5);
		glPushMatrix(); {
			glColor3f(0.60, 0.45, 0.12);
			glPushMatrix();
			{
				glTranslatef(0, 0.5, 0);
				glScalef(0.25, 1, 0.25);
				glutSolidCube(1);
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 0.5, 0);
				glTranslatef(0, T2num - 1, 0);
				glColor3f(0, 1, 0);
				glRotatef(90, 1, 0, 0);
				glutSolidTorus(0.1, 0.3, 20, 20);
				glPopMatrix();
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void DrawBuilding2()
{
	glPushMatrix();
	glTranslatef(-1.5, 0, 1.5);

	glPushMatrix(); {
		glColor3f(0, 1, 0);
		glRotatef(270, 1, 0, 0);
		glScalef(1 + B2num, 1 + B2num, 1 + B2num);
		glutSolidCone(0.5, 0.5, 20, 20);
		glPopMatrix();
	}
	glPushMatrix(); {
		glColor3f(1, 0, 0);
		glTranslatef(0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(1 - B2num, 1 - B2num, 1 - B2num);
		glutSolidCone(0.5, 0.5, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
}
void DrawPyramid()
{
	glPushMatrix(); {
		glTranslatef(0, 0.5, 0);
		glScalef(0.5, 0.5, 0.5);
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 1, 0);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Front }
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
		glVertex3f(1.0f, -1.0f, 1.0f); // { Front }

		glNormal3f(0, 1, 0);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Right }
		glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
		glVertex3f(1.0f, -1.0f, -1.0f); // { Right }

		glNormal3f(0, 1, 0);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Back }
		glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }

		glNormal3f(0, 1, 0);
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

void Draw_Light()
{
	/*GLfloat lightPos1[] = {-2,1,0,1}; // 조명위치 1
	GLfloat lightPos2[] = { 2,1,0,1 }; // 조명위치 2
	*/
	glPushMatrix(); {
		glColor3f(0, 1, 0);
		glTranslatef(-2, 1, 0);
		glRotatef(270, 0, 1, 0);
		glutSolidCone(0.25, 0.5, 20, 20);
	}
	glPopMatrix();

	glPushMatrix(); {
		glColor3f(1, 0, 0);
		glTranslatef(2, 1, 0);
		glRotatef(90, 0, 1, 0);
		glutSolidCone(0.25, 0.5, 20, 20);
	}
	glPopMatrix();
}