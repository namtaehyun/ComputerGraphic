#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <cmath>
#include <stdlib.h>
#include <Windows.h>
#define Gravity 0.98
#define RAD_TO_ANGLE 180/3.141592
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
//
bool RightButtonDown;
bool LeftButtonDown;
int downX;
int downY;
float viewvertical;
float viewhorizontal;
float viewdepth;
//카메라
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint textures[6];
void initTextures();
//텍스처
int angle;
void Draw_Box();

bool CollideCheck(double x1, double y1, double z1, double x2, double y2, double z2, double r1, double r2);
int time;
void main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);
	initTextures();
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, Timer, 1);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -viewdepth);//마우스로 화면 z축 이동
	glRotatef(-viewhorizontal, 1.0, 0.0, 0.0);//마우스로 화면 x축 이동
	glRotatef(viewvertical, 0.0, 1.0, 0.0);//마우스로 화면 y축 이동 
	gluLookAt(
		0, 0, 0,
		0.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glRotatef(30, 1, 1, 0);
	glRotatef(angle, 0, 1, 0);
	Draw_Box();
	glPopMatrix();
	glutSwapBuffers();

}

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. // 1. 클리핑 공간 설정: 원근 투영인 경우 
	gluPerspective(10.0f, w / h, 1.0, 20000);
	glTranslatef(0.0, 0.0, -50.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다. 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_DOWN:
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
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	angle++;
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
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
void Draw_Box()
{
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glPushMatrix();
	glScalef(5, 5, 5);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);//앞면 육면체
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2, 0.2, 0.2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2, -0.2, 0.2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.2, -0.2, 0.2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.2, 0.2, 0.2);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);//뒷면 육면체
	{
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.2, 0.2, -0.2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.2, -0.2, -0.2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2, -0.2, -0.2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2, 0.2, -0.2);
	}
	glEnd();
	//////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);//윗면 육면체
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2, 0.2, -0.2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.2, 0.2, 0.2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.2, 0.2, 0.2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.2, 0.2, -0.2);
	}
	glEnd();
	//////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);//아랫면 육면체
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2, -0.2, -0.2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2, -0.2, 0.2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.2, -0.2, 0.2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.2, -0.2, -0.2);
	}
	glEnd();


	glBindTexture(GL_TEXTURE_2D, textures[4]);
	{
		glBegin(GL_QUADS);//옆면 육면체 1
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2, 0.2, -0.2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2, -0.2, -0.2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.2, -0.2, 0.2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.2, 0.2, 0.2);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	{
		glBegin(GL_QUADS);//옆면 육면체 1
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.2, 0.2, 0.2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.2, -0.2, 0.2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.2, -0.2, -0.2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.2, 0.2, -0.2);
		glEnd();
	}
	glPopMatrix();
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


void initTextures()
{
	glGenTextures(6, textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

	glBindTexture(GL_TEXTURE_2D, textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
	pBytes = LoadDIBitmap("Yee_boss.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes = LoadDIBitmap("wall1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes = LoadDIBitmap("wall2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	pBytes = LoadDIBitmap("Box4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	pBytes = LoadDIBitmap("Box5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	pBytes = LoadDIBitmap("Box6.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

