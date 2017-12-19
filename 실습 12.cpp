//위에꺼는 회전+이동
//밑에꺼는 이동만
//회전은 원일때만 적용해도됨.

/*
원의 경로를 따라 이동/회전하는 애니메이션 구현하기
– 오픈지엘 변환 함수를 사용한다.
– 화면 중앙에 좌표축이 그려진다.
– 좌표측의 원점을 중심으로 xy 평면에 원이 그려진다.
– 키보드 명령에 따라 선택된 도형이 원의 경로를 따라 회전 또는 이동하고 크기가 확 대→축소→확대 → …된다.
• 도형 종류: 삼각형, 사각형 – 또 키보드 명령어에 따라 경로 바꾸기
• 1: 사인 곡선
• 2: 회오리
• 3: 지그재그
• 4: 경로 그리기 (4번을 선택하면 왼쪽 마우스 클릭을 이용하여 직선 경로를 그리고,
오른쪽 마우스를 클릭하면 경로 그리기가 끝나고 삼각형이 경로를 따라 이동한다.
왼쪽 마우스는 최대 5번까지 클릭할 수 있다.)
*/
#include <math.h>
#include "Conversion.h"
#include <gl\GL.h>
#include <glut.h>
#include <stdio.h>    // 또는 <GL/freeglut.h>

struct Point
{
	bool isTrue;
	double x, y;
	Point() {
		isTrue = false;
	}
};

bool tr = false;
void Mouse(int button, int state, int x, int y);
GLvoid KeyBoardInput(unsigned char key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);

