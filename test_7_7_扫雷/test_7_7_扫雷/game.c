#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"
//初始化棋盘
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
//打印棋盘信息
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("------扫雷游戏------\n");
	printf("════════════════════\n");//美化棋盘
	for (j = 0; j <= col; j++)
	{
		printf("%d|", j);
	}
	printf("\n-|══════════════════");//美化棋盘
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
	printf("════════════════════\n");//美化棋盘
	printf("------扫雷游戏------\n\n");
}
//设置雷的函数
void Setmine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	//行1-9  列1-9
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
//统计周围雷数的函数
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

//递归，展开一片区域的函数
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

// 计算非雷和非标记的位置个数
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

//排雷的函数
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	 //1.输入排查的坐标
     //2.检查该坐标处是不是雷
	 //(1) 是雷   - 很遗憾，你被炸死了 - 游戏结束
	 //(2) 不是雷 - 统计坐标周围有几个雷 - 存储排查雷的信息到show数组，游戏继续
	int x = 0;
	int y = 0;
	int win = 0;
	int select = 0;

	while (win < row * col - EASY_COUNT)
	{
		printf("请选择：1.排查雷 2.标记雷 3.取消标记\t");
		scanf("%d", &select);
		if (select == 1) 
		{
			printf("请输入要排查雷的坐标：>");
			scanf("%d %d", &x, &y);
			//判断坐标合法性
			if (x >= 1 && x <= row && y >= 1 && y <= col) 
			{
				if (show[x][y] == '*')
				{
					if (mine[x][y] == '1')
					{
						printf("\n\n很遗憾，你被炸死了！\n");
						printf("雷的分布情况，其中（'1'表示雷）：\n");
						DisplayBoard(mine, ROW, COL);
						break;
					}
					else
					{
						OpenArea(mine, show,ROW,COL, x, y);
						//显示排查出的信息
						DisplayBoard(show, ROW, COL);
						//计算已经排出的非雷位置的个数
						win = get_win(show, ROW, COL);
					}
				}
				else
				{
					printf("该位置已被排查过，请重新输入！\n");
				}
			}
			else
			{
				printf("坐标不合法，请重新输入！\n");
			}
		}
		else if (select == 2)
		{
			printf("请输入要标记的坐标：>");
			scanf("%d %d", &x, &y);
			//判断坐标合法性
			if (x >= 1 && x <= row && y >= 1 && y <= col) 
			{
				if (show[x][y] == '*')
				{
					show[x][y] = '!';
					DisplayBoard(show, ROW, COL);
				}
				else if(show[x][y]=='!')
				{
					printf("该位置已被标记，请重新选择！\n");
				}
				else
				{
					printf("该位置不能标记，请重新选择！\n");
				}
			}
			else 
			{
				printf("坐标不合法，请重新输入！\n");
			}
		}
		else if (select == 3)
		{
			printf("请输入要取消标记的坐标：>");
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
					printf("该位置不能取消标记，请重新选择！\n");
				}
			}
			else
			{
				printf("坐标不合法，请重新输入！\n");
			}
		}
		else 
		{
			printf("输入有误，请重新输入！\n");
		}
		
		//printf("win=%d\n", win);
	}
	if (win == row * col - EASY_COUNT) 
	{
		printf("\n恭喜你，排雷成功！\n");
		printf("雷的分布情况，其中（'1'表示雷）：\n");
		DisplayBoard(mine, ROW, COL);
	}
}

//基础功能+拓展功能
//1.标记功能（用'!'）
//2.展开一片区域的功能（使用递归）      
//*当排查下x，y坐标时：（1）该坐标不是雷  （2）该坐标周围没有雷  （3）该坐标没有被排查过
