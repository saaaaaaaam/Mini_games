// battle_plane.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
using namespace std;

int position_x, position_y;    //plain's position
int high, width;
int bullet_x, bullet_y;
int enemy_x, enemy_y;    //enemy's position
int score;
int miss;
char enemy ;
float bang, sum;
float hitrate;
int restart;

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()
{
	high = 18;
	width = 30;

	position_x = high-2;
	position_y = width / 2;

	bullet_x = -2;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = width / 2;

	score = 0;
	miss = 0;
	bang = 0;
	sum = 0;
	HideCursor();
	enemy = rand() % 26 + 65;
	restart = 0;
}
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos. X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void show()      
{
	gotoxy(0, 0);
	int i, j;
	//system("cls");
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width ;j++)
		{
			if ((i == position_x) && (j == position_y))
			{
				cout << "*";
			}
			/*
			if ((i == position_x + 1) && (j == position_y - 1))
			{
				cout << "*";
			}
			if ((i == position_x + 1) && (j == position_y ))
			{
				cout << "*";
			}
			*/	
			else if ((i == bullet_x) && (j == bullet_y))
				cout << "|";
			else if ((i == enemy_x) && (j == enemy_y))
			{
				cout << enemy;
			}	
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << "	     Score:" << score <<"		Miss enemy:"<<miss<< endl;
}
void show_end()
{
	if  (sum)
	hitrate = bang / sum;
	else
	{
		hitrate = 0;
	}
	cout << "	     Game over,and your score is " << score<<";";
	cout << "	Hit rate: " << hitrate * 100 << "%" << endl << endl;
	Sleep(3000);
	system("pause");
	system("cls");
}
void updateWithoutInput()
{
	if ((bullet_x == enemy_x ||bullet_x == enemy_x-1)&& bullet_y == enemy_y)
	{
		score++;
		bang++;
		enemy_x = 0;
		bullet_x = -1;
		enemy_y = rand() % width;
		enemy = rand() % 26 + 65;
	}
	if ((enemy_x == position_x) && (enemy_y == position_y))
	{
		restart = 1;
	}
	static int speed = 0;
	if (speed < 20)
		speed++;
	if (bullet_x > -1)
		bullet_x--;
	if (speed == 20)
	{
		if (enemy_x > high)
		{
			miss++;
			enemy_x = 0;
			enemy_y = rand() % width;
		}
		else
			enemy_x++;
		speed = 0;
	}
}

void updateWithInput()
{
	int input;
		if (_kbhit())
		{
			input = _getch();
			if (position_x > 0)
			{
				if (input == 72)
					position_x--;
			}
			if (position_y > 0)
			{
				if (input == 75)
					position_y--;
			}
			if (position_x <high-1)
			{
				if (input == 80)
					position_x++;
			}
			if (position_y <width-1)
			{
				if (input == 77)
					position_y++;
			}
			if (input ==32)
			{
				bullet_x = position_x - 1;
				bullet_y = position_y;
				sum++;
			}
		}
}

int main()
{
	while (1)
	{
		startup();
		while (!restart)
		{
			show();
			updateWithoutInput();
			updateWithInput();
		}
		show_end();
	}
    return 0;
}