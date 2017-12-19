/*
*/
#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
int rotateX, rotateY, rotateZ;
int wheelAngle;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
GLfloat fog_color[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat density = 0.7;
GLfloat start = 0.0;
GLfloat end = 50.0;
/*
GL_FOG_MODE: 안개 블렌드 인자, 초기값은 GL_EXP
(GL_LINEAR / GL_EXP / GL_EXP2)
GL_FOG_COLOR: 안개의 색, 초기값은 (0, 0, 0, 0)
(RGBA컬러를 나타내는 4개의 숫자로 된 배열)
GL_FOG_DENSITY: 안개 밀도, 0.0보다 큰 수로 설정, 초기값: 1
(fog mode가 GL_EXP, GL_EXP2일 경우 밀도의 설정이 가능) GL_FOG_START: world coordinate상에서 안개 시작 위치
(관측자로부터 안개 시작 거리, 세계좌표상의 z값, 초기값: 0)
GL_FOG_END: 는 world coordinate상에서 안개 끝 위치
(세계좌표상의 z값, 초기값: 1)
GL_FOG_START로 지정한 위치보다 가까이 있는 물체는 안개효과 를 사용하지 않는다.
GL_FOG_END로 지정한 위치보다 멀리 떨어짂 곳에 있는 물체는 안개효과를 최대로 사용한다.
*/
int mode;
void main(int argc, char** argv)
{
	srand(unsigned(time(NULL)));
	moveX = 0;
	moveY = 0;
	moveZ = 10;
	xAngle = 10;
	yAngle = 0;
	zAngle = 0;
	wheelAngle = 0;
	mode = 0;
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
	glClearColor(0.5, 0.5, 0.5, 1);
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
	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fog_color); // fog_color는 안개의 색을 의미한다. 
	glFogf(GL_FOG_START, start); // start는 world coordinate상에서 안개 시작 위치를 의미한다.
	glFogf(GL_FOG_END, end); // end는 world coordinate상에서 안개 끝 위치를 의미한다.
	/*
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogi(GL_FOG_MODE,GL_EXP);
	glFogi(GL_FOG_MODE,GL_EXP2);
	*/

	glFogf(GL_FOG_DENSITY, density);
	if (mode == 0) {
		glFogi(GL_FOG_MODE, GL_EXP);
		printf("EXP\n");
	}
	else if (mode == 1) {
		glFogi(GL_FOG_MODE, GL_EXP2);
		printf("EXP2\n");
	}
	else
	{
		glFogi(GL_FOG_MODE, GL_LINEAR);
		printf("Linear\n");
	}


	// 위의 두 줄은 아래의 두 줄과 같은 결과이다
	// glRotatef (45.0, 0.0, 0.0, 1.0);과 같은 결과                  // glutWireTeapot (1.0); 
	{
		glPushMatrix();
		glTranslatef(1.5, 0, 0);
		glColor4f(0, 0, 1,0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor4f(1, 0, 1, 0.5);
		glutSolidCube(1.5);
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(-1.5, 0, 0);
		glColor4f(0, 1, 1, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
	glDisable(GL_FOG);
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
	/*
	d/D: 포그의 density값을 올리기/내리기
•s/S: 포그의 시작 위치 올리기/내리기
•e/E: 포그의 끝 위치를 올리기/내리기
•M: 포그의 모드를 바꾸기*/
	switch (key)
	{
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
	case 'd':
		printf("%f", density);
		density+=0.01;
		break;
	case 'D':
		printf("%f", density);
		density -= 0.01;
		break;
	case 's':
		printf("%f", start);
		start += 1;
		break;
	case 'S':
		printf("%f", start);
		start -= 1;
		break;
	case 'e':
		printf("%f", end);
		end += 1;
		break;
	case 'E':
		printf("%f", end);
		end -= 1;
		break;
	case 'm':
		if (mode == 0)
		{
			mode = 1;
		}
		else if (mode == 1)
		{
			mode = 2;
		}
		else
		{
			mode = 0;
		}
		printf("%d", mode);
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}