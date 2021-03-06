// bouncing_ball.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<Windows.h>

#define high 480
#define width 320

int restart;
int position_x, position_y;
int radius;
int dir_x, dir_y;
int board_l, board_r,board_h;
int enemy_x, enemy_y;
int bang;
int score;
TCHAR s[5];

void startup()
{
	initgraph(width, high);
	radius = 10;
	position_x = rand() % 100+radius;
	position_y = rand() % 100+radius;
	enemy_x = width / 2;
	enemy_y = width / 2;
	score = 0;
	dir_x = 1;
	dir_y = 1;
	restart = 0;
	bang = 0;
	board_h = high -50;
	board_l = width / 3;
	board_r = width / 3*2;
}

void show()
{
	BeginBatchDraw();
	setlinestyle(PS_SOLID, 3);
	setcolor(RED);
	line(board_l, board_h, board_r, board_h);
	line(board_l, board_h+3, board_r, board_h+3);
	setfillcolor(YELLOW);
	solidcircle(position_x, position_y,radius);
	setfillcolor(GREEN);
	solidcircle(enemy_x, enemy_y, 2*radius);
	setcolor(WHITE);
	outtextxy(10, high - 30, L"Score:");
	_stprintf_s(s, _T("%d"), score);
	outtextxy(60, high -30, s);
	if (position_y > high)
	{
		outtextxy(120, high - 30, L"Game over !");
		restart = 1;
	}
	FlushBatchDraw();
	Sleep(5);
	cleardevice();
}
void updateWithoutInput()
{
	position_x = position_x + dir_x;
	position_y = position_y + dir_y;
	if (position_x == width - radius)
		dir_x = -dir_x;
	if (position_x ==  radius)
		dir_x = -dir_x;
	if ((position_y == board_h - radius)&&(position_x >= board_l)&&(position_x<=board_r))
		dir_y = -dir_y;
	if (position_y == radius)
		dir_y = -dir_y;
	if ( ( abs(position_x-enemy_x))* (abs(position_x - enemy_x))+(abs(position_y - enemy_y ))*(abs(position_y - enemy_y ))<  radius*radius*9 )
	{
		score++;
		bang=1;
		enemy_x = rand() % (width-4*radius);
		enemy_y = rand() % (high-60-4*radius);
	}

	if (board_l <= 0)
	{
		board_l = 0;
		board_r = width / 3;
	}
	if (board_r >= width)
	{
		board_r =width;
		board_l = width / 3 * 2;
	}

	if (board_h <= 40)
		board_h=40;
	if (board_h >= high-40)
		board_h=high-40;
}
void updateWithInput()
{
	int input;
	if (_kbhit())
	{
		input = _getch();
		if (board_l >= 0 && board_r <= width  && board_h>=40 && board_h <= high - 40)
		{
			if (input == 75)
			{
				board_l = board_l - 7;
				board_r = board_r - 7;
			}
			if (input == 77)
			{
				board_l = board_l + 7;
				board_r = board_r + 7;
			}

			if (input == 72)
				board_h = board_h - 10;
			if (input == 80)
				board_h = board_h + 10;
		}
	}
}

int main()
{
	do
	{	
		startup();
		while (!restart)
			{	
				show();
				updateWithoutInput();
				updateWithInput();
			}
		Sleep(2000);
		system("pause");
	} while (restart);
    return 0;
}