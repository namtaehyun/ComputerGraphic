#include <glut.h> // OpenGL ���̺귯��  
#include <math.h>
#include <stdio.h>
#include "Point.h"
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);
// ȭ���� �׸� �� ȣ��
Point p[10];
int time[10] = { 0 };
int idx = 0; //�ε��� ��
int num = 0;
float rad;
void drawScene(void)
{
	glColor3f(0.0f, 0.0f, 0.0f);// �׸����� �������� ����
	glClear(GL_COLOR_BUFFER_BIT);// ���� ������ ������ ä���� �簢���� �׸���.
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(1); // ���� ����
	glBegin(GL_POINTS);// drawing ����� ����

	printf("---------------------------- \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d��° ���� �ð� : %d \n",i+1,time[i]);
	}
	for (int k = 0; k < 10; k++) {
		if (p[k].returnTrue() == true) {
			if (time[k] < 540) {
				for (int i = 0; i <=time[k]; i++) //1080���� �����ش����� 0���� ����������.
				{
					glVertex2f(p[k].p[i].x, p[k].p[i].y);
				}
			}
			else
			{
				if (time[k] < 1080) {
					for (int i = time[k] -540; i <= 540; i++) //1080���� �����ش����� 0���� ����������.
					{
						glVertex2f(p[k].p[i].x, p[k].p[i].y);
					}
				}
				for (int i = 540; i <= time[k]; i++) //1080���� �����ش����� 0���� ����������.
				{
					glVertex2f(p[k].p[1620-i].x, p[k].p[1620 - i].y);
				}

			}
		}
	}
	glEnd();
	glFlush();
}

// Rendering ���¸� ����
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

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
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
					} //�����⻱����
					else
					{
						rad = i*Radian; //������ 180�� ȸ��
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//������R���� �ٷ� ���� ��������.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600 - y; //y�� ����
					} //�ݴ���⻱�R��
				}
				else if (p[idx].dir == 1 && p[idx].cw ==0)
				{
					if (i < 540) {
						rad = (i-180)*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //�����⻱����
					else
					{
						rad = (i-180)*Radian; //������ 180�� ȸ��
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//������R���� �ٷ� ���� ��������.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600 - y; 
					} //�ݴ���⻱�R��
				}
				//////////////////////////////////////////////////
				else if (p[idx].dir == 2 && p[idx].cw == 1) {
					if (i < 540) {
						rad = (i - 60)*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //�����⻱����
					else
					{
						rad = (i-60)*Radian;
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//������R���� �ٷ� ���� ��������.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600-y+94;//2 * p[idx].p[539].x - x
					} //�ݴ���⻱�R��
				}
				else if (p[idx].dir == 2 && p[idx].cw == 0)
				{
					if (i < 540) {
						rad = (i - 240)*Radian;
						p[idx].p[i].x = x + cos(rad)*0.1*i;
						p[idx].p[i].y = sin(rad)*0.1*i + 600 - y;
					} //�����⻱����
					else
					{
						rad = (i - 240)*Radian; //������ 180�� ȸ��
						p[idx].p[i].x = cos(rad)*0.1*(i - 540) + 2 * p[idx].p[539].x - x;//������R���� �ٷ� ���� ��������.
						p[idx].p[i].y = sin(rad)*0.1*(i - 540) + 600 - y-94; 
					} //�ݴ���⻱�R��
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

GLvoid reshape(int w, int h) // �ٽ� �׸��� �Լ�
{
	glViewport(0, 0, w, h); 
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);             // glut �ʱ�ȭ 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);     // ���÷��� ��� ����      
	glutInitWindowPosition(200, 0);         // �������� ��ġ ����     
	glutInitWindowSize(800, 600);          // �������� ũ�� ����       
	glutCreateWindow("Example7");         // ������ ���� (������ �̸�)      
	glutReshapeFunc(reshape);
	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);// ��� �Լ��� ����  
	glutTimerFunc(100, Timerfunction, 1);                // �ٽ� �׸��� �Լ� ����       
	glutMainLoop();                // �̺�Ʈ ó�� ���� 

	return 0;
}