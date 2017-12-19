#include <glut.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define ANGLE_TO_RAD 180/3.141592

float ctrlpoints[30][3];

void Curve_calcu();
// 베지어곡선을 만들 컨트롤포인트 30개
// 첫점과 마지막(4번째) 점을 기준으로 첫점보다
// 마지막점이 x,y,z축의 아래방향에 있을 경우
// 컨트롤포인트를 x,y,z축의 각각의 아래로 잡아준다
double innerproduct(double x1, double y1, double z1, double x2, double y2, double z2);
double vector_line_x;
double vector_line_y;
double vector_line_z;

double angle_xy;
double angle_yz;
double angle_zx;

struct P_move {
	float moveX[101];
	float moveY[101];
	float moveZ[101];
}; // 좌표 움직일꺼
   //

struct pMove_data
{
	float moveX[3000];
	float moveY[3000];
	float moveZ[3000];
};
P_move Move_data[30];
pMove_data m_data;

int Dirnum;
int movenum;
int pangle;
int start;
//비행기 움직임관련
//
int first_click_x;
int first_click_y;
int drag_x;
int drag_y;
int temp_x;
int temp_y;
bool click;
//마우스
bool CollisionCheck(double x1, double x2, double y1, double y2, double z1, double z2, double rad1, double rad2); // 구와 구간의 충돌체크
void Draw_Collision(double x, double y, double z); // 충돌시 폭발 시뮬
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
GLvoid Timer(int value);
void SpecialKeyboard(int key, int x, int y);
GLUquadricObj *obj;
void keyboard(unsigned char key, int x, int y);
//
int rotateX, rotateY, rotateZ;
double xAngle, yAngle, zAngle;
double moveX, moveY, moveZ;
bool Fps;
//카메라
void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);
//
void Draw_Boundary();
void DrawStar();
void Draw_Home(double rad);
void Draw_Planet();
void Draw_arrow(double rad);
void Draw_Line();
void Draw_Plane();
void Draw_Tree(double rad);
//
void Set_Position();
bool collide;
float c_x, c_y, c_z; // 컨트롤 포인트를 찍을 점의 위치를 결정하기 위한 변수
int cp_idx; // 컨트롤포인트의 인덱스 
double ex_time; // 폭발 시간
bool explode;
bool timeTostart;
int roundTrip; // 1일때 왕복 2일때 편도
//
GLfloat AmbientLight1[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat DiffuseLight1[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat SpecularLight1[] = { 0.0, 1.0, 1.0, 1.0 }; //
GLfloat lightPos1[] = { 0,10,10,1 }; // 조명위치 1

struct Star
{
	double x, y, z, R, G, B;
};
bool bCheckExistOfNum[15] = { false, }; // 중복체크
struct Planet
{
	double x, y, z; //구의 중심점의 좌표
	double rad;      //구의 반지름
	double R, G, B; //구의 색깔
};
Star s[3000];
Planet p[15];
void main(int argc, char** argv)
{
	c_x = 0;
	c_y = 0;
	c_z = 0;
	ctrlpoints[0][0] = 0;
	ctrlpoints[0][1] = 10;
	ctrlpoints[0][2] = 10;
	srand(time(unsigned(NULL)));
	for (int i = 0; i < 30; i++)
	{
		ctrlpoints[i][0] = 0;
		ctrlpoints[i][1] = 10;
		ctrlpoints[i][2] = 10;
	}
	for (int i = 0; i < 3000; i++)
	{
		s[i].x = rand() % 100 - 50;
		s[i].y = rand() % 100 - 50;
		s[i].z = rand() % 100 - 50;
		s[i].R = rand() % 100 * 0.01;
		s[i].G = rand() % 100 * 0.01;
		s[i].B = rand() % 100 * 0.01;
	}
	Set_Position();
	moveX = -5;
	moveY = -5;
	moveZ = -90;
	xAngle = 0;
	yAngle = 0;
	zAngle = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, Timer, 1);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (Fps == false) {
		glTranslatef(moveX, moveY, moveZ);
		glTranslatef(5, 5, 5);
		glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
		glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
		glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
		glTranslatef(-5, -5, -5);
		gluLookAt(
			0, 0, 0,
			0.0, 0.0, -1.0,
			0.0, 1.0, 0.0
		);
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	else
	{
		glTranslatef(0, 0, 36);
		glRotatef(22 + xAngle, 1.0f, 0.0f, 0.0f);
		glRotatef(90 + yAngle, 0.0f, 1.0f, 0.0f);
		glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
		glTranslatef(-m_data.moveX[movenum], -m_data.moveY[movenum], -m_data.moveZ[movenum]);
		gluLookAt(
			0, 0, 0,
			0.0, 0.0, -1.0,
			0.0, 1.0, 0.0
		);
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		printf("m: %f %f %f \n", moveX, moveY, moveZ);
		printf("R: %f %f \n", xAngle, yAngle);

	}

	glEnable(GL_DEPTH_TEST);
	{
		glColor3f(1, 1, 1);
		for (int i = 0; i * 3 < cp_idx; i++) {
			glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpoints[i * 3][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= 100; i++)
			{
				glEvalCoord1f((float)i / 100.0);
			}
			glEnd();
			glDisable(GL_MAP1_VERTEX_3);
		}

		Curve_calcu();

		glPointSize(5.0);
		glBegin(GL_POINTS);
		for (int j = 0; j < 30; j++) {
			glVertex3fv(&ctrlpoints[j][0]); // 컨트롤 포인트에 점을 찍는다.
		}
		glEnd();
	} // 베지어곡선
	Draw_Boundary();
	DrawStar();
	Draw_Plane();
	Draw_Planet();
	Draw_Line();

	if (explode == true) {
		Draw_Collision(m_data.moveX[movenum], m_data.moveY[movenum], m_data.moveZ[movenum]);
	}

	glutSwapBuffers();
}

GLvoid reshape(int w, int h)    // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다. // 1. 클리핑 공간 설정: 원근 투영인 경우 
	gluPerspective(10.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -50.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다. 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if (c_x < 10) {
			c_x += 0.1;
		}
		break;
	case GLUT_KEY_LEFT:
		if (c_x > 0) {
			c_x -= 0.1;
		}
		break;
	case GLUT_KEY_UP:
		if (c_z > -9.9) {
			c_z -= 0.1;
		}
		break;
	case GLUT_KEY_DOWN:
		if (c_z < 0) {
			c_z += 0.1;
		}
		break;
	}

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (Fps == false)
		{
			Fps = true;
		}
		else
		{
			Fps = false;
		}
		break;
	case '[':
		if (c_y > -9.9) {
			c_y -= 0.1;
		}
		break;
	case ']':
		if (c_y < 0) {
			c_y += 0.1;
		}
		break;
	case 'k':
		if (timeTostart == false) {
			for (int i = 0; i < 14; i++) {
				if (CollisionCheck(p[i].x, c_x, p[i].y, c_y, p[i].z, c_z, 0.5, 0.5))
				{
					collide = true;
					break;
				}
				else
				{
					collide = false;
				}
			}
			if (collide == false) {
				for (int i = cp_idx + 1; i < 30; i++) {
					ctrlpoints[i][0] = c_x;
					ctrlpoints[i][1] = c_y + 10;
					ctrlpoints[i][2] = c_z + 10;
				}
				cp_idx++;
			}
			if (CollisionCheck(p[14].x, ctrlpoints[cp_idx][0], p[14].y, ctrlpoints[cp_idx][1], p[14].z, ctrlpoints[cp_idx][2], p[14].rad, 0.1))
			{
				timeTostart = true;
				roundTrip = 2; // 편도
			}
		}
		break;
	case 'r':
		if (cp_idx > 0) {
			ctrlpoints[cp_idx][0] = 0;
			ctrlpoints[cp_idx][1] = 10;
			ctrlpoints[cp_idx][2] = 10;
			cp_idx--;
		}
		break;
	case 'R':
		for (int i = 0; i < 30; i++) {
			ctrlpoints[i][0] = 0;
			ctrlpoints[i][1] = 10;
			ctrlpoints[i][2] = 10;
		}
		for (int i = 0; i < 3000; i++) {
			m_data.moveX[movenum] = 0;
			m_data.moveY[movenum] = 0;
			m_data.moveZ[movenum] = 0;
		}
		timeTostart = false;
		movenum = 0;
		roundTrip = 0;
		start = 0;
		cp_idx = 0;
		c_x = 0;
		c_y = 0;
		c_z = 0;
	case 'w':
		moveZ++;
		break;
	case 's':
		moveZ--;
		break;
	case 'a':
		moveX++;
		break;
	case 'd':
		moveX--;
		break;
	case '-':
		moveY++;
		break;
	case '=':
		moveY--;
		break;
	case 'x':
		xAngle++;
		break;
	case 'y':
		yAngle++;
		break;
	case 'z':
		zAngle++;
		break;
	case 'X':
		xAngle--;
		break;
	case 'Y':
		yAngle--;
		break;
	case 'Z':
		zAngle--;
		break;
	case 'n':
		roundTrip = 1; // 왕복
		start = 1;
		break;
	case 'm':
		roundTrip = 2; // 편도
		break;
	case 'i':
		moveX = -5;
		moveY = -5;
		moveZ = -90;
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
		break;
	}
	glutPostRedisplay();
}
GLvoid Timer(int value)
{
	for (int i = 1; i < 14; i++)
	{
		if (CollisionCheck(p[i].x, m_data.moveX[movenum], p[i].y, m_data.moveY[movenum],
			p[i].z, m_data.moveZ[movenum], p[i].rad, 0.5) == true)
			explode = true;
	}

	if (explode == true) {
		ex_time += 0.3;
		if (ex_time > 3)
		{
			for (int i = 0; i < 30; i++) {
				ctrlpoints[i][0] = 0;
				ctrlpoints[i][1] = 10;
				ctrlpoints[i][2] = 10;
			}
			for (int i = 0; i < 3000; i++) {
				m_data.moveX[movenum] = 0;
				m_data.moveY[movenum] = 0;
				m_data.moveZ[movenum] = 0;
			}
			timeTostart = false;
			c_x = 0;
			c_y = 0;
			c_z = 0;
			movenum = 0;
			roundTrip = 0;
			start = 0;
			cp_idx = 0;
			explode = false;
			ex_time = 0;
		}
	}
	for (int i = 0; i < 3000; i++)
	{
		s[i].R = rand() % 100 * 0.01;
		s[i].G = rand() % 100 * 0.01;
		s[i].B = rand() % 100 * 0.01;
	}
	if (roundTrip == 1) {
		if (CollisionCheck(p[0].x, m_data.moveX[movenum], p[0].y, m_data.moveY[movenum], p[0].z, m_data.moveZ[movenum], 0.5, p[0].rad))
		{
			start = 1;
		}
		else if (CollisionCheck(p[14].x, m_data.moveX[movenum], p[14].y, m_data.moveY[movenum], p[14].z, m_data.moveZ[movenum], 0.5, p[14].rad))
		{
			start = 2;
		}

		if (start == 1) {
			movenum++;
			vector_line_x = m_data.moveX[movenum + 1] - m_data.moveX[movenum];
			vector_line_y = m_data.moveY[movenum + 1] - m_data.moveY[movenum];
			vector_line_z = m_data.moveZ[movenum + 1] - m_data.moveZ[movenum];
			if (vector_line_x < 0)
			{
				angle_xy = -1 * (innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90) + 180;
			}
			else
				angle_xy = innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90;

			angle_yz = innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90;
			//001
			angle_zx = innerproduct(0, 0, 1, vector_line_x, vector_line_y, vector_line_z) - 90;




		}
		else if (start == 2)
		{
			vector_line_x = m_data.moveX[movenum] - m_data.moveX[movenum - 1];
			vector_line_y = m_data.moveY[movenum] - m_data.moveY[movenum - 1];
			vector_line_z = m_data.moveZ[movenum] - m_data.moveZ[movenum - 1];
			if (vector_line_x < 0)
			{
				angle_xy = -1 * (innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90) + 180;
			}
			else
				angle_xy = innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90;

			angle_yz = innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90;
			//001
			angle_zx = innerproduct(0, 0, 1, vector_line_x, vector_line_y, vector_line_z) - 90;


			movenum--;
		}
	}
	else if (roundTrip == 2)
	{

		vector_line_x = m_data.moveX[movenum + 1] - m_data.moveX[movenum];
		vector_line_y = m_data.moveY[movenum + 1] - m_data.moveY[movenum];
		vector_line_z = m_data.moveZ[movenum + 1] - m_data.moveZ[movenum];
		if (CollisionCheck(p[14].x, m_data.moveX[movenum], p[14].y, m_data.moveY[movenum], p[14].z, m_data.moveZ[movenum], 0.5, p[14].rad) == false)
		{
			if (vector_line_x < 0)
			{
				angle_xy = -1 * (innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90) + 180;
			}
			else
			{
				angle_xy = innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90;
				angle_yz = innerproduct(0, 1, 0, vector_line_x, vector_line_y, vector_line_z) - 90;
				angle_zx = innerproduct(0, 0, 1, vector_line_x, vector_line_y, vector_line_z) - 90;
			}

			printf("X : %f, Y : %f , Z : %f \n", vector_line_x, vector_line_y, vector_line_z);

			movenum++;
		}
	}
	pangle += 15;
	glutTimerFunc(100, Timer, 1);
	glutPostRedisplay();
}

