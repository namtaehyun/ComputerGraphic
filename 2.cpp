#include <stdio.h>
#include <math.h>
//���� ����Ʈ �����
// �� (x,y,z)�� ���������� �Ÿ��� �����ϴ� ����Ʈ�� �����. �� �����ʹ� ����ü�迭
//�ִ� 10���� �����͸� �����Ѵ�.
//���� ���� �Է� �Ǵ� ����ϴ� ��ɾ �Է¹޾� ����
//����� ��� ����Ʈ�� ����ϰ� ����Ʈ

struct Matrix
{
int x, y, z; // x,y,z��ǥ��
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
	int idx= 0;  //�ؿ� �߰�
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
		case '+': // ����Ʈ�� �� ���� �ִ´�
			if (Yesorno(mat) == false) {
				printf("x,y,z��ǥ�� �����ϼ���");
				scanf("%d %d %d", &mat[idx].x, &mat[idx].y, &mat[idx].z);
				mat[idx].dis = sqrt(mat[idx].x*mat[idx].x + mat[idx].y*mat[idx].y + mat[idx].z*mat[idx].z);
				mat[idx].exist = true;
				idx++;
				numOfData++;
			}
			else
			{
				printf("����Ʈ�� ��á���ϴ�. \n");
			}
			break;
		case '-': // ����Ʈ�� �� ������ ����
			if (Yesorno2(mat) == false) {
				idx--;
				printf("%d�� x : %d y : %d z : %d", idx + 1, mat[idx].x, mat[idx].y, mat[idx].z);
				mat[idx].exist = false;
				numOfData--;
			}
			else
			{
				printf("����Ʈ�� ������ϴ�. \n");
			}
			break;
		case 'e': // ����Ʈ�� �� �Ʒ��� �ִ´�
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
				printf("x,y,z��ǥ�� �����ϼ���");
				scanf("%d %d %d", &mat[idx - numOfData].x, &mat[idx - numOfData].y, &mat[idx - numOfData].z);
				mat[idx - numOfData].dis = sqrt(mat[idx - numOfData].x*mat[idx - numOfData].x + mat[idx].y*mat[idx - numOfData].y + mat[idx - numOfData].z*mat[idx - numOfData].z);
				mat[idx - numOfData].exist = true;
				numOfData++;
				idx++;
			}
			else if (Yesorno(mat) == false && mat[0].exist == false)
			{
				printf("x,y,z��ǥ�� �����ϼ���");
				scanf("%d %d %d", &mat[0].x, &mat[0].y, &mat[0].z);
				mat[0].dis = sqrt(mat[0].x*mat[0].x + mat[0].y*mat[0].y + mat[0].z*mat[0].z);
				mat[0].exist = true;
				numOfData++;
			}
			else
			{
				printf("����Ʈ�� ��á���ϴ�. \n");
			}
			break;
		case 'd': //����Ʈ�� �� �Ʒ����� ����
			if (Yesorno2(mat) == false) {
				printf("%d�� x : %d y : %d z : %d", idx - numOfData + 1, mat[idx - numOfData].x, mat[idx - numOfData].y, mat[idx - numOfData].z);
				mat[idx - numOfData].exist = false;
				numOfData--;
			}
			else
			{
				printf("����Ʈ�� ������ϴ�. \n");
			}
			break;
		case 'l': // ����Ʈ�� ���̸� ���
			printf("����Ʈ�� ���� :%d \n", numOfData);
			break;
		case 'c': // ����Ʈ�� ����
			for (int i = 0; i < 10; i++)
			{
				mat[i].exist = false;
			}
			numOfData = 0;
			idx = 0;
			break;
		case 'm': // �������� ���� �� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�
			PrintMax(mat);
			break;
		case 'n': // �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�
			PrintMin(mat);
			break;
		case 'k':
			printf("���� ����Ʈ ��Ȳ \n");
			for (int i =9; i > -1; i--)
			{
				if (mat[i].exist == true) {
					printf("%d ��", i + 1);
					printf("(x,y,z) = %d %d %d �Ÿ� :%d \n", mat[i].x, mat[i].y, mat[i].z, mat[i].dis);
				}
				else
				{
					printf("%d ���� ������ϴ�. \n", i + 1);
				}
			}
			break;
		case 'q': // ���α׷��� �����Ѵ�
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
	printf("���� �� ��(x,y,z) : %d %d %d \n", a.x, a.y, a.z);
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
	printf("���� ����� ��(x,y,z) : %d %d %d \n", a.x, a.y, a.z);
}


bool Yesorno (Matrix * mat)
{
	int count=0;
	for (int i = 0; i < 10; i++)
	{
		if (mat[i].exist == true) //������
		{
			count++;
		}
	}
	if (count < 10)
	{
		return false; //�������
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
		if (mat[i].exist == false) //������
		{
			count++;
		}
	}
	if (count < 10)
	{
		return false; //�������
	}
	else
	{
		return true;
	}
}