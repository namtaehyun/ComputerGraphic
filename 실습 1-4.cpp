#include <glut.h>  
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Mouse(int button, int state, int x, int y);

struct Rect {
	int x1, y1,x2,y2;
	int x3, y3, x4, y4;
};

int k = 0;
int i=0;
Rect rect[10];

void main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	glutMouseFunc(Mouse);
	glutTimerFunc(100, Timerfunction, 1);
	glutDisplayFunc(drawScene);    // 출력 함수의 지정  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);    // 설정된 색으로 젂체를 칠하기 
									 //glOrtho(left,right,bottom,top)
	if (k % 2 == 0) {
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		for (int i = 0; i < 10; i++)
		{
			glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
		}
	}
	else
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 10; i++)
		{
			glRectf(rect[i].x3, rect[i].y3, rect[i].x4, rect[i].y4);
		}
	}
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);     // 그리기 색을 'green' 으로 지정 
	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glutPostRedisplay();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Mouse(int button, int state, int x, int y) 
{ 
	int size = rand()%100+100;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (i < 10) {
			rect[i].x1 = x;
			rect[i].y1 = 600-y+size-50;
			rect[i].y2 = 600 - y + size;
			rect[i].x2 = x + size;

			rect[i].x3 = x + 50;
			rect[i].y3 = 600 - y;
			rect[i].x4 = x + size - 50;
			rect[i].y4 = 600 - y + size + 50;
			i++;
		}
		else
		{
			i = 0;
			rect[i].x1 = x;
			rect[i].y1 = 600 - y - 50;
			rect[i].x2 = x + size;
			rect[i].y2 = 600 - y + size;
			
			rect[i].x3 = x+50 ;
			rect[i].y3 = 600 - y;
			rect[i].x4 = x + size-50;
			rect[i].y4 = 600 - y + size + 50;
		}
		printf("%d %d %d %d \n", x, y, x + size, y + size);
	}
	glutPostRedisplay();
}

void Timerfunction(int value) {
	k++;
	glutPostRedisplay();   // 화면 재 출력 
	glutTimerFunc (100, Timerfunction, 1); // 타이머함수 재 설정 
}