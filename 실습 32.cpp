#include <glut.h>
#include <stdio.h>    // �Ǵ� <GL/freeglut.h>
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
//ī�޶�
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
GLuint textures[6];
void initTextures();
//�ؽ�ó
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
	glTranslatef(0.0, 0.0, -viewdepth);//���콺�� ȭ�� z�� �̵�
	glRotatef(-viewhorizontal, 1.0, 0.0, 0.0);//���콺�� ȭ�� x�� �̵�
	glRotatef(viewvertical, 0.0, 1.0, 0.0);//���콺�� ȭ�� y�� �̵� 
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

GLvoid reshape(int w, int h)    // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	// ���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- ������ ���� ���� �Ǵ� ���� ���� �� �� ���� �����Ѵ�. // 1. Ŭ���� ���� ����: ���� ������ ��� 
	gluPerspective(10.0f, w / h, 1.0, 20000);
	glTranslatef(0.0, 0.0, -50.0); // ���� ������ ȭ�� �������� �̵��Ͽ� �þ߸� Ȯ���Ѵ�. 
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
	glBegin(GL_QUADS);//�ո� ����ü
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
	glBegin(GL_QUADS);//�޸� ����ü
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
	glBegin(GL_QUADS);//���� ����ü
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
	glBegin(GL_QUADS);//�Ʒ��� ����ü
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
		glBegin(GL_QUADS);//���� ����ü 1
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
		glBegin(GL_QUADS);//���� ����ü 1
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
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
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
	glGenTextures(6, textures); //�ؽ�ó �̸��� �����Ѵ�. n:�����Ǿ���� �ؽ�ó�̸��� �� 

	glBindTexture(GL_TEXTURE_2D, textures[0]); // �ؽ�ó�� �� ��ü�� �ؽ�ó�� �������ش�.
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