void Draw_Boundary()
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(0, 0, 10);
	glVertex3f(10, 0, 10);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 0, 10);
	glVertex3f(0, 0, 10);
	glVertex3f(0, 10, 10);
	glVertex3f(0, 10, 10);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 10, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 0, 10);
	glEnd();
}

void DrawStar()
{
	for (int i = 0; i < 3000; i++)
	{
		glPointSize(1);
		glColor3f(s[i].R, s[i].G, s[i].B);
		glBegin(GL_POINTS);
		glVertex3f(s[i].x, s[i].y, s[i].z);
		glEnd();
	}
}

void Draw_Planet()
{
	for (int i = 1; i < 14; i++)
	{
		glPushMatrix();
		glTranslatef(p[i].x, p[i].y, p[i].z);
		if (i % 3 == 1)
		{
			glRotatef(pangle, 0, 1, 0);
		}
		glColor3f(p[i].R, p[i].G, p[i].B);
		glutSolidSphere(p[i].rad, 20, 20);
		glColor3f(0, 1, 0);
		glutSolidCube(p[i].rad*1.3);
		glPopMatrix();
	}
	{
		glPushMatrix();
		glColor3f(0, 1, 1);
		glTranslatef(p[0].x, p[0].y, p[0].z);
		Draw_arrow(p[0].rad);
		glColor3f(p[0].R, p[0].G, p[0].B);
		glutSolidSphere(p[0].rad, 20, 20);
		glPopMatrix();
	}

	{
		glPushMatrix();
		glTranslatef(p[14].x, p[14].y, p[14].z);
		Draw_Home(p[14].rad);
		if (timeTostart == true)
		{
			glColor3f(0, 1, 0);
		}
		Draw_arrow(p[14].rad);
		glColor3f(p[14].R, p[14].G, p[14].B);
		glutSolidSphere(p[14].rad, 20, 20);
		glPopMatrix();
	}

}

