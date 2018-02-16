// clock.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<math.h>

#define PI 3.1415926
#define High 480
#define Width 640

int main()
{
	initgraph(Width, High);

	int center_x, center_y;
	center_x = Width / 2;
	center_y = High / 2;

	int secondLength;
	secondLength = Width / 5;

	int minuteLength;
	minuteLength = Width / 6;

	int hourLength;
	hourLength = Width / 8;

	int maxLength;
	maxLength = Width / 4.5;

	float secondAngle = 0;
	float minuteAngle = 0;	
	float hourAngle = 0;

	SYSTEMTIME ti;

	//BeginBatchDraw();

	while (1)
	{
		GetLocalTime(&ti);

		secondAngle = ti.wSecond * 2 * PI / 60; 
		minuteAngle = ti.wMinute * 2 * PI / 60;
		hourAngle = ti.wHour * 2 * PI / 12;

		int secondEnd_x = center_x + secondLength * sin(secondAngle);
		int secondEnd_y = center_y - secondLength * cos(secondAngle);

		int minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		int minuteEnd_y = center_y - minuteLength * cos(minuteAngle);

		int hourEnd_x = center_x + hourLength * sin(hourAngle);
		int hourEnd_y = center_y - hourLength * cos(hourAngle);

		//绘制表盘
		setlinestyle(PS_SOLID, 4);
		setcolor(YELLOW);
		circle(center_x, center_y, maxLength);

		//绘制表针
		setlinestyle(PS_SOLID, 3);
		setcolor(RED);
		line(center_x, center_y, secondEnd_x, secondEnd_y);

		setlinestyle(PS_SOLID, 3);
		setcolor(GREEN);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);

		setlinestyle(PS_SOLID, 4);
		setcolor(WHITE);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();

		Sleep(60);
		setcolor(BLACK);

		line(center_x, center_y, secondEnd_x, secondEnd_y);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		//EndBatchDraw();
	}
	_getch();
	closegraph;

    return 0;
}