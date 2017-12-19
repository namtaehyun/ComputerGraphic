#include <glut.h>  
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
GLvoid drawScene();
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(800, 600);    // 윈도우의 크기 지정
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene()
{
	int n = rand()%5+1;
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);    // 설정된 색으로 젂체를 칠하기 
									 //glOrtho(left,right,bottom,top)
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);     // 그리기 색을 'green' 으로 지정 
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
	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
	glOrtho(0.0, 900, 0.0, 900, -1.0, 1.0);
}
