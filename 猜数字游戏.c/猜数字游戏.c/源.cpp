#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
int u; //ȫ�ֱ���
int same(int num[]);//��������
void menu()//��������
{
	printf("\t\t\t\t��������Ϸ\n\n\n\n");
	printf("\t\t\t\t1.��ʼ��Ϸ\n\n");
	printf("\t\t\t\t2.����\n\n");
	printf("\t\t\t\t3.�˳�\n\n");
	printf("\t\t\t�����루1-3����");
}
//������
int main()
{
	void help();//��������
	void game(int a[]);//��������

	int  k = 0, select=0;
	int a[4] = { 0 };
	srand((unsigned)time(NULL));//������֣�ֻ����һ�μ���
	menu();
	scanf("%d", &select);
	while (select!= 3)
	{
		switch (select)
		{
		case 1: {system("cls"); game(a); break; }
		case 2: {system("cls"); help(); _getch(); system("cls"); menu(); break; }
		default:printf("���벻�Ϸ�������������!"); break;
		}
		scanf("%d", &select);
	}
	return 0;
}

void help()//��Ϸ����˵������
{
	printf("\t\t\t��ӭʹ�ñ�����\n\n\n");
	printf("��Ϸ˵����������λ���֣����������ʾXAYB��X��ʾ�м����������������ͬ��λ����ͬ��\n");
	printf("Y��ʾ�м�λ�������������ͬ��λ�ò���ȷ��\n");
	printf("�����������............\n");
}

void game(int a[])//�Ƚ��û��������ݺ����������������ʾ��Ϣ
{
	int b[4] = {0};
	int i = 0, j = 0;
	while (1)
	{
		//����4�������
		do
		{
			for (i = 0; i < 4; i++)
				a[i] = rand() % 10;
			same(a);
		} while (u);//�˴��õ�ȫ�ֱ���u
		if (a[0] != 0)
			break;
	}
	int k = 1, A = 0, B = 0, N = 8 ,pick = 0;
	printf("������Ҫ�������λ��\n");
	while (A != 4 && k <= N)
	{
		A = 0, B = 0;
		printf("��%d�Σ�", k);
		scanf("%d", &pick);//��ҴӼ�����������
		while (pick < 999 || pick>10000)
		{
			printf("���벻�Ϸ���\n");
			scanf("%d", &pick);
		}
		for (i = 3; i >= 0; i--)
		{
			b[i] = pick % 10;
			pick = pick/ 10;
		}
		//�Ƚ϶�Ӧλ���ϵ���
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (a[i] == b[j])
					if (i == j)
						A++;
					else
						B++;
		printf("%dA%dB\n", A, B);
		if (A == 4)
		{
			printf("��ϲ����Ϸ�ɹ���\n");
		}
		k++;
	}
	if (A != 4 && k > 8)
	{
		printf("��Ϸʧ�ܣ�\n");
		printf("��ȷ���ǣ�");
		for (i = 0; i < 4; i++)
			printf("%d", a[i]);
		printf("\n");
	}
	printf("���� 1 ������Ϸ������ 2 ���ز˵������� 0 �˳���Ϸ��");
	while (1)
	{
		scanf("%d", &pick);
		if (pick == 2)
		{
			system("cls"); menu();
			int select=0;
			while (select != 3)
			{
				switch (select)
				{
				case 1: {system("cls"); game(a); break; }
				case 2: {system("cls"); help(); _getch(); system("cls"); menu(); break; }
				default:printf("���벻�Ϸ�������������!"); break;
				}
				scanf("%d", &select);
			}
			exit(0);
		}
		else if (pick == 1)
		{
			system("cls");
			game(a);
		}
		else if (pick == 0)
			exit(0);
		else
			printf("����������������룡\n");
	}
}

int same(int num[])//�жϲ��������������λ������û���ظ��ĺ���
{
	u = 0;//ע��u��ȫ�ֱ���
	for (int i = 0; i < 3; i++)
		for (int j = i + 1; j < 4; j++)
			if (num[i] == num[j])
				u = 1;
	return u;
}