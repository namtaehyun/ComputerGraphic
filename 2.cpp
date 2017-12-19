#include <stdio.h>
#include <math.h>
//저장 리스트 만들기
// 점 (x,y,z)와 원점에서의 거리를 저장하는 리스트를 만든다. 점 데이터는 구조체배열
//최대 10개의 데이터를 저장한다.
//양쪽 끝에 입력 또는 출력하는 명령어를 입력받아 실행
//명령후 결과 리스트를 출력하고 리스트

struct Matrix
{
int x, y, z; // x,y,z좌표값
int dis;
bool exist;
};
bool Yesorno(Matrix * mat);
bool Yesorno2(Matrix * mat);
void PrintMax(Matrix * mat);
void PrintMin(Matrix * mat);


void main()
{
	char s; // switch
	int idx= 0;  //밑에 추가
	int numOfData=0;
	Matrix mat[10];
	for (int i = 0; i < 10; i++)
	{
		mat[i].exist = false;
	}

	while (1) {
		scanf("%c", &s);
		switch (s)
		{
		case '+': // 리스트의 맨 위에 넣는다
			if (Yesorno(mat) == false) {
				printf("x,y,z좌표를 삽입하세요");
				scanf("%d %d %d", &mat[idx].x, &mat[idx].y, &mat[idx].z);
				mat[idx].dis = sqrt(mat[idx].x*mat[idx].x + mat[idx].y*mat[idx].y + mat[idx].z*mat[idx].z);
				mat[idx].exist = true;
				idx++;
				numOfData++;
			}
			else
			{
				printf("리스트가 꽉찼습니다. \n");
			}
			break;
		case '-': // 리스트의 맨 위에서 뺀다
			if (Yesorno2(mat) == false) {
				idx--;
				printf("%d층 x : %d y : %d z : %d", idx + 1, mat[idx].x, mat[idx].y, mat[idx].z);
				mat[idx].exist = false;
				numOfData--;
			}
			else
			{
				printf("리스트가 비었습니다. \n");
			}
			break;
		case 'e': // 리스트의 맨 아래에 넣는다
			if (Yesorno(mat) == false&&mat[0].exist==true) {
				for (int i = idx; i > 0; i--)
				{
					mat[i].x = mat[i - 1].x;
					mat[i].y = mat[i - 1].y;
					mat[i].z = mat[i - 1].z;
					mat[i].dis = mat[i - 1].dis;
					mat[i - 1].exist = false;
					mat[i].exist = true;
				}
				printf("x,y,z좌표를 삽입하세요");
				scanf("%d %d %d", &mat[idx - numOfData].x, &mat[idx - numOfData].y, &mat[idx - numOfData].z);
				mat[idx - numOfData].dis = sqrt(mat[idx - numOfData].x*mat[idx - numOfData].x + mat[idx].y*mat[idx - numOfData].y + mat[idx - numOfData].z*mat[idx - numOfData].z);
				mat[idx - numOfData].exist = true;
				numOfData++;
				idx++;
			}
			else if (Yesorno(mat) == false && mat[0].exist == false)
			{
				printf("x,y,z좌표를 삽입하세요");
				scanf("%d %d %d", &mat[0].x, &mat[0].y, &mat[0].z);
				mat[0].dis = sqrt(mat[0].x*mat[0].x + mat[0].y*mat[0].y + mat[0].z*mat[0].z);
				mat[0].exist = true;
				numOfData++;
			}
			else
			{
				printf("리스트가 꽉찼습니다. \n");
			}
			break;
		case 'd': //리스트의 맨 아래에서 뺀다
			if (Yesorno2(mat) == false) {
				printf("%d층 x : %d y : %d z : %d", idx - numOfData + 1, mat[idx - numOfData].x, mat[idx - numOfData].y, mat[idx - numOfData].z);
				mat[idx - numOfData].exist = false;
				numOfData--;
			}
			else
			{
				printf("리스트가 비었습니다. \n");
			}
			break;
		case 'l': // 리스트의 길이를 출력
			printf("리스트의 길이 :%d \n", numOfData);
			break;
		case 'c': // 리스트를 비운다
			for (int i = 0; i < 10; i++)
			{
				mat[i].exist = false;
			}
			numOfData = 0;
			idx = 0;
			break;
		case 'm': // 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다
			PrintMax(mat);
			break;
		case 'n': // 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다
			PrintMin(mat);
			break;
		case 'k':
			printf("현재 리스트 상황 \n");
			for (int i =9; i > -1; i--)
			{
				if (mat[i].exist == true) {
					printf("%d 층", i + 1);
					printf("(x,y,z) = %d %d %d 거리 :%d \n", mat[i].x, mat[i].y, mat[i].z, mat[i].dis);
				}
				else
				{
					printf("%d 층은 비었습니다. \n", i + 1);
				}
			}
			break;
		case 'q': // 프로그램을 종료한다
			return;
		}
	}
	return;
}

void PrintMax(Matrix * mat)
{
	Matrix a;
	int max=0;
	for (int i = 0; i < 10; i++)
	{
		if (max < mat[i].dis&&mat[i].dis<100&& mat[i].dis>0 && mat[i].exist == true)
		{
			a.x = mat[i].x;
			a.y = mat[i].y;
			a.z = mat[i].z;
			a.dis = mat[i].dis;
			max = a.dis;
		}
	}
	printf("가장 먼 점(x,y,z) : %d %d %d \n", a.x, a.y, a.z);
}

void PrintMin(Matrix * mat)
{
	Matrix a;
	int min = 1000;
	for (int i = 0; i < 10; i++)
	{
		if (min > mat[i].dis&&mat[i].dis<100 && mat[i].dis>0 &&mat[i].exist==true)
		{
			a.x = mat[i].x;
			a.y = mat[i].y;
			a.z = mat[i].z;
			a.dis = mat[i].dis;
			min = a.dis;
		}
	}
	printf("가장 가까운 점(x,y,z) : %d %d %d \n", a.x, a.y, a.z);
}


bool Yesorno (Matrix * mat)
{
	int count=0;
	for (int i = 0; i < 10; i++)
	{
		if (mat[i].exist == true) //차있음
		{
			count++;
		}
	}
	if (count < 10)
	{
		return false; //비어있음
	}
	else
	{
		return true;
	}
}


bool Yesorno2(Matrix * mat)
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		if (mat[i].exist == false) //차있음
		{
			count++;
		}
	}
	if (count < 10)
	{
		return false; //비어있음
	}
	else
	{
		return true;
	}
}