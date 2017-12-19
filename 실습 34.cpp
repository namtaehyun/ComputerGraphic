
#include <stdio.h>
#include<glut.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void renderBitmapCharacter(float x, float y, void *font, char *string);
double alpha_Color[9];
int select_Num;
GLvoid drawScene()
{
	glClearColor(0, 0, 0, 0);            // 바탕색을 'black' 로 지정   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);                              // 가려진 면 제거
	{
		glPushMatrix();
		if (select_Num < 3)
		{
			glTranslatef(select_Num * 200, 0, 0);
		}
		if (select_Num >= 3&& select_Num < 6)
		{
			glTranslatef((select_Num-3) * 200, -200, 0);
		}
		if (select_Num >= 6 && select_Num <= 9)
		{
			glTranslatef((select_Num - 6) * 200, -400, 0);
		}
		glLineWidth(5);
		glBegin(GL_LINE_STRIP);
		glColor3f(1, 0, 1);
		{
			glVertex2f(0, 600);
			glVertex2f(0, 400);
			glVertex2f(200, 400);
			glVertex2f(200, 600);
			glVertex2f(0, 600);
			glVertex2f(0, 400);
		}
		glEnd();
		glPopMatrix();
	}


	{
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE,GL_ZERO);
			glPushMatrix();
			glTranslatef(0, 400, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.4 + alpha_Color[0]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.3 + alpha_Color[0]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.2 + alpha_Color[0]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(40, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(50, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_ONE,GL_ZERO)");
			glPopMatrix();
			
		} //1번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ZERO, GL_ONE);
			glPushMatrix();
			glTranslatef(200, 400, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.6 + alpha_Color[1]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.2 + alpha_Color[1]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.4 + alpha_Color[1]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(50, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_ZERO,GL_ONE)");
			glPopMatrix();
		}//2번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glPushMatrix();
			glTranslatef(400, 400, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.4 + alpha_Color[2]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.2 + alpha_Color[2]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.3 + alpha_Color[2]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(50, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_ONE,GL_ONE)");
			glPopMatrix();
		}//3번
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPushMatrix();
			glTranslatef(0, 200, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.6 + alpha_Color[3]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.8 + alpha_Color[3]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.9 + alpha_Color[3]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(0, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_SRC_A,GL_ONE_MINUS_SRC_A)");
			glPopMatrix();
		} //4번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glPushMatrix();
			glTranslatef(200, 200, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.4 + alpha_Color[4]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.2 + alpha_Color[4]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.5 + alpha_Color[4]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(50, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_SRC_ALPHA,GL_ONE)");
			glPopMatrix();
		}//5번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);			
			glPushMatrix();
			glTranslatef(400, 200, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.7 + alpha_Color[5]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.8 + alpha_Color[5]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.9 + alpha_Color[5]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(50, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_ZERO,GL_SRC_COLOR)");
			glPopMatrix();
		}//6번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.3 + alpha_Color[6]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.6 + alpha_Color[6]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.9 + alpha_Color[6]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(0, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_ONE_MINUS_DST_C,GL_ZERO)");
		} //7번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
			glPushMatrix();
			glTranslatef(200, 0, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.5 + alpha_Color[7]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.6 + alpha_Color[7]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.2 + alpha_Color[7]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(0, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_SRC_A,GL_ONE_MINUS_SRC_C)");
			glPopMatrix();
		}//8번

		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glPushMatrix();
			glTranslatef(400, 0, 0);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.4 + alpha_Color[8]);
			glTranslatef(60, 100, 300);
			glutSolidCube(100);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 0.7 + alpha_Color[8]);
			glTranslatef(90, 100, 200);
			glutSolidTeapot(50);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 0.0, 1.0, 0.5 + alpha_Color[8]);
			glTranslatef(90, 50, 100);
			glutSolidSphere(50, 20, 20);
			glPopMatrix();
			glDisable(GL_BLEND);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(50, 180, GLUT_BITMAP_TIMES_ROMAN_10, "(GL_ONE,GL_ONE)");
			glPopMatrix();
		}//9번


	}

	glutSwapBuffers();// 화면에 출력하기
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		select_Num = 0;
		break;
	case '2':
		select_Num = 1;
		break;
	case '3':
		select_Num = 2;
		break;
	case '4':
		select_Num = 3;
		break;
	case '5':
		select_Num = 4;
		break;
	case '6':
		select_Num = 5;
		break;
	case '7':
		select_Num = 6;
		break;
	case '8':
		select_Num = 7;
		break;
	case '9':
		select_Num = 8;
		break;
	case '-':
		alpha_Color[select_Num]-=0.1;
		break;
	case '+':
		alpha_Color[select_Num] += 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void main(int argc, char** argv)                    // 윈도우 출력하고 출력함수 설정 
{
	for (int i = 0; i < 9; i++)
	{
		alpha_Color[i] = 0;
	}
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);                           // glut 초기화 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);     // 디스플레이 모드 설정
	glutInitWindowPosition(200, 0);                  // 윈도우의 위치 지정
	glutInitWindowSize(600, 600);                    // 윈도우의 크기 지정
	glutCreateWindow("Example11");                   // 윈도우 생성 (윈도우 이름)
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutDisplayFunc(drawScene);                      // 출력 함수의 지정
	glutReshapeFunc(reshape);                        // 다시 그리기 함수 지정
	glutPostRedisplay();
	glutMainLoop();                                  // 이벤트 처리 시작
}
void Mouse(int button, int state, int x, int y)
{
	glutPostRedisplay();

}
void Motion(int x, int y) {

	glutPostRedisplay();
}
GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 600, 0, 600, 300, -300);
	glutPostRedisplay();
}

void renderBitmapCharacter(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}