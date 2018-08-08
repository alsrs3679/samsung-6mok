// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI 코드 작성 방법]

1. char info[]의 배열 안에					"TeamName:자신의 팀명,Department:자신의 소속"					순서로 작성합니다.
( 주의 ) Teamname:과 Department:는 꼭 들어가야 합니다.
"자신의 팀명", "자신의 소속"을 수정해야 합니다.

2. 아래의 myturn() 함수 안에 자신만의 AI 코드를 작성합니다.

3. AI 파일을 테스트 하실 때는 "육목 알고리즘대회 툴"을 사용합니다.

4. 육목 알고리즘 대회 툴의 연습하기에서 바둑돌을 누른 후, 자신의 "팀명" 이 들어간 알고리즘을 추가하여 테스트 합니다.



[변수 및 함수]
myturn(int cnt) : 자신의 AI 코드를 작성하는 메인 함수 입니다.
int cnt (myturn()함수의 파라미터) : 돌을 몇 수 둬야하는지 정하는 변수, cnt가 1이면 육목 시작 시  한 번만  두는 상황(한 번), cnt가 2이면 그 이후 돌을 두는 상황(두 번)
int  x[0], y[0] : 자신이 둘 첫 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
int  x[1], y[1] : 자신이 둘 두 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
void domymove(int x[], int y[], cnt) : 둘 돌들의 좌표를 저장해서 출력


//int board[BOARD_SIZE][BOARD_SIZE]; 바둑판 현재상황 담고 있어 바로사용 가능함. 단, 원본데이터로 수정 절대금지
// 놓을수 없는 위치에 바둑돌을 놓으면 실격패 처리.

boolean ifFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int showBoard(int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:Winlab,Department:INU" };
#define BOARD_SIZE 20
int myboard[21][21];
float weight[21][21];

FILE *check = NULL;
void setweight(int cnt)
{
	int count = 0;
	////세로
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

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

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

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
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