#include <glut.h>  
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
GLvoid drawScene();
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ����  
	glutInitWindowSize(800, 600);    // �������� ũ�� ����
	glutCreateWindow("Example2");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// ������ ��� �Լ� 
GLvoid drawScene()
{
	int n = rand()%5+1;
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // �������� 'blue' �� ����  
	glClear(GL_COLOR_BUFFER_BIT);    // ������ ������ ��ü�� ĥ�ϱ� 
									 //glOrtho(left,right,bottom,top)
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);     // �׸��� ���� 'green' ���� ���� 
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			glRectf(900 / n*i, 900 / n*k, (900 / n) / 2 + 900 / n*i, (900 / n) / 2 + 900 / n*k);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			glRectf((900 / n) / 2 + (900 / n)*i, (900 / n) / 2 + (900 / n)*k, (900 / n) + (900 / n)*i, (900 / n) + (900 / n)*k);
		}
	}
	printf("%d", n);
	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
	glOrtho(0.0, 900, 0.0, 900, -1.0, 1.0);
}
