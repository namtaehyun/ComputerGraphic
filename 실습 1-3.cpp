#include <glut.h>   
#include <stdlib.h>
#include <time.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정  
	glutInitWindowSize(450, 450);    // 윈도우의 크기 지정
	glutCreateWindow("Example2");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정  
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	srand(time(NULL));
	int i = rand()%4;

	GLfloat v1[5][2] = { {20,650},{10,750},{100,800},{ 200,750 } ,{150,650} };
	GLfloat v2[5][2] = { { 320,650 },{ 310,750 },{ 400,800 },{ 500,750 } ,{ 450,650 } };
	GLfloat v3[5][2] = { { 620,650 },{ 610,750 },{ 700,800 },{ 800,750 } ,{ 750,650 } };
	GLfloat v4[5][2] = { { 20,350 },{ 10,450 },{ 100,500 },{ 200,450 } ,{ 150,350 } };
	GLfloat v5[5][2] = { { 320,350 },{ 310,450 },{ 400,500 },{ 500,450 } ,{ 450,350 } };
	GLfloat v6[5][2] = { { 620,350 },{ 610,450 },{ 700,500 },{ 800,450 } ,{ 750,350 } };
	GLfloat v7[5][2] = { { 20,50 },{ 10,150 },{ 100,200 },{ 200,150 } ,{ 150,50 } };
	GLfloat v8[5][2] = { { 320,50 },{ 310,150 },{ 400,200 },{ 500,150 } ,{ 450,50 } };
	GLfloat v9[5][2] = { { 620,50 },{ 610,150 },{ 700,200 },{ 800,150 } ,{ 750,50 } };

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear(GL_COLOR_BUFFER_BIT);    // 설정된 색으로 젂체를 칠하기 
									 //glOrtho(left,right,bottom,top)
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);  // 바탕색을 'blue' 로 지정  

	glBegin(GL_LINES); 
	glVertex2i(300,0);
	glVertex2i(300,900);
	glVertex2i(600, 0);
	glVertex2i(600, 900);
	glVertex2i(0, 300);
	glVertex2i(900, 300);
	glVertex2i(0, 600);
	glVertex2i(900, 600);
	glEnd ();//선그리기

	if (i == 0)// 선일때
	{
		glBegin(GL_LINES);
		glVertex2iv(v1[0]);
		glVertex2iv(v1[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v2[0]);
		glVertex2iv(v2[1]);
		glVertex2iv(v2[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v3[0]);
		glVertex2iv(v3[1]);
		glVertex2iv(v3[2]);
		glVertex2iv(v3[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v4[0]);
		glVertex2iv(v4[1]);
		glVertex2iv(v4[2]);
		glVertex2iv(v4[3]);
		glVertex2iv(v4[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v5[0]);
		glVertex2iv(v5[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v6[0]);
		glVertex2iv(v6[1]);
		glVertex2iv(v6[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v7[0]);
		glVertex2iv(v7[1]);
		glVertex2iv(v7[2]);
		glVertex2iv(v7[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v8[0]);
		glVertex2iv(v8[1]);
		glVertex2iv(v8[2]);
		glVertex2iv(v8[3]);
		glVertex2iv(v8[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v9[0]);
		glVertex2iv(v9[1]);
		glEnd();

	}
	else if(i == 1) //삼각형일때
	{

		
		glBegin(GL_TRIANGLES);
		glVertex2iv(v1[0]);
		glVertex2iv(v1[1]);
		glVertex2iv(v1[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v2[0]);
		glVertex2iv(v2[1]);
		glVertex2iv(v2[2]);
		glVertex2iv(v2[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v3[0]);
		glVertex2iv(v3[1]);
		glVertex2iv(v3[2]);
		glVertex2iv(v3[3]);
		glVertex2iv(v3[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v4[0]);
		glVertex2iv(v4[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v5[0]);
		glVertex2iv(v5[1]);
		glVertex2iv(v5[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v6[0]);
		glVertex2iv(v6[1]);
		glVertex2iv(v6[2]);
		glVertex2iv(v6[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v7[0]);
		glVertex2iv(v7[1]);
		glVertex2iv(v7[2]);
		glVertex2iv(v7[3]);
		glVertex2iv(v7[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v8[0]);
		glVertex2iv(v8[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v9[0]);
		glVertex2iv(v9[1]);
		glVertex2iv(v9[2]);
		glEnd();

	}


	else if (i == 2) //사각형일때
	{

		glBegin(GL_QUADS);
		glVertex2iv(v1[0]);
		glVertex2iv(v1[1]);
		glVertex2iv(v1[2]);
		glVertex2iv(v1[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v2[0]);
		glVertex2iv(v2[1]);
		glVertex2iv(v2[2]);
		glVertex2iv(v2[3]);
		glVertex2iv(v2[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v3[0]);
		glVertex2iv(v3[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v4[0]);
		glVertex2iv(v4[1]);
		glVertex2iv(v4[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v5[0]);
		glVertex2iv(v5[1]);
		glVertex2iv(v5[2]);
		glVertex2iv(v5[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v6[0]);
		glVertex2iv(v6[1]);
		glVertex2iv(v6[2]);
		glVertex2iv(v6[3]);
		glVertex2iv(v6[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v7[0]);
		glVertex2iv(v7[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v8[0]);
		glVertex2iv(v8[1]);
		glVertex2iv(v8[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v9[0]);
		glVertex2iv(v9[1]);
		glVertex2iv(v9[2]);
		glVertex2iv(v9[3]);
		glEnd();
	}



	else if (i == 3) //오각형일때
	{
		glBegin(GL_POLYGON);
		glVertex2iv(v1[0]);
		glVertex2iv(v1[1]);
		glVertex2iv(v1[2]);
		glVertex2iv(v1[3]);
		glVertex2iv(v1[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v2[0]);
		glVertex2iv(v2[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v3[0]);
		glVertex2iv(v3[1]);
		glVertex2iv(v3[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v4[0]);
		glVertex2iv(v4[1]);
		glVertex2iv(v4[2]);
		glVertex2iv(v4[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v5[0]);
		glVertex2iv(v5[1]);
		glVertex2iv(v5[2]);
		glVertex2iv(v5[3]);
		glVertex2iv(v5[4]);
		glEnd();

		glBegin(GL_LINES);
		glVertex2iv(v6[0]);
		glVertex2iv(v6[1]);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2iv(v7[0]);
		glVertex2iv(v7[1]);
		glVertex2iv(v7[2]);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2iv(v8[0]);
		glVertex2iv(v8[1]);
		glVertex2iv(v8[2]);
		glVertex2iv(v8[3]);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2iv(v9[0]);
		glVertex2iv(v9[1]);
		glVertex2iv(v9[2]);
		glVertex2iv(v9[3]);
		glVertex2iv(v9[4]);
		glEnd();

	}

	glFlush(); // 화면에 출력하기 
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 900, 0, 900, -1.0, 1.0);
}
