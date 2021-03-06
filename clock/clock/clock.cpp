// clock.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<math.h>

#define PI 3.1415926
#define High 500
#define Width 500

IMAGE img_bg;

int main()
{
	initgraph(Width, High);
	loadimage(&img_bg, _T("images\\bg.jpg"));

	int center_x, center_y;
	center_x = Width / 2;
	center_y = High / 2;

	int secondLength;
	secondLength = Width / 5*2;

	int minuteLength;
	minuteLength = Width / 3;

	int hourLength;
	hourLength = Width / 4;

	double secondAngle = 0;
	double minuteAngle = 0;	
	double hourAngle = 0;

	SYSTEMTIME ti;

	BeginBatchDraw();

	while (1)
	{
		putimage(0, 0, &img_bg);
		GetLocalTime(&ti);

		secondAngle = ti.wSecond * 2 * PI / 60; 
		minuteAngle = (ti.wMinute+ti.wSecond/60.0) * 2 * PI / 60;
		hourAngle = (ti.wHour+ti.wMinute / 60.0) * 2 * PI / 12;

		int secondEnd_x = center_x +int(secondLength * sin(secondAngle));
		int secondEnd_y = center_y - int(secondLength * cos(secondAngle));

		int minuteEnd_x = center_x + int(minuteLength * sin(minuteAngle));
		int minuteEnd_y = center_y - int(minuteLength * cos(minuteAngle));

		int hourEnd_x = center_x + int(hourLength * sin(hourAngle));
		int hourEnd_y = center_y - int(hourLength * cos(hourAngle));

		//绘制表针
		setlinestyle(PS_SOLID, 3);
		setcolor(RED);
		line(center_x, center_y, secondEnd_x, secondEnd_y);

		setlinestyle(PS_SOLID, 6);
		setcolor(BLACK);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);

		setlinestyle(PS_SOLID, 9);
		setcolor(BLACK);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
	}
	_getch();

    return 0;
}