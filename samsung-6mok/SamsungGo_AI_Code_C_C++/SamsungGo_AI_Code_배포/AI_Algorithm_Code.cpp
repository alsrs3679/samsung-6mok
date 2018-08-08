// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�					"TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"					������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.

3. AI ������ �׽�Ʈ �Ͻ� ���� "���� �˰����ȸ ��"�� ����մϴ�.

4. ���� �˰��� ��ȸ ���� �����ϱ⿡�� �ٵϵ��� ���� ��, �ڽ��� "����" �� �� �˰����� �߰��Ͽ� �׽�Ʈ �մϴ�.



[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
void domymove(int x[], int y[], cnt) : �� ������ ��ǥ�� �����ؼ� ���


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:Winlab,Department:INU" };
#define BOARD_SIZE 20
int myboard[21][21];
float weight[21][21];

FILE *check = NULL;
void setweight(int cnt)
{
	int count = 0;
	////����
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (myboard[y + 1][x + 1] == 1 || myboard[y + 1][x + 1] == 3)
				count++;
			else
			{
				weight[y + 1][x + 1] += count;
				weight[y - count][x + 1] += count;
				count = 0;
			}
		}
	}



	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (myboard[y + 1][x + 1] == 1 || myboard[y + 1][x + 1] == 3)
				count++;
			else
			{

				weight[y + 1][x + 1] += count;
				weight[y + 1][x - count] += count;
				count = 0;
			}
		}
	}

	////////////////////////////////////////////////////////////////////
	for (int x = 0; x < BOARD_SIZE - 1; x++)
	{
		for (int y = 0; y <= x + 1; y++)
		{
			if (myboard[y + 1][x + 1 - y] == 1 || myboard[y + 1][x + 1 - y] == 3)
				count++;
			else
			{

				weight[y + 1][x + 1 - y] += count;
				weight[y - count][x + 1 - y + count + 1] += count;
				count = 0;
			}
		}
	}


	for (int x = 0; x < BOARD_SIZE - 2; x++)
	{
		for (int y = 0; y <= x + 1; y++)
		{
			if (myboard[y + 19 - x][19 - y] == 1 || myboard[y + 19 - x][19 - y] == 3)
				count++;
			else
			{

				weight[y + 19 - x][19 - y] += count;
				weight[y - count + 18 - x][20 - y + count] += count;
				count = 0;
			}
		}
	}

	///////////////////////////////////////////////////////////////////

	for (int x = 0; x < BOARD_SIZE - 1; x++)
	{
		for (int y = 0; y <= x + 1; y++)
		{
			if (myboard[y + 1][y + 19 - x] == 1 || myboard[y + 1][y + 19 - x] == 3)
				count++;
			else
			{

				weight[y + 1][y + 19 - x] += count;
				weight[y - count][y + 19 - x - count - 1] += count;
				count = 0;
			}
		}
	}


	for (int x = 0; x < BOARD_SIZE - 2; x++)
	{
		for (int y = 0; y <= x + 1; y++)
		{
			if (myboard[y + 19 - x][y + 1] == 1 || myboard[y + 19 - x][y + 1] == 3)
				count++;
			else
			{

				weight[y + 19 - x][y + 1] += count;
				weight[y - count + 18 - x][y + 1 - count - 1] += count;
				count = 0;
			}
		}
	}
}

void myturn(int cnt) {

	int x[2], y[2];

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	for (int q = 0; q < cnt; q++)
	{
		int max = 0, index_x = 0, index_y = 0;

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
			{
				myboard[i + 1][j + 1] = showBoard(i, j);
				weight[i + 1][j + 1] = 0;
			}
		}



		if (q == 1)
			myboard[x[0] + 1][y[0] + 1] = 1;

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (myboard[i + 1][j + 1] == 1 || myboard[i + 1][j + 1] == 3 || myboard[i + 1][j + 1] == 2)
					weight[i + 1][j + 1] = INT_MIN;
			}
		}

		setweight(q);

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (max < weight[i + 1][j + 1])
				{
					max = weight[i + 1][j + 1];
					index_x = i;
					index_y = j;
				}
			}
		}
		x[q] = index_x;
		y[q] = index_y;

		check = fopen("check.txt", "a");
		fprintf(check, "(%d, %d)\n", index_x, index_y);
		fclose(check);

		if (terminateAI) return;
		//if (!isFree(x[q], y[q]))
		//	q--;
	}



	//srand((unsigned)time(NULL));

	//for (int i = 0; i < cnt; i++) {
	//	do {
	//		x[i] = rand() % width;
	//		y[i] = rand() % height;
	//		if (terminateAI) return;
	//	} while (!isFree(x[i], y[i]));

	//	if (x[1] == x[0] && y[1] == y[0]) i--;
	//}

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);


	fp = fopen("weight.txt", "w");


	for (int j = 0; j< BOARD_SIZE - 1; j++)

	{
		for (int i = 0; i < BOARD_SIZE - 1; i++)
		{
			fprintf(fp, "%6.f ", weight[i + 1][j + 1]);
		}

		fprintf(fp, "\n");
	}
	fclose(fp);

}