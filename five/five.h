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
//��Ⱦ���棺���崰�ڴ�С
void consize(int conlong, int conwide)
{
	char cmd[LONG * WIDE];
	sprintf(cmd, "mode con cols=%d lines=%d", conlong, conwide);
	system(cmd);
	system("color 8B");
}
//��Ⱦ���棺���Ƶ�ͼ
void interface()
{
	consize(LONG, WIDE);
	printf("Thinking Player:");
	if (sel == 1)
	{
		printf("����\n");
	}
	else
	{
		printf("����\n");
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
//ѡ���������
void random_player()
{
	printf("��ѡ�����֣�1��ʾ���ӣ�2��ʾ����,3��ʾ�����");
	scanf("%d", &sel);
	if (sel == 3)
	{
		srand((unsigned int)time(NULL));
		do
		{
			sel = rand() % 3; //1Ϊ���ӣ�2Ϊ����
		} while (sel == 0);
	}
}
//��Ҳ���
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
//�ж���Ϸʤ��
int victory()
{
	int count1 = 0, count2 = 0;
	//�������
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
					printf("���ӻ�ʤ\n");
					return 1;
				}
			}
			else if (map[i][j] == 2)
			{
				count1 = 0;
				count2++;
				if (count2 == 5)
				{
					printf("���ӻ�ʤ\n");
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
	//��������
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
					printf("���ӻ�ʤ\n");
					return 1;
				}
			}
			else if (map[i][j] == 2)
			{
				count1 = 0;
				count2++;
				if (count2 == 5)
				{
					printf("���ӻ�ʤ\n");
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
	//����Խ���
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
						printf("���ӻ�ʤ\n");
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
						printf("���ӻ�ʤ\n");
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