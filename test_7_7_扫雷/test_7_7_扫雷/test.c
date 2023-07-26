#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()
{
	printf("\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("*********************\n");
	printf("*****  1. play  *****\n");
	printf("*****  0. exit  *****\n");
	printf("*********************\n");
}

void game()
{
	char mine[ROWS][COLS] = { 0 };//存放布置好的雷的信息
	char show[ROWS][COLS] = { 0 };//存放排查出的雷的信息
	//初始化数组的内容为指定内容
	//mine数组在没有布置雷的时候，都是‘0’
	InitBoard(mine, ROWS, COLS,'0');
	//show数组在没有排查雷的时候都是‘*’
	InitBoard(show, ROWS, COLS, '*'); 


	//设置雷
	Setmine(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//DisplayBoard(mine, ROW, COL);
	//排查雷
	FindMine(mine, show, ROW, COL);

}


int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:system("cls"); game();
			break;
		case 0:printf("退出游戏\n");
			break;
		default:printf("选择错误，请重新输入！\n");
			break;
		}
	} while (input);
	return 0;
}