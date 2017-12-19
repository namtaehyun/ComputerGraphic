#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <cmath>
#include <stdlib.h>
#include <Windows.h>
#define Gravity 0.98
#define RAD_TO_ANGLE 180/3.141592
#define TEXTURE_NUMBER 2//텍스쳐 개수
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
void Draw_Light();
void DrawPyramid();
void Draw_Field();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint textures[TEXTURE_NUMBER];
void initTextures();

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
double p_s, p_x, p_z;
bool RightButtonDown;
bool LeftButtonDown;
int downX;
int downY;
float viewvertical;
float viewhorizontal;
float viewdepth;

bool CollideCheck(double x1, double y1, double z1, double x2, double y2, double z2, double r1, double r2);
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
Particle p[360];
Snow s[300];
void Draw_Snow();
void Draw_Particle();
void Draw_Robot();
void main(int argc, char** argv)
{
	rx = 0;
	rz = 0;
	for (int i = 0; i < 300; i++)
	{
		s[i].x = rand() % 1000 * 0.01;
		s[i].y = rand() % 1000 * 0.01;
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
	initTextures();
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
	glEnable(GL_DEPTH_TEST);
	if (snow_On == true) {
		Draw_Snow();
	}
	glEnable(GL_TEXTURE_2D);
	Draw_Robot();
	Draw_Field();
	DrawPyramid();
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
			}
			else
				rx += 0.1;
	}
	else if (robot_dir == 4)//zUP
	{
		robot_angle = 180;
		if (rz>0)
			if (rx > p_x - p_s&&rx < p_x + p_s
				&&p_z + p_s + 0.1>rz&&p_z - p_s<rz)
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
				&&p_x + p_s + 0.1>rx&&p_x - p_s<rx)
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
				&&p_z + p_s>rz&&p_z - p_s - 0.1<rz)
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
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(10, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(10, 0, 10);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 10);
	glEnd();
}

void DrawPyramid()
{
	glPushMatrix(); {
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTranslatef(p_x, 1, p_z);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5,1.0);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Front }
		glTexCoord2f(1, 0);
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
		glTexCoord2f(0, 0);
		glVertex3f(1.0f, -1.0f, 1.0f); // { Front }

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Right }
		glTexCoord2f(1, 0);
		glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
		glTexCoord2f(0, 0);
		glVertex3f(1.0f, -1.0f, -1.0f); // { Right }

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Back }
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Left }
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }
		glEnd();
		glPopMatrix();
	}
}

void Draw_Snow()
{
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	for (int i = 0; i < 300; i++) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(s[i].x, s[i].y, s[i].z);
		{
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glColor3f(1,1,1);
			glutSolidSphere(0.1, 20, 20);
		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
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



void initTextures()
{
	printf("d");
	glGenTextures(TEXTURE_NUMBER, textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

	glBindTexture(GL_TEXTURE_2D, textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
	pBytes = LoadDIBitmap("Pyramid.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 581, 594, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes = LoadDIBitmap("Earth.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1023, 757, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes = LoadDIBitmap("grass.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 275, 183, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