void Draw_Line()
{
	glPointSize(5);
	{
		glPushMatrix();
		glTranslatef(0, c_y, c_z);
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		for (int i = 0; i < 20; i++) {
			glVertex3f(0, 10, 10);
			glVertex3f(i, 10, 10);
		}
		glEnd();
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(c_x, 0, c_z);
		glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		for (int i = 0; i < 20; i++) {
			glVertex3f(0, 10, 10);
			glVertex3f(0, i - 10, 10);
		}
		glEnd();
		glPopMatrix();
	}
	{
		glPushMatrix();
		glTranslatef(c_x, c_y, 0);
		glBegin(GL_POINTS);
		glColor3f(0, 0, 1);
		for (int i = 0; i < 20; i++) {
			glVertex3f(0, 10, 10);
			glVertex3f(0, 10, 10 - i);
		}
		glEnd();
		glPopMatrix();
	}
}

void Draw_arrow(double rad) // 화살표 그리기
{
	glPushMatrix(); {
		glTranslatef(0, rad + 0.3, 0);
		{
			glPushMatrix();
			glTranslatef(0, 0.25, 0);
			glutSolidCube(0.5);
			glPopMatrix();
		}
		glRotatef(90, 1, 0, 0);
		glutSolidCone(0.5, 0.25, 20, 20);
	}
	glPopMatrix();
}

