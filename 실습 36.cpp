#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <math.h>
#include <Windows.h>
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);

void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m);
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc);
void Draw_Haemuk();
int moving, startx, starty, count = 0;
void Draw_HOSU();
void Draw_Rect();

int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
int time;
int angle;
int n;

void initTextures();
void Draw_Big_Wheel();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint textures[6];
GLfloat ctrlpoints[4][4][3] = //[i][2][]
{ { { -2.0, 0.0, 2.0 },{ -1.0, 0.5, 2.0 },{ 1.0, 0.0, 2.0 },{ 2.0, 0.0, 2.0 } },
{ { -2.0, 0.0, 1.0 },{ -1.0, 0.5, 1.0 },{ 1.0, 0.0, 1.0 } ,{ 2.0, 0.0, 1.0 } },
{ { -2.0, 0.0, -1.0 },{ -1.0, 0.5, -1.0 },{ 1.0, 0.0, -1.0 },{ 2.0, 0.0, -1.0 } },
{ { -2.0, 0.0, -2.0 },{ -1.0, 0.5, -2.0 },{ 1.0, 0.0, -2.0 },{ 2.0, 0.0, -2.0 } } };
GLfloat v[4][3] = { { 0.0,-0.5,1.0 },{ 0.0,0.5,0.0 },
{ -1.0,-0.5,0.0 },{ 1.0,-0.5,0.0 } };
GLfloat colors[4][3] = { { 1.0,0.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },{ 0.0,0.0,0.0 } };

GLfloat AmbientLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명

GLfloat lightPos1[] = { 5,4,5,1 }; // 조명위치 1