bool click =false;
int idx;
int k = 0;
int Shape = 0;
int Width, Height;
Point p[5]; // 다섯점을 잇는 직선그릴꺼임
void main(int argc, char** argv) {
	Width = 700;
	Height = 700;
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutTimerFunc(100, Timer, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyBoardInput);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()     // 출력 함수 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색을 'blue' 로 지정       
	glClear(GL_COLOR_BUFFER_BIT);   // 설정된 색으로 젂체를 칠하기      
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glEnd();

	glColor3f(1, 1, 0);

	if (tr == false)
	{
		if (Shape == 0) 
		{
			glPushMatrix();
			glRotatef(k, 0.0, 0.0, 1.0);
			glTranslatef(0.5, 0.0, 0.0);
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glRectf(-0.1, -0.1, 0.1, 0.1);
			glPopMatrix();
		}
		else if (Shape == 1)
		{
			glPushMatrix(); //push와 pop는 한쌍 스택구조
			glRotatef(0, 0.0, 0.0, 1.0); //회전행렬
			if (-0.5+k*0.01 < 0.5) {
				glTranslatef(-0.5 + k*0.01, sin(3.141592 / 7 * k)*0.1, 0.0); //이동행렬
			}
			else
			{
				glTranslatef(0.5, sin(3.141592 / 7 * 100)*0.1, 0.0); //이동행렬
			}
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glRectf(-0.1, -0.1, 0.1, 0.1);
			glPopMatrix();
		}
		else if (Shape == 2)
		{
			glPushMatrix();
//			glRotatef(0, 0.0, 0.0, 0.0);
			glTranslatef(0.0009*k*sin(k*3.141592 / 180), 0.0009*k*cos(k*3.141592 / 180), 0.0);
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glRectf(-0.1, -0.1, 0.1, 0.1);
			glPopMatrix();
//			glRectf(0.0009*k*sin(k*3.141592 / 180) - 0.1, 0.0009*k*cos(k*3.141592 / 180) - 0.1, 0.0009*k*sin(k*3.141592 / 180) + 0.1, 0.0009*k*cos(k*3.141592 / 180) + 0.1);
		}
		else if (Shape == 3)
		{
			glPushMatrix();
			glRotatef(0, 0.0, 0.0, 1.0);
			if (k < 11) {
				glTranslatef(-0.75 + 0.025*k, 0.25 - 0.05*k, 0);
			}
			else if (k >= 11 && k < 21)
			{
				glTranslatef(-0.5+0.025*(k-10), -0.25+0.05*(k-10),0);//전번꺼보다 x축은 그대로 가면서 y축만올라가면됨
			}
			else if (k >= 21 && k < 31)
			{
				glTranslatef(-0.25 + 0.025*(k-20), 0.25 - 0.05*(k-20), 0);
			}
			else if (k >= 31 && k < 41)
			{
				glTranslatef(0 + 0.025*(k - 30), -0.25 + 0.05*(k - 30), 0);//전번꺼보다 x축은 그대로 가면서 y축만올라가면됨
			}
			else if (k >= 41 && k < 51)
			{
				glTranslatef(0.25 + 0.025*(k - 40), 0.25 - 0.05*(k - 40), 0);
			}
			else
			{
				glTranslatef(0.5, -0.25,0);
			}
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glRectf(-0.1, -0.1, 0.1, 0.1);
			glPopMatrix();
		}
		else
		{
			if (click == true) {
				printf("%d", k);
				glPushMatrix();
				if (k < 51) {
					glTranslatef(p[0].x+(p[1].x-p[0].x)/50*k, p[0].y +(p[1].y - p[0].y)*k / 50, 0);
				}
				else if (k >= 51 && k < 101)
				{
					glTranslatef(p[1].x + (p[2].x - p[1].x) / 50 * (k-50), p[1].y + (p[2].y - p[1].y)*(k - 50) / 50, 0);
				}
				else if (k >= 101 && k < 151)
				{
					glTranslatef(p[2].x + (p[3].x - p[2].x) / 50 * (k - 100), p[2].y + (p[3].y - p[2].y)*(k - 100) / 50, 0);
				}
				else if (k >= 151 && k < 201)
				{
					glTranslatef(p[3].x + (p[4].x - p[3].x) / 50 * (k - 150), p[3].y + (p[4].y - p[3].y)*(k - 150) / 50, 0);
				}
				else
				{
					glTranslatef(p[4].x, p[4].y, 0);
				}

				if (k % 2 == 0) {
					glScalef(1.3, 1.3, 1.0);
				}
				glRectf(-0.1, -0.1, 0.1, 0.1);
				glPopMatrix();
			}
		}
	}
	else
	{
		if (Shape == 0) {
			glPushMatrix();
			glRotatef(k, 0.0, 0.0, 1.0);
			glTranslatef(0.5, 0.0, 0.0);
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glBegin(GL_TRIANGLES);
			glVertex2d(-0.1, -0.1);
			glVertex2d(0.1, -0.1);
			glVertex2d(0, 0.1);
			glEnd();
			glPopMatrix();
		}
		else if (Shape == 1)
		{
			glPushMatrix();
			if (-0.5 + k*0.01 < 0.5) {
				glTranslatef(-0.5 + k*0.01, sin(3.141592 / 7 * k)*0.1, 0.0); //이동행렬
			}
			else
			{
				glTranslatef(0.5, sin(3.141592 / 7 * 100)*0.1, 0.0); //이동행렬
			}
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glBegin(GL_TRIANGLES);
			glVertex2d(-0.1, -0.1);
			glVertex2d(0.1, -0.1);
			glVertex2d(0, 0.1);
			glEnd();
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}

			glPopMatrix();
		}
		else if (Shape == 2)
		{
			glPushMatrix();
			glRotatef(0, 0.0, 0.0, 1.0);
			glTranslatef(0.0009*k*sin(k*3.141592 / 180), 0.0009*k*cos(k*3.141592 / 180), 0.0);
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glBegin(GL_TRIANGLES);
			glVertex2d(-0.1, -0.1);
			glVertex2d(0.1, -0.1);
			glVertex2d(0, 0.1);
			glEnd();			
			glPopMatrix();
		}
		else if (Shape == 3)
		{
			glPushMatrix();
			if (k < 11) {
				glTranslatef(-0.75 + 0.025*k, 0.25 - 0.05*k, 0);
			}
			else if (k >= 11 && k < 21)
			{
				glTranslatef(-0.5 + 0.025*(k - 10), -0.25 + 0.05*(k - 10), 0);//전번꺼보다 x축은 그대로 가면서 y축만올라가면됨
			}
			else if (k >= 21 && k < 31)
			{
				glTranslatef(-0.25 + 0.025*(k - 20), 0.25 - 0.05*(k - 20), 0);
			}
			else if (k >= 31 && k < 41)
			{
				glTranslatef(0 + 0.025*(k - 30), -0.25 + 0.05*(k - 30), 0);//전번꺼보다 x축은 그대로 가면서 y축만올라가면됨
			}
			else if (k >= 41 && k < 51)
			{
				glTranslatef(0.25 + 0.025*(k - 40), 0.25 - 0.05*(k - 40), 0);
			}
			else
			{
				glTranslatef(0.5, -0.25, 0);
			}
			if (k % 2 == 0) {
				glScalef(1.3, 1.3, 1.0);
			}
			glBegin(GL_TRIANGLES);
			glVertex2d(-0.1, -0.1);
			glVertex2d(0.1, -0.1);
			glVertex2d(0, 0.1);
			glEnd();
			glPopMatrix();
		}
		else
		{
			if (click == true) {
				glPushMatrix();

				if (k < 51) {
					glTranslatef(p[0].x + (p[1].x - p[0].x) / 50 * k, p[0].y + (p[1].y - p[0].y)*k / 50, 0);
				}
				else if (k >= 51 && k < 101)
				{
					glTranslatef(p[1].x + (p[2].x - p[1].x) / 50 * (k - 50), p[1].y + (p[2].y - p[1].y)*(k - 50) / 50, 0);
				}
				else if (k >= 101 && k < 151)
				{
					glTranslatef(p[2].x + (p[3].x - p[2].x) / 50 * (k - 100), p[2].y + (p[3].y - p[2].y)*(k - 100) / 50, 0);
				}
				else if (k >= 151 && k < 201)
				{
					glTranslatef(p[3].x + (p[4].x - p[3].x) / 50 * (k - 150), p[3].y + (p[4].y - p[3].y)*(k - 150) / 50, 0);
				}
				else
				{
					glTranslatef(p[4].x, p[4].y, 0);
				}
				if (k % 2 == 0) {
					glScalef(1.3, 1.3, 1.0);
				}
				glBegin(GL_TRIANGLES);
				glVertex2d(-0.1, -0.1);
				glVertex2d(0.1, -0.1);
				glVertex2d(0, 0.1);
				glEnd();
				glPopMatrix();
			}
		}
	}
	glBegin(GL_LINE_STRIP);
	if (Shape == 0) {
		for (int i = 0; i < 360; i++)
		{
			glVertex2f(0.5*sin(i*3.141592 / 180), 0.5*cos(i*3.141592 / 180)); // 원
		}
	}
	else if (Shape == 1)
	{
		for (int i = 0; i < 100; i++)
		{
			glVertex3f(-0.5 + i*0.01, sin(3.141592 / 7 * i)*0.1, 0);
			glVertex3f(-0.5 + (i + 1)*0.01, sin(3.141592 / 7 * (i + 1))*0.1, 0); //사인곡선
		}
	}
	else if (Shape == 2)
	{
		for (int i = 0; i < 1080; i++)
		{
			glVertex2f(0.0009*i*sin(i*3.141592 / 180), 0.0009*i*cos(i*3.141592 / 180)); //회오리
		}
	}
	else if (Shape == 3)
	{
		glVertex2f(-0.75, 0.25);
		glVertex2f(-0.5, -0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(0, -0.25);
		glVertex2f(0.25, 0.25);
		glVertex2f(0.5, -0.25); //지그재그
	}
	else if (Shape == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			glVertex2f(p[i].x, p[i].y);
			glVertex2f(p[i + 1].x, p[i + 1].y);	 //자유곡선			
		}
	}
	glEnd();



	//좌표계
	glFlush();
}  // gl에서 가져옴 3차원 그래픽에 관련

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
}
//GL에서의 좌표값은 모두 -1~1까지이다. 하지만 좌표계는 바꿀 수 있다. 원점이 중점이다.

