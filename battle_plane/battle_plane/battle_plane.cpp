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

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()
{
	high = 18;
	width = 30;

	position_x = high / 2;
	position_y = width / 2;

	bullet_x = -1;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = width / 2;

	score = 0;
	HideCursor();
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
	//int k;
	//system("cls");
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width ;j++)
		{
			if ((i == position_x) && (j == position_y))
			{
				cout << "*";
			/*	 fail to get it's body
			for (k = 0; k < j-1; k++)
				{
					cout << " ";
				}
				cout << "* *"; 
			*/
			}
			else if ((i == bullet_x) && (j == bullet_y))
				cout << "|";
			else if ((i == enemy_x) && (j == enemy_y))
				cout << "o";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << "Score:" << score << endl;
}
void updateWithoutInput()
{
	if ((bullet_x == enemy_x) && (bullet_y == enemy_y))
	{
		score++;
		enemy_x = 0;
		bullet_x = -1;
		enemy_y = rand() % width;
	}
	if ((enemy_x == position_x) && (enemy_y == position_y))
	{
		cout << "Game over , and your score is " << score << endl;
		_getch();
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
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == 'w')
			position_x--;
		if (input == 'a')
			position_y--;
		if (input == 's')
			position_x++;
		if (input == 'd')
			position_y++;
		if (input == ' ')
		{
			bullet_x = position_x - 1;
			bullet_y = position_y;
		}
	}
}
int main()
{
	startup();       
	while(1)
	{
		show();     
		updateWithoutInput();
		updateWithInput();
	}
    return 0;
}