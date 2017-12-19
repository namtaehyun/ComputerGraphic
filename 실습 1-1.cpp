#include <glut.h>   
GLvoid drawScene( GLvoid );
GLvoid Reshape (int w, int h); 

void main(int argc, char *argv[]) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition ( 100, 100 );    // 윈도우의 위치지정  
	glutInitWindowSize ( 800, 600 );    // 윈도우의 크기 지정
	glutCreateWindow ( "Example2" );    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc (drawScene);    // 출력 함수의 지정  
	glutReshapeFunc (Reshape);
	glutMainLoop(); 
}  
																		   // 윈도우 출력 함수 
GLvoid drawScene ( GLvoid ) 
{  
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);  // 바탕색을 'blue' 로 지정  
	glClear( GL_COLOR_BUFFER_BIT );    // 설정된 색으로 젂체를 칠하기 
	//glOrtho(left,right,bottom,top)

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);     // 그리기 색을 'green' 으로 지정 
	glRectf (-0.2f, -0.2f, 0.2f, 0.2f);    // 사각형 그리기
	//중앙

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);     // 그리기 색을 'red' 으로 지정 
	glRectf(-1.0f, -1.0f, -0.6f, -0.6f);    // 사각형 그리기

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);     // 그리기 색을 'green' 으로 지정 
	glRectf(1.0f, 1.0f, 0.6f, 0.6f);    // 사각형 그리기

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);     // 그리기 색을 'blue' 으로 지정 
	glRectf(-1.0f,1.0f,-0.6f,0.6f);    // 사각형 그리기

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);     // 그리기 색을 'yellow' 으로 지정 
	glRectf(1.0f, -1.0f, 0.6f, -0.6f);    // 사각형 그리기

	glFlush(); // 화면에 출력하기 
} 
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}