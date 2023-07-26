#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"
//��ʼ������
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	int i = 0;
	int j = 0;
	for(i=0;i<rows;i++)
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
}
//��ӡ������Ϣ
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("------ɨ����Ϸ------\n");
	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");//��������
	for (j = 0; j <= col; j++)
	{
		printf("%d|", j);
	}
	printf("\n-|�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");//��������
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d|", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c|", board[i][j]);
		}
		printf("\n");
	}
	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");//��������
	printf("------ɨ����Ϸ------\n\n");
}
//�����׵ĺ���
void Setmine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	//��1-9  ��1-9
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
//ͳ����Χ�����ĺ���
int get_mine_count(char board[ROWS][COLS], int x,int y)
{
	int count = 0;
	for(int i=-1;i<=1;i++)
		for (int j = -1; j <= 1; j++)
		{
			if (board[x + i][y + j] == '1')
				count++;
		}
	return count;

	/*return (board[x - 1][y] +
		board[x - 1][y - 1] +
		board[x][y - 1] +
		board[x + 1][y - 1] +
		board[x + 1][y] +
		board[x + 1][y + 1] +
		board[x][y + 1] +
		board[x - 1][y + 1] - 8 * '0');*/
}

//�ݹ飬չ��һƬ����ĺ���
void OpenArea(char mine[ROWS][COLS],char show[ROWS][COLS], int row, int col,int x, int y)
{
	int count = get_mine_count(mine, x, y);
	if (count == 0) 
	{
		show[x][y] = ' ';
		for (int i = x - 1; i <= x + 1; i++) 
		{
			for (int j = y - 1; j <= y + 1; j++) 
			{
				if (show[i][j] == '*' && x >= 1 && x <= row && y >= 1 && y <= col) 
				{
					OpenArea(mine, show,ROW,COL, i, j);
				}
			}
		}
	}
	else 
	{
		show[x][y] = count + '0';
	}
}

// ������׺ͷǱ�ǵ�λ�ø���
int get_win(char board[ROWS][COLS], int row, int col)
{
	int win = 0;
	for(int i=1;i<=row;i++)
		for (int j = 1; j <= col; j++)
		{
			if (board[i][j]!='*'&&board[i][j]!='!')
				win++;
		}
	return win;
}

//���׵ĺ���
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	 //1.�����Ų������
     //2.�������괦�ǲ�����
	 //(1) ����   - ���ź����㱻ը���� - ��Ϸ����
	 //(2) ������ - ͳ��������Χ�м����� - �洢�Ų��׵���Ϣ��show���飬��Ϸ����
	int x = 0;
	int y = 0;
	int win = 0;
	int select = 0;

	while (win < row * col - EASY_COUNT)
	{
		printf("��ѡ��1.�Ų��� 2.����� 3.ȡ�����\t");
		scanf("%d", &select);
		if (select == 1) 
		{
			printf("������Ҫ�Ų��׵����꣺>");
			scanf("%d %d", &x, &y);
			//�ж�����Ϸ���
			if (x >= 1 && x <= row && y >= 1 && y <= col) 
			{
				if (show[x][y] == '*')
				{
					if (mine[x][y] == '1')
					{
						printf("\n\n���ź����㱻ը���ˣ�\n");
						printf("�׵ķֲ���������У�'1'��ʾ�ף���\n");
						DisplayBoard(mine, ROW, COL);
						break;
					}
					else
					{
						OpenArea(mine, show,ROW,COL, x, y);
						//��ʾ�Ų������Ϣ
						DisplayBoard(show, ROW, COL);
						//�����Ѿ��ų��ķ���λ�õĸ���
						win = get_win(show, ROW, COL);
					}
				}
				else
				{
					printf("��λ���ѱ��Ų�������������룡\n");
				}
			}
			else
			{
				printf("���겻�Ϸ������������룡\n");
			}
		}
		else if (select == 2)
		{
			printf("������Ҫ��ǵ����꣺>");
			scanf("%d %d", &x, &y);
			//�ж�����Ϸ���
			if (x >= 1 && x <= row && y >= 1 && y <= col) 
			{
				if (show[x][y] == '*')
				{
					show[x][y] = '!';
					DisplayBoard(show, ROW, COL);
				}
				else if(show[x][y]=='!')
				{
					printf("��λ���ѱ���ǣ�������ѡ��\n");
				}
				else
				{
					printf("��λ�ò��ܱ�ǣ�������ѡ��\n");
				}
			}
			else 
			{
				printf("���겻�Ϸ������������룡\n");
			}
		}
		else if (select == 3)
		{
			printf("������Ҫȡ����ǵ����꣺>");
			scanf("%d %d", &x, &y );
			if (x >= 1 && x <= row && y >= 1 && y <= col)
			{
				if (show[x][y] == '!')
				{
					show[x][y] = '*';
					DisplayBoard(show, ROW, COL);
				}
				else
				{
					printf("��λ�ò���ȡ����ǣ�������ѡ��\n");
				}
			}
			else
			{
				printf("���겻�Ϸ������������룡\n");
			}
		}
		else 
		{
			printf("�����������������룡\n");
		}
		
		//printf("win=%d\n", win);
	}
	if (win == row * col - EASY_COUNT) 
	{
		printf("\n��ϲ�㣬���׳ɹ���\n");
		printf("�׵ķֲ���������У�'1'��ʾ�ף���\n");
		DisplayBoard(mine, ROW, COL);
	}
}

//��������+��չ����
//1.��ǹ��ܣ���'!'��
//2.չ��һƬ����Ĺ��ܣ�ʹ�õݹ飩      
//*���Ų���x��y����ʱ����1�������겻����  ��2����������Χû����  ��3��������û�б��Ų��
