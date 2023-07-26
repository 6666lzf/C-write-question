#define _CRT_SECURE_NO_WARNINGS 1
//test.c测试游戏的逻辑
//game.c游戏代码实现
//game.h游戏代码声明(函数声明等)

#include"game.h"
void menu()
{
	printf("\t\t\t\t\t\n");
	printf("************************\n");
	printf("*********1.play*********\n");
	printf("*********0.exit*********\n");
	printf("************************\n");
}

void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 }; 
	//初始化棋盘的函数
	InitBoard(board,ROW,COL);
	//打印棋盘
	DisplayBoard(board, ROW, COL);
	//下棋
	while (1)
	{
		//玩家下棋的函数
		PlayerMove(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DisplayBoard(board, ROW, COL);
		//电脑下棋的函数
		ComputerMove(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL); 
		if (ret != 'C')
		{
			break;
		}
		DisplayBoard(board, ROW, COL);
	}
	if (ret == '*')
	{
		printf("\n玩家赢!!!!\n");
	}
	else if (ret == '#')
	{
		printf("\n电脑赢!!!!\n");
	}
	else
	{
		printf("\n平局!!!!\n");
	}
	DisplayBoard(board, ROW, COL);
}


int main()
{
	srand((unsigned int)time(NULL));//设置随机数的生成起点
	int input=0;
	do 
	{
		menu();//打印菜单
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误!\n");
			break;
		}
	} while (input);
	return 0;
}