void Draw_Home(double rad)
{
	glPushMatrix(); {
		glTranslatef(0, 0, rad*1.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.3, 0.3, 0.3);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Front }
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
		glVertex3f(1.0f, -1.0f, 1.0f); // { Front }

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Right }
		glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
		glVertex3f(1.0f, -1.0f, -1.0f); // { Right }

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Back }
		glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f); // { Left }
		glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
		glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }
		glEnd();
	}
	glPopMatrix();
}
void Draw_Plane()
{
	{
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslatef(m_data.moveX[movenum], m_data.moveY[movenum], m_data.moveZ[movenum]);
		glRotated(-angle_xy, 0, 0, 1);
		glRotated(-angle_yz, 1, 0, 0);
		glRotated(angle_zx, 0, 1, 0);
		glColor3f(0, 0, 1);
		glScalef(1, 0.5, 0.5);
		glutSolidCube(1);
		if (roundTrip==1 && start==2)
		{
			glPushMatrix();
			glColor3f(1, 1, 0);
			glTranslatef(-0.6, 0, 0);
			glRotatef(pangle, 1, 0, 0);
			glScalef(0.2, 0.5, 2);
			glutSolidCube(1);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glColor3f(1, 1, 0);
			glTranslatef(0.6, 0, 0);
			glRotatef(pangle, 1, 0, 0);
			glScalef(0.2, 0.5, 2);
			glutSolidCube(1);
			glPopMatrix();
		}
		glPopMatrix();

	}
}

