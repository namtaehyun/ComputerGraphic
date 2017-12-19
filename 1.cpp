#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 행렬 다루기
// 1 3X3 행렬의 덧셈
// 2 뺄셈
// 3 Determinent값
// 4 3X3 행렬을 4X4행렬로 변환

void main()
{

	int matrix[4][4];
	int matrix2[4][4];
	int katrix[4][4]; //곱셈결과
	int det=0;
	int num=0;
	bool mat = false; // mat값이 0이면 3X3 1이면 4X4

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
			matrix2[i][j] = 0;
		}
	}
	matrix[3][3] = 1;
	matrix2[3][3] = 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = rand() % 2;
			matrix2[i][j] = rand() % 2;
		}
	}

	while (1) // 1번출력 2번덧셈
	{
		scanf("%d", &num);
		switch (num) {
		case 1:
			if (mat == 0)// 출력
			{
				printf("A행렬\n");
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						printf("%d ", matrix[i][j]);
					}
					printf("\n");
				}
				printf("B행렬\n");
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						printf("%d ", matrix2[i][j]);
					}
					printf("\n");
				}

			}
			else
			{
				printf("A행렬\n");
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						printf("%d ", matrix[i][j]);
					}
					printf("\n");
				}
				printf("B행렬\n");
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						printf("%d ", matrix2[i][j]);
					}
					printf("\n");
				}
			}
			break;
		case 2:
			printf("덧셈 완료 1번을 누르면 덧셈결과 출력");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix[i][j] += matrix2[i][j];
				}
			}
			break;
		case 3:
			printf("뺄셈 완료 1번을 누르면 덧셈결과 출력");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix[i][j] -= matrix2[i][j];
				}
			}
			break;
		case 4:
			printf("곱셈 완료 \n");
			for (int i = 0; i < 3; i++)
			{
				katrix[0][i] = matrix[0][0] * matrix2[0][i]+ matrix[0][1] * matrix2[1][i]+ matrix[0][2] * matrix2[2][i];
				katrix[1][i] = matrix[1][0] * matrix2[0][i] + matrix[1][1] * matrix2[1][i] + matrix[1][2] * matrix2[2][i];
				katrix[2][i] = matrix[2][0] * matrix2[0][i] + matrix[2][1] * matrix2[1][i] + matrix[2][2] * matrix2[2][i];
			}
			if (mat == false)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						printf("%d ", katrix[i][j]);
					}
					printf("\n");
				}
			}
			else {
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						printf("%d ", katrix[i][j]);
					}
					printf("\n");
				}
			}
			break;
		case 5:
			det = matrix[0][0]* matrix[1][1]* matrix[2][2]+ matrix[0][1] * matrix[1][2] * matrix[2][0]+ matrix[0][2] * matrix[1][0] * matrix[2][1]-matrix[0][1]* matrix[1][0]* matrix[2][2]- matrix[0][0] * matrix[1][2] * matrix[2][1]- matrix[0][2] * matrix[1][1] * matrix[2][0];
			printf("determinent = %d", det);
			break;
		case 6:
			if (mat == false)
			{
				mat = true;
			}
			else
			{
				mat = false;
			}
			break;
		}
	}
	return;
}