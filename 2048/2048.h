#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 4
#define LONG 5 * SIZE + SIZE
#define WIDE SIZE * 2 + 4 + 1
#define COLSIZE LONG *WIDE
int nums[SIZE][SIZE] = {0};
int count = 0;
int victory();
int defeat();
void newNum();
void setSize(int collong, int colwide);
int getScores();
void interface();
//定义初始数字
void original_nums()
{
	srand((unsigned int)time(NULL));
	int x1 = rand() % SIZE;
	int x2 = 0;
	do
	{
		x2 = rand() % SIZE;
	} while (x2 == x1);
	nums[x1][x1] = 2;
	nums[x2][x2] = 2;
}
//渲染界面:定义窗口大小
void setSize(int conlong, int conwide)
{
	char cmd[COLSIZE];
	sprintf(cmd, "mode con cols=%d lines=%d", conlong, conwide);
	system(cmd);
}
//渲染界面:绘制地图
void interface()
{
	// system("mode con cols=24 lines=12");
	setSize(LONG, WIDE);
	system("color 8B");
	printf("your steps:%d\n", count);
	printf("your scores:%d\n", getScores());
	printf("-----------------------\n");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%5d", nums[i][j]);
			printf("|");
		}
		printf("\n");
		printf("-----------------------\n");
	}
}
//移动数字 && 判断游戏结束
void move()
{

	do
	{
		char mov = getchar();
		count++;
		if (mov == 'a' || mov == 'A')
		{
			int x = 0;
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 1; j < SIZE; j++)
				{
					if (nums[i][j] != 0)
					{
						for (int k = j - 1; k >= 0; k--)
						{
							if (nums[i][k] != 0)
							{
								if (nums[i][k] == nums[i][j] && nums[i][k] != x)
								{
									nums[i][k] *= 2;
									x = nums[i][k];
									nums[i][j] = 0;
									j = -1;
								}
								break;
							}
						}
					}
				}
				for (int j = 0; j < SIZE; j++)
				{
					if (nums[i][j] == 0)
					{
						for (int k = j + 1; k < SIZE; k++)
						{
							if (nums[i][k] != 0)
							{
								for (int l = j; l < SIZE - 1; l++)
								{
									nums[i][l] = nums[i][l + 1];
								}
								nums[i][SIZE - 1] = 0;
								j = -1;
								break;
							}
						}
					}
				}
			}
		}
		else if (mov == 'd' || mov == 'D')
		{
			for (int i = 0; i < SIZE; i++)
			{
				int x = 0;
				for (int j = 2; j >= 0; j--)
				{
					if (nums[i][j] != 0)
					{
						for (int k = j + 1; k < SIZE; k++)
						{
							if (nums[i][k] != 0)
							{
								if (nums[i][k] == nums[i][j] && nums[i][k] != x)
								{
									nums[i][k] *= 2;
									x = nums[i][k];
									nums[i][j] = 0;
									j = SIZE + 1;
								}
								break;
							}
						}
					}
				}
				for (int j = SIZE - 1; j >= 0; j--)
				{
					if (nums[i][j] == 0)
					{
						for (int k = j - 1; k >= 0; k--)
						{
							if (nums[i][k] != 0)
							{
								for (int l = j; l >= 1; l--)
								{
									nums[i][l] = nums[i][l - 1];
								}
								nums[i][0] = 0;
								j = SIZE;
								break;
							}
						}
					}
				}
			}
		}
		else if (mov == 'w' || mov == 'W')
		{
			for (int j = 0; j < SIZE; j++)
			{
				int x = 0;
				for (int i = 1; i < SIZE; i++)
				{
					if (nums[i][j] != 0)
					{
						for (int k = i - 1; k >= 0; k--)
						{
							if (nums[k][j] != 0)
							{
								if (nums[k][j] == nums[i][j] && nums[k][j] != x)
								{
									nums[k][j] *= 2;
									x = nums[k][j];
									nums[i][j] = 0;
									i = -1;
								}
								break;
							}
						}
					}
				}
				for (int i = 0; i < SIZE; i++)
				{
					if (nums[i][j] == 0)
					{
						for (int k = i + 1; k < SIZE; k++)
						{
							if (nums[k][j] != 0)
							{
								for (int l = i; l < SIZE - 1; l++)
								{
									nums[l][j] = nums[l + 1][j];
								}
								nums[SIZE - 1][j] = 0;
								i = -1;
								break;
							}
						}
					}
				}
			}
		}
		else if (mov == 's' || mov == 'S')
		{
			for (int j = 0; j < SIZE; j++)
			{
				int x = 0;
				for (int i = 2; i >= 0; i--)
				{
					if (nums[i][j] != 0)
					{
						for (int k = i + 1; k < SIZE; k++)
						{
							if (nums[k][j] != 0)
							{
								if (nums[k][j] == nums[i][j] && nums[k][j] != x)
								{
									nums[k][j] *= 2;
									x = nums[k][j];
									nums[i][j] = 0;
									i = SIZE + 1;
								}
								break;
							}
						}
					}
				}
				for (int i = SIZE - 1; i >= 0; i--)
				{
					if (nums[i][j] == 0)
					{
						for (int k = i - 1; k >= 0; k--)
						{
							if (nums[k][j] != 0)
							{
								for (int l = i; l >= 0; l--)
								{
									nums[l][j] = nums[l - 1][j];
								}
								nums[0][j] = 0;
								i = SIZE;
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			count--;
			continue;
		}
		getchar();
		newNum();
		interface();
	} while (!defeat() && !victory());
}
//产生新数
void newNum()
{
	int y1, y2;
	int out = 0;
	do
	{
		y1 = rand() % SIZE;
		y2 = rand() % SIZE;

		if (nums[y1][y2] == 0)
		{
			out++;
			nums[y1][y2] = pow(2, ((rand() % (count / 6 + 1) + 1)));
			if (nums[y1][y2] > 16)
			{
				nums[y1][y2] = 16;
			}
		}
	} while (!out);
}
//判断游戏失败
int defeat()
{
	int def = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (nums[i][j] == 0)
			{
				def = 0;
				break;
			}
		}
		if (def == 0)
		{
			break;
		}
	}
	if (def == 1)
	{
		printf("defeat!\n");
	}
	return def;
}
//判断游戏胜利
int victory()
{
	int vic = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (nums[i][j] == 2048)
			{
				printf("victory!\n");
				//printf("你走了%d步！\n", count);
				vic = 1;
			}
		}
	}
	return vic;
}
//计算得分
int getScores()
{
	int scores = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			scores += nums[i][j];
		}
	}
	return scores;
}