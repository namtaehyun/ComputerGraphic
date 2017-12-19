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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ����  
	glutInitWindowSize(800, 600);    // �������� ũ�� ����
	glutCreateWindow("Example2");    // ������ ���� (������ �̸�)  
	glutMouseFunc(Mouse);
	glutTimerFunc(100, Timerfunction, 1);
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// ������ ��� �Լ� 
GLvoid drawScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);  // �������� 'blue' �� ����  
	glClear(GL_COLOR_BUFFER_BIT);    // ������ ������ ��ü�� ĥ�ϱ� 
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
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);     // �׸��� ���� 'green' ���� ���� 
	glFlush(); // ȭ�鿡 ����ϱ� 
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
	glutPostRedisplay();   // ȭ�� �� ��� 
	glutTimerFunc (100, Timerfunction, 1); // Ÿ�̸��Լ� �� ���� 
}