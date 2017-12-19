#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <cmath>
#include <stdlib.h>
#define Gravity 0.98
#define RAD_TO_ANGLE 180/3.141592
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
void Draw_Light();
void DrawPyramid();
void Draw_Field();
int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
double swingAngle;
bool swing;
int robot_dir;
int robot_angle;
GLfloat rx, rz;
bool jump;
int jtime;
double jumpY;
double p_s,p_x,p_z;
bool RightButtonDown;
bool LeftButtonDown;
int downX;
int downY;
float viewvertical;
float viewhorizontal;
float viewdepth;

bool CollideCheck(double x1, double y1, double z1, double x2, double y2, double z2, double r1, double r2);
GLfloat AmbientLight[]={ 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat DiffuseLight[]={ 1.0f, 0.0f, 1.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 
GLfloat SpotLight_Vect[] = { 0,-1,0};
GLfloat Spot_CutOff[] = { 30 };
GLfloat Spot_Exponent[] = {1};
GLfloat lightPos[] =   { 0,5,0,1 }; // 조명위치 1
struct Snow {
	double x, y, z;
	double speed;
};

struct Particle {
	double x, y, z;
};
int time;
bool spark_on;
bool snow_On;
bool spot_light_On;
Particle p[360];
Snow s[300];
void Draw_Snow();
void Draw_Particle();
void Draw_Robot();
void main(int argc, char** argv)
{
	spot_light_On = false;
	rx = 0;
	rz = 0;
	for (int i = 0; i < 300; i++)
	{
		s[i].x = rand() % 1000 * 0.01;
		s[i].y = rand() % 1000 * 0.01 ;
		s[i].z = rand() % 1000 * 0.01;
		s[i].speed = rand() % 1000 * 0.0001 + 0.01;
	}
	swing = false;
	moveX = -5;
	moveY = 0;
	moveZ = -70;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	p_s = 2;
	p_x = 5;
	p_z = 5;
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotLight_Vect);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Spot_CutOff);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, Spot_Exponent);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	if (spot_light_On == true) {
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	Draw_Light();
	Draw_Robot();
	Draw_Field();
	DrawPyramid();
	if (spark_on == true) {
		Draw_Particle();
	}
	if(snow_On==true){
	Draw_Snow();
	}
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
	case GLUT_KEY_RIGHT:
		robot_dir = 1;
		break;
	case GLUT_KEY_LEFT:
		robot_dir = 3;
		break;
	case GLUT_KEY_DOWN:
		robot_dir = 2;
		break;
	case GLUT_KEY_UP:
		robot_dir = 4;
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (spot_light_On == true)
		{
			spot_light_On = false;
		}
		else
		{
			spot_light_On = true;
		}
		break;
	case '2':
		if (snow_On == true)
		{
			snow_On = false;
		}
		else
		{
			snow_On = true;
		}
		break;
	case '3':
		if (spark_on == true)
		{
			spark_on = false;
		}
		else
		{
			spark_on = true;
		}
		break;
	case 'j':
		jump = true;
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
		moveX = -5;
		moveY = 0;
		moveZ = -70;
		xAngle = 10;
		yAngle = 0;
		zAngle = 0;
		robot_dir = 0;
		robot_angle = 0;
		rx = 0;
		rz = 0;
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	time++;
	lightPos[0] = rx;
	lightPos[2] = rz;
	if (spark_on == true) {
		for (int i = 0; i < 360; i++)
		{
			p[i].x += sin(i*RAD_TO_ANGLE)*0.5;
			p[i].z += cos(i*RAD_TO_ANGLE)*0.5;
		}
		if (time % 20 == 0)
		{
			for (int i = 0; i < 360; i++)
			{
				p[i].x = rx;
				p[i].z = rz;
			}
		}
	}
	printf("%f %f\n", rx,rz);
	for (int i = 0; i < 300; i++)
	{
		s[i].y -= s[i].speed;
	}
	for (int i = 0; i < 300; i++)
	{
		if (s[i].y < 0)
		{
			s[i].y = 10;
		}
	}
	if (jump == true)
	{
		jtime++;
		if (jtime <= 10)
		{
			jumpY += 0.3;
		}
		else if (jtime>10 && jtime <= 20)
		{
			jumpY -= 0.3;
		}
		else
		{
			jtime = 0;
			jump = false;
		}
	}
	if (robot_dir == 1)
	{
		robot_angle = 90;
	
		if (rx<10)
				if (rz > p_z - p_s&&rz < p_z + p_s
					&&p_x + p_s>rx&&p_x - p_s - 0.1<rx)
				{
				}else
				rx += 0.1;
	}
	else if (robot_dir == 4)//zUP
	{
		robot_angle = 180;
		if (rz>0)
			if (rx > p_x - p_s&&rx < p_x + p_s
				&&p_z+p_s+0.1>rz&&p_z - p_s<rz)
			{
			}
			else
				rz -= 0.1;
	}
	else if (robot_dir == 3)
	{
		robot_angle = 270;
		if (rx>0)
			if (rz > p_z - p_s&&rz < p_z + p_s
				&&p_x+p_s+0.1>rx&&p_x-p_s<rx)
			{
			}
			else
				rx -= 0.1;
	}
	else if (robot_dir == 2) //zDOWN
	{
		robot_angle = 360;
		if (rz<10)
			if (rx > p_x - p_s&&rx < p_x + p_s
				&&p_z + p_s>rz&&p_z - p_s-0.1<rz)
			{
			}
			else
				rz += 0.1;
	}
	if (swing == false) {
		swingAngle += 5;
		if (swingAngle > 45)
		{
			swing = true;
		}
	}
	else
	{
		swingAngle -= 5;
		if (swingAngle < -45)
		{
			swing = false;
		}
	}
	glutTimerFunc(10, Timer, 1);
	glutPostRedisplay();
}