GLvoid Timer(int value)
{
	if (Shape == 0)
	{
		k += 5;
	}
	else if (Shape == 1)
	{
		k += 5;
	}
	else if (Shape == 2)
	{
		k += 5;
	}
	else if (Shape == 3)
	{
		k += 5;
	}
	else if (Shape == 4)
	{
		if (click == true) {
			k += 5;
		}
	}
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

GLvoid KeyBoardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		k = 0;
		Shape = 1;
		break;
	case '2':
		k = 0;
		Shape = 2;
		break;
	case '3':
		k = 0;
		Shape = 3;
		break;
	case '4':
		click = false;
		k = 0;
		Shape = 4;
		break;
	case 'f':
		if (tr == false) {
			tr = true;
		}
		else
		{
			tr = false;
		}
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	int Y = Height - y;
	for (int i = 0; i < 5; i++)
	{

		printf("%f %f \n", p[i].x, p[i].y);
	}
	printf("%d %d \n", x, Y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&&Shape==4)
	{
		if (idx < 5) {
			p[idx].x = (double)(x - Width/2) / (Width / 2);
			p[idx].y = (double)(Y - Height/2) / (Height / 2);
			idx++;
		}
		else
		{
			idx = 0;
		}
	}
	if (button == GLUT_RIGHT_BUTTON&&state == GLUT_DOWN&&click == false)
	{
		click = true;
	}
}