bool CollisionCheck(double x1, double x2, double y1, double y2, double z1, double z2, double rad1, double rad2)
{
	if (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2)) <= rad1 + rad2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		first_click_x = x;
		first_click_y = y;
		click = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		temp_x = yAngle;
		temp_y = xAngle;
	}
}

void Motion(int x, int y)
{
	yAngle = x - temp_x;
	xAngle = y - temp_y;
}
void Curve_calcu() {
	int k = 0;
	for (int n = 0; n < 30; n += 3) {
		float C1, C2, C3, C4;
		int i = 0;
		for (float t = 0.0; t < 1.0; t += 0.01) {
			C1 = (1 - t)*(1 - t)*(1 - t);
			C2 = 3 * t * (1 - t)*(1 - t);
			C3 = 3 * t*t*(1 - t);
			C4 = t*t*t;
			Move_data[k].moveX[i] = (C1*ctrlpoints[n][0]) + (C2*ctrlpoints[n + 1][0]) + (C3*ctrlpoints[n + 2][0]) + (C4*ctrlpoints[n + 3][0]);
			Move_data[k].moveY[i] = (C1*ctrlpoints[n][1]) + (C2*ctrlpoints[n + 1][1]) + (C3*ctrlpoints[n + 2][1]) + (C4*ctrlpoints[n + 3][1]);
			Move_data[k].moveZ[i] = (C1*ctrlpoints[n][2]) + (C2*ctrlpoints[n + 1][2]) + (C3*ctrlpoints[n + 2][2]) + (C4*ctrlpoints[n + 3][2]);
			++i;
		}
		k += 1;
	}
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			m_data.moveX[100 * i + j] = Move_data[i].moveX[j];
			m_data.moveY[100 * i + j] = Move_data[i].moveY[j];
			m_data.moveZ[100 * i + j] = Move_data[i].moveZ[j];
		}
	}
}
void Set_Position()
{

	// 행성들의 위치 초기화
	p[0].x = 0;
	p[0].y = 10;
	p[0].z = 10;
	p[0].R = rand() % 50 * 0.01 + 0.5;
	p[0].G = rand() % 50 * 0.01 + 0.5;
	p[0].B = rand() % 50 * 0.01 + 0.5;
	p[0].rad = rand() % 100 * 0.005 + 0.3;
	// 시작별
	p[14].x = 10;
	p[14].y = 0;
	p[14].z = 0;
	p[14].R = rand() % 50 * 0.01 + 0.5;
	p[14].G = rand() % 50 * 0.01 + 0.5;
	p[14].B = rand() % 50 * 0.01 + 0.5;
	p[14].rad = rand() % 100 * 0.005 + 0.3;
	// 끝별
	for (int i = 1; i < 14; i++)
	{
		p[i].rad = rand() % 100 * 0.005 + 0.3;
		p[i].x = rand() % 20 * 0.5 + 1;
		p[i].y = rand() % 20 * 0.5 + 1;
		p[i].z = rand() % 20 * 0.5 + 1;
		p[i].R = rand() % 50 * 0.01 + 0.5;
		p[i].G = rand() % 50 * 0.01 + 0.5;
		p[i].B = rand() % 50 * 0.01 + 0.5;
	}

	for (int i = 1; i<14; )
	{
		int nTemp = rand() % 16;

		if (bCheckExistOfNum[nTemp] == false)
		{
			bCheckExistOfNum[nTemp] = true;
			p[i].x = nTemp*0.5 + 1;
			++i;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		bCheckExistOfNum[i] = false;
	}
	for (int i = 1; i<14; )
	{
		int nTemp = rand() % 16;

		if (bCheckExistOfNum[nTemp] == false)
		{
			bCheckExistOfNum[nTemp] = true;
			p[i].y = nTemp*0.5 + 1;
			++i;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		bCheckExistOfNum[i] = false;
	}
	for (int i = 1; i<14; )
	{
		int nTemp = rand() % 16;

		if (bCheckExistOfNum[nTemp] == false)
		{
			bCheckExistOfNum[nTemp] = true;
			p[i].z = nTemp*0.5 + 1;
			++i;
		}
	}

}

void Draw_Collision(double x, double y, double z)
{
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(ex_time, ex_time, ex_time);
		glColor3f(1, 0, 0);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
	}
}

double innerproduct(double x1, double y1, double z1, double x2, double y2, double z2) // 내적해서 각도를 구한다
{
	return acos((x1*x2 + y1*y2 + z1*z2) / (sqrt((x1*x1) + (y1*y1) + (z1*z1))*sqrt((x2*x2) + (y2*y2) + (z2*z2))))*ANGLE_TO_RAD;
}


void Draw_Tree(double rad)
{
	glPushMatrix();
	glPopMatrix();
}