void Draw_Robot()
{
	glPushMatrix();
	glTranslatef(rx, jumpY, rz);
	glRotatef(robot_angle, 0, 1, 0);
	{	glPushMatrix(); //몸통

	glColor3f(1, 0, 0);
	glTranslatef(0, 1.5, 0);
	glutSolidCube(1);
	glPopMatrix();
	}
	{
		glPushMatrix(); //왼팔
		glColor3f(1, 0, 1);
		glTranslatef(-0.8, 1.5, 0);
		glTranslatef(0, 0.5, 0);
		glRotatef(swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //오른팔
		glColor3f(1, 1, 0);
		glTranslatef(0.8, 1.5, 0);
		glTranslatef(0, 0.5, 0);
		glRotatef(-swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //왼다리
		glColor3f(1, 0, 1);
		glTranslatef(-0.5, 0.5, 0);
		glTranslatef(0, 0.5, 0);
		glRotatef(-swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //오른다리
		glColor3f(1, 1, 0);
		glTranslatef(0.5, 0.5, 0);
		glTranslatef(0, 0.5, 0);
		glRotatef(swingAngle, 1, 0, 0);
		glTranslatef(0, -0.5, 0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //얼굴
		glColor3f(0, 0, 1);
		glTranslatef(0, 2.5, 0);
		glScalef(0.7, 0.7, 0.7);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix(); //코
		glColor3f(0.3, 1, 0);
		glTranslatef(0, 2.5, 0.5);
		glScalef(0.2, 0.2, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
}


void Draw_Field()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			glPushMatrix();
			glTranslatef(i,0,j);
			glScalef(1, 0.1, 1);
			glutSolidSphere(1, 10, 10);
			glPopMatrix();
		}
	}
}

void DrawPyramid()
{
	glPushMatrix(); {
		glTranslatef(p_x,1,p_z);
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
}

void Draw_Snow()
{
	for (int i = 0; i < 300; i++) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(s[i].x, s[i].y, s[i].z);
		glScalef(0.5, 0.5, 0.5);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
}

bool CollideCheck(double x1, double y1, double z1, double x2, double y2, double z2, double r1, double r2)
{
	if (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2)) < r1 + r2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Draw_Light()
{
	/*GLfloat lightPos1[] = {-2,1,0,1}; // 조명위치 1
	GLfloat lightPos2[] = { 2,1,0,1 }; // 조명위치 2
	*/
	glPushMatrix(); {
		glColor3f(0, 1, 0);
		glNormal3f(0, 1, 0);
		glTranslatef(rx, 5, rz);
		glRotatef(270, 1, 0, 0);
		glutSolidCone(0.25, 0.5, 20, 20);
	}
	glPopMatrix();
}
void Draw_Particle()
{
	for (int i = 0; i < 360; i++)
	{
		glPushMatrix();
		glTranslatef(p[i].x, 1, p[i].z);
		glScalef(0.05, 0.05, 0.05);
		glutSolidCube(1);
		glPopMatrix();
	}
}
void Mouse(int button, int state, int x, int y)
{
	downX = x; downY = y;
	LeftButtonDown = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	RightButtonDown = ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN));
	glutPostRedisplay();

}
void Motion(int x, int y) {

	if (LeftButtonDown)
	{
		viewvertical += (float)(x - downX) / 4.0;
		viewhorizontal += (float)(downY - y) / 3.0;
	} // rotate
	if (RightButtonDown)
	{
		viewdepth += (float)(downY - y) / 25.0;
	} // scale
	downX = x;
	downY = y;
	glutPostRedisplay();
}