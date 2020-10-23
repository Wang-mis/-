#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
#define LONG SIZE * 5 + 1
#define WIDE SIZE * 2 + 5
void consize(int conlong, int conwide);
void random_player();
void interface();
void player_operate();
int victory();
int map[SIZE][SIZE] = {0};
int sel = 0;
//渲染界面：定义窗口大小
void consize(int conlong, int conwide)
{
	char cmd[LONG * WIDE];
	sprintf(cmd, "mode con cols=%d lines=%d", conlong, conwide);
	system(cmd);
	system("color 8B");
}
//渲染界面：绘制地图
void interface()
{
	consize(LONG, WIDE);
	printf("Thinking Player:");
	if (sel == 1)
	{
		printf("黑子\n");
	}
	else
	{
		printf("白子\n");
	}
	for (int i = 0; i < SIZE; i++)
	{
		printf("-----");
	}
	printf("-");
	printf("\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("|");
		for (int j = 0; j < SIZE; j++)
		{
			printf("%4d|", map[i][j]);
		}
		for (int k = 0; k < SIZE; k++)
		{
			printf("-----");
		}
		printf("-");
		printf("\n");
	}
}
//选择先手玩家
void random_player()
{
	printf("请选择先手，1表示黑子，2表示白子,3表示随机：");
	scanf("%d", &sel);
	if (sel == 3)
	{
		srand((unsigned int)time(NULL));
		do
		{
			sel = rand() % 3; //1为黑子，2为白子
		} while (sel == 0);
	}
}
//玩家操作
void player_operate()
{
	int i, j;
	do
	{
		scanf("%d %d", &i, &j);
		if (map[i][j] == 0)
		{
			map[i][j] = sel;
		}
		else
		{
			continue;
		}
		if (sel == 1)
		{
			sel = 2;
		}
		else
		{
			sel = 1;
		}
		interface();
	} while (!victory());
}
//判断游戏胜利
int victory()
{
	int count1 = 0, count2 = 0;
	//检验横排
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (map[i][j] == 1)
			{
				count2 = 0;
				count1++;
				if (count1 == 5)
				{
					printf("黑子获胜\n");
					return 1;
				}
			}
			else if (map[i][j] == 2)
			{
				count1 = 0;
				count2++;
				if (count2 == 5)
				{
					printf("白子获胜\n");
					return 2;
				}
			}
			else
			{
				count1 = 0;
				count2 = 0;
			}
		}
		count1 = 0;
		count2 = 0;
	}
	//检验竖排
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (map[i][j] == 1)
			{
				count2 = 0;
				count1++;
				if (count1 == 5)
				{
					printf("黑子获胜\n");
					return 1;
				}
			}
			else if (map[i][j] == 2)
			{
				count1 = 0;
				count2++;
				if (count2 == 5)
				{
					printf("白子获胜\n");
					return 2;
				}
			}
			else
			{
				count1 = 0;
				count2 = 0;
			}
		}
		count1 = 0;
		count2 = 0;
	}
	//检验对角线
	for (int i = 0; i < SIZE - 4; i++)
	{
		for (int j = 0; j < SIZE - 4; j++)
		{
			if (map[i][j] == 1)
			{
				count1++;
				for (int ii = i + 1, jj = j + 1; ii < i + 5; ii++, jj++)
				{
					if (map[ii][jj] == 1)
					{
						count1++;
					}
					else
					{
						break;
					}
					if (count1 == 5)
					{
						printf("黑子获胜\n");
						return 1;
					}
				}
			}
			if (map[i][j] == 2)
			{
				count2++;
				for (int ii = i + 1, jj = j + 1; ii < i + 5; ii++, jj++)
				{
					if (map[ii][jj] == 2)
					{
						count2++;
					}
					else
					{
						break;
					}
					if (count2 == 5)
					{
						printf("白子获胜\n");
						return 2;
					}
				}
			}
			count1 = 0;
			count2 = 0;
		}
	}
	return 0;
}