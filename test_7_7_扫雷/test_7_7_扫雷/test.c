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
	char mine[ROWS][COLS] = { 0 };//��Ų��úõ��׵���Ϣ
	char show[ROWS][COLS] = { 0 };//����Ų�����׵���Ϣ
	//��ʼ�����������Ϊָ������
	//mine������û�в����׵�ʱ�򣬶��ǡ�0��
	InitBoard(mine, ROWS, COLS,'0');
	//show������û���Ų��׵�ʱ���ǡ�*��
	InitBoard(show, ROWS, COLS, '*'); 


	//������
	Setmine(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//DisplayBoard(mine, ROW, COL);
	//�Ų���
	FindMine(mine, show, ROW, COL);

}


int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:system("cls"); game();
			break;
		case 0:printf("�˳���Ϸ\n");
			break;
		default:printf("ѡ��������������룡\n");
			break;
		}
	} while (input);
	return 0;
}