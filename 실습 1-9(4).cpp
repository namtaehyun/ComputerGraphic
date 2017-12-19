#include <glut.h> // OpenGL 라이브러리  
#include <math.h>
#include <stdio.h>
#include "Point.h"
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);
// 화면을 그릴 때 호출
Point p[10];
int time[10] = { 0 };
int idx = 0; //인덱스 값
int num = 0;
float rad;
void drawScene(void)
{
	glColor3f(0.0f, 0.0f, 0.0f);// 그림색을 적색으로 설정
	glClear(GL_COLOR_BUFFER_BIT);// 현재 설정된 색으로 채워진 사각형을 그린다.
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(1); // 선의 굵기
	glBegin(GL_POINTS);// drawing 명령을 실행

	printf("---------------------------- \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d번째 원의 시간 : %d \n",i+1,time[i]);
	}
	for (int k = 0; k < 10; k++) {
		if (p[k].returnTrue() == true) {
			if (time[k] < 540) {
				for (int i = 0; i <=time[k]; i++) //1080까지 보여준다음에 0부터 없어져야함.
				{
					glVertex2f(p[k].p[i].x, p[k].p[i].y);
				}
			}
			else
			{
				if (time[k] < 1080) {
					for (int i = time[k] -540; i <= 540; i++) //1080까지 보여준다음에 0부터 없어져야함.
					{
						glVertex2f(p[k].p[i].x, p[k].p[i].y);
					}
				}
				for (int i = 540; i <= time[k]; i++) //1080까지 보여준다음에 0부터 없어져야함.
				{
					glVertex2f(p[k].p[1620-i].x, p[k].p[1620 - i].y);
				}

			}
		}
	}
	glEnd();
	glFlush();
}

// Rendering 상태를 설정
void Timerfunction(int value)
{
	for (int i = 0; i < 10; i++)
	{
		if (p[i].returnTrue() == true)
		{
			if (time[i]< 1080)
			{
				time[i] += 20;
			}
		}
	}

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, Timerfunction, 1); // 타이머함수 재 설정
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (idx < 10) {
			for (int i = 0; i <= 1080; i++) 
			{
				if (p[idx].dir == 1 && p[idx].cw == 1) {
					if (i < 540) {
						rad = i*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //정방향뺑뺑이
					else
					{
						rad = i*Radian; //뺑뺑이 180도 회전
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//정방향뻉뺑이 바로 옆에 나오게함.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600 - y; //y는 같음
					} //반대방향뺑뻉이
				}
				else if (p[idx].dir == 1 && p[idx].cw ==0)
				{
					if (i < 540) {
						rad = (i-180)*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //정방향뺑뺑이
					else
					{
						rad = (i-180)*Radian; //뺑뺑이 180도 회전
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//정방향뻉뺑이 바로 옆에 나오게함.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600 - y; 
					} //반대방향뺑뻉이
				}
				//////////////////////////////////////////////////
				else if (p[idx].dir == 2 && p[idx].cw == 1) {
					if (i < 540) {
						rad = (i - 60)*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //정방향뺑뺑이
					else
					{
						rad = (i-60)*Radian;
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//정방향뻉뺑이 바로 옆에 나오게함.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600-y+94;//2 * p[idx].p[539].x - x
					} //반대방향뺑뻉이
				}
				else if (p[idx].dir == 2 && p[idx].cw == 0)
				{
					if (i < 540) {
						rad = (i - 240)*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //정방향뺑뺑이
					else
					{
						rad = (i - 240)*Radian; //뺑뺑이 180도 회전
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//정방향뻉뺑이 바로 옆에 나오게함.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600 - y-94; 
					} //반대방향뺑뻉이
				}

			}
			p[idx].ChangeIstrue();
			idx++;
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				for (int k = 0; k < 1080; k++) {
					p[i].SetX(0,k);
					p[i].SetY(0,k);
					time[i] = 0;
					p[i].ChangeIstrue();
				}
			}
			idx = 0;
		}
	}
	glutPostRedisplay();
}

GLvoid reshape(int w, int h) // 다시 그리기 함수
{
	glViewport(0, 0, w, h); 
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);             // glut 초기화 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);     // 디스플레이 모드 설정      
	glutInitWindowPosition(200, 0);         // 윈도우의 위치 지정     
	glutInitWindowSize(800, 600);          // 윈도우의 크기 지정       
	glutCreateWindow("Example7");         // 윈도우 생성 (윈도우 이름)      
	glutReshapeFunc(reshape);
	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);// 출력 함수의 지정  
	glutTimerFunc(100, Timerfunction, 1);                // 다시 그리기 함수 지정       
	glutMainLoop();                // 이벤트 처리 시작 

	return 0;
}