void main(int argc, char** argv)
{
	moveX = 0;
	moveY = 0;
	moveZ = -10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	angle = -45;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);
	initTextures();
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

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHT0);
	{
		glPushMatrix();
		glTranslatef(-5, 0, -5);
		glEnable(GL_TEXTURE_2D);
		{
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glColor3f(1, 1, 1);
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
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0, 0.5, 2);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0], v[1], v[2], v[3], n);
	glEnd();
	glPopMatrix();
	Draw_HOSU();
	Draw_Big_Wheel();
	Draw_Haemuk();
	Draw_Rect();
	glDisable(GL_LIGHTING);
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
	case GLUT_KEY_UP:
		for (int i = 0; i < 4; i++)
		{
			ctrlpoints[i][1][1]++;
		}
		break;
	case GLUT_KEY_DOWN:
		for (int i = 0; i < 4; i++)
		{
			ctrlpoints[i][1][1]--;
			ctrlpoints[i][2][1]++;
		}
		break;
	case GLUT_KEY_LEFT:
		for (int i = 0; i < 4; i++)
		{
			ctrlpoints[i][2][1]++;
		}
		break;
	case GLUT_KEY_RIGHT:
		for (int i = 0; i < 4; i++)
		{
			ctrlpoints[i][2][1]--;
		}
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
	time++;
	if (time%180 < 90)
	{
		angle++;
	}
	else
	{
		angle--;
	}
	n = n% 4 + 1;
	if (time % 4 == 0)
	{
		for (int i = 0; i < 4; i++) {
			ctrlpoints[i][1][1]--;
			ctrlpoints[i][2][1]++;
		}
	}
	else if(time%4==1)
	{
		for (int i = 0; i < 4; i++) {
			ctrlpoints[i][1][1]--;
			ctrlpoints[i][2][1]++;
		}
	}
	else if (time % 4 == 2)
	{
		for (int i = 0; i < 4; i++) {
			ctrlpoints[i][1][1]++;
			ctrlpoints[i][2][1]--;
		}
	}
	else
	{
		for (int i = 0; i < 4; i++) {
			ctrlpoints[i][1][1]++;
			ctrlpoints[i][2][1]--;
		}
	}

	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void Draw_HOSU()
{


	{
		//호수
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2, 0, 2.5);
		glScalef(0.1, 0.1, 2);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(4, 0, 2.5);
		glScalef(0.1, 0.1, 2);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(3, 0, 3.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.1, 0.1, 2);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(3, 0, 1.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.1, 0.1, 2);
		glutSolidCube(1);
		glPopMatrix();
		{
			glPushMatrix();
			glTranslatef(3, 0, 2.5);
			glScalef(0.5, 0.5, 0.5);
			glColor3f(0, 0, 1);
			glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &ctrlpoints[0][0][0]);
			glEnable(GL_MAP2_VERTEX_3);
			// 그리드를 이용한 곡면 드로잉
			glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
			// 선을 이용하여 그리드 연결
			glEvalMesh2(GL_LINE, 0, 10, 0, 10);
			glColor3f(0.0, 0.0, 1.0);
			glPopMatrix();
		}
	}
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
	glGenTextures(1, textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

	glBindTexture(GL_TEXTURE_2D, textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
	pBytes = LoadDIBitmap("floor.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 550, 557, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glColor3fv(colors[count % 4]);
	triangle(a, b, c);
	glColor3fv(colors[(count + 1) % 4]);
	triangle(a, c, d);
	glColor3fv(colors[(count + 2) % 4]);
	triangle(a, d, b);
	glColor3fv(colors[(count + 3) % 4]);
	triangle(b, d, c);
}

void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{
	GLfloat mid[6][3];
	int j;
	if (m>0)
	{	/*compute six midpoints*/
		for (j = 0; j<3; j++) mid[0][j] = (a[j] + b[j]) / 2;
		for (j = 0; j<3; j++) mid[1][j] = (a[j] + c[j]) / 2;
		for (j = 0; j<3; j++) mid[2][j] = (a[j] + d[j]) / 2;
		for (j = 0; j<3; j++) mid[3][j] = (b[j] + c[j]) / 2;
		for (j = 0; j<3; j++) mid[4][j] = (c[j] + d[j]) / 2;
		for (j = 0; j<3; j++) mid[5][j] = (b[j] + d[j]) / 2;

		divide_tetra(a, mid[0], mid[1], mid[2], m - 1);
		divide_tetra(mid[0], b, mid[3], mid[5], m - 1);
		divide_tetra(mid[1], mid[3], c, mid[4], m - 1);
		divide_tetra(mid[2], mid[5], mid[4], d, m - 1);
	}
	else
		tetra(a, b, c, d);      //draw triangle at end of recursion//
}

void Draw_Big_Wheel()
{
	glPushMatrix();
	{
		glColor3f(0, 1, 0);
		glTranslatef(4, 1.5, -5);
		glRotatef(180, 1, 0, 0);
		glutSolidTorus(0.1,1.5, 20, 20);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(4, 1.5, -5);		
		for (int i = 0; i < 8; i++)
		{
			glColor3f(0, 0, 1);
			glPushMatrix();
			glTranslatef(1.5*cos(time*3.141592 / 180+i*0.8), 1.5*sin(time*3.141592 / 180 + i*0.8), 0);
			glutSolidCube(0.5);
			glPopMatrix();
		}
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(4, 1.5, -5);
		for (int i = 0; i < 8; i++)
		{
			glPushMatrix();
			glRotatef(45*i+time, 0, 0, 1);
			glScalef(0.1, 5, 0.1);
			glColor3f(1, 0, 0);
			glutSolidCube(0.5);
			glPopMatrix();
		}
	}
	glPopMatrix();

}

void Draw_Haemuk()
{
	{
		glPushMatrix();
		glTranslatef(-2.5, 1.5, -2.5);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(2.5, -1.5, 2.5);
		glPointSize(5);
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(-2.5, 1.5, -2.5);
		glVertex3f(-2.0, 0.5, -2.5);
		glVertex3f(-2.5, 1.5, -2.5);
		glVertex3f(-3.0, 0.5, -2.5);
		glEnd();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0.5, -2.5);
		if (time%180 < 90)
		{
			{
				glPushMatrix();
				glTranslatef(0, 0.2, 0);
				glScalef(0.2, 0.2, 0.2);
				glColor3f(1, 1, 1);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();
			}
			{
				glPushMatrix();
				glTranslatef(0, 0.5, 0);
				glScalef(0.2, 0.2, 0.2);
				glColor3f(1, 1, 1);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();
			}
		}
		glColor3f(1, 0, 0);
		glScalef(1.5, 0.1, 1.5);
		glutSolidCube(1);
		glPopMatrix();
		glPopMatrix();
	}

	{
		glPushMatrix();
		glTranslatef(2.5, 0, 0);
		glPushMatrix();
		glTranslatef(-2.5, 1.5, -2.5);
		glRotatef(-angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(2.5, -1.5, 2.5);
		glPointSize(5);
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(-2.5, 1.5, -2.5);
		glVertex3f(-2.0, 0.5, -2.5);
		glVertex3f(-2.5, 1.5, -2.5);
		glVertex3f(-3.0, 0.5, -2.5);
		glEnd();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0.5, -2.5);
		if (time % 180 > 90)
		{
			{
				glPushMatrix();
				glTranslatef(0, 0.2, 0);
				glScalef(0.2, 0.2, 0.2);
				glColor3f(1, 1, 1);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();
			}
			{
				glPushMatrix();
				glTranslatef(0, 0.5, 0);
				glScalef(0.2, 0.2, 0.2);
				glColor3f(1, 1, 1);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();
			}
		}
		glColor3f(1, 0, 0);
		glScalef(1.5, 0.1, 1.5);
		glutSolidCube(1);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}
}

void Draw_Rect()
{
	glPushMatrix();
	glTranslatef(-2.5, 0.5, 2.5);
	glRotatef(time, 0, 1, 0);
	glColor3f(1, 1, 0);
	glutSolidCube(0.5);
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glPushMatrix();
	glColor4f(1, 0, 0, 0.6);
	glTranslatef(-2.5, 0.5, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_BLEND);
}