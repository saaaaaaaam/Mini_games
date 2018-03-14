// flappy_bird.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <graphics.h>
#include <conio.h>

// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define Width 504
#define High  896

IMAGE img_bgd, img_bgn, img_land, img_bd000, img_bd00, img_bd010, img_bd01, img_bd020, img_bd02, img_black,
img_piped, img_piped0, img_pipeu0, img_pipeu, img_bar_down1, img_bar_down2, img_s1, img_s2, img_s10, img_s20,
img_title0, img_title;

int title_x, title_y;
int bird_x,bird_y;
int ring;
int ring_t;
int land_x, land_y;
int pipe_x, pipe_y;
int pipe_x1, pipe_y1;
int again;
double a;
double t;
int score;
int s1, s2;
int bang;
int restart;
int score_x1, score_x2, score_y;
int gogogo;
char input;

void startup()
{
	initgraph(Width,High);
	loadimage(&img_bgd, _T("images\\bg_day.jpg"));
	loadimage(&img_bgn, _T("images\\bg_night.jpg"));
	//loadimage(&img_title, _T("images\\title.JPG"));
	//loadimage(&img_title0, _T("images\\title0.JPG"));
	loadimage(&img_land, _T("images\\bg_land.jpg"));
	loadimage(&img_black, _T("images\\black0.jpg"));
	loadimage(&img_bd000, _T("images\\bird0_00.JPG"));
	loadimage(&img_bd00, _T("images\\bird0_0.JPG"));
	loadimage(&img_bd010, _T("images\\bird0_10.JPG"));
	loadimage(&img_bd01, _T("images\\bird0_1.JPG"));
	loadimage(&img_bd020, _T("images\\bird0_20.JPG"));
	loadimage(&img_bd02, _T("images\\bird0_2.JPG"));
	loadimage(&img_land, _T("images\\land.JPG"));
	loadimage(&img_piped, _T("images\\pipe_down.JPG"));
	loadimage(&img_piped0, _T("images\\pipe_down0.JPG"));
	loadimage(&img_pipeu, _T("images\\pipe_up.JPG"));
	loadimage(&img_pipeu0, _T("images\\pipe_up0.JPG"));
	loadimage(&img_s1, _T("images\\font_048.JPG"));
	loadimage(&img_s2, _T("images\\font_048.JPG"));
	loadimage(&img_s10, _T("images\\font_0480.JPG"));
	loadimage(&img_s20, _T("images\\font_0480.JPG"));

	title_x = Width / 6;
	title_y = High / 3;
	bird_x =Width/4;
	bird_y =60;
	ring = 0;
	ring_t = 0;
	again = 0;
	land_x = 0;
	land_y = 700;
	pipe_x = 756;		//Width*1.5;         
	pipe_y = rand() %100 -50-296;
	pipe_x1 = pipe_x +298;	// pipe_x+0.5(Width+91);
	pipe_y1 = rand() % 100-50 - 296;
	a =0.001;
	t = 0;
	bang = 0;
	score = 0;
	restart = 0;
	score_x1 = 252 - 21;
	score_x2 = score_x1-42;
	score_y = 140;
	gogogo = 0;
	BeginBatchDraw();

	//mciSendString("open D:\\background.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
	//mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
}

void show()
{
	putimage(0, 0, &img_bgd);					// 显示背景	
	putimage(title_x, title_y, &img_title0, NOTSRCERASE); 
	putimage(title_x, title_y, &img_title, SRCINVERT);

	putimage(pipe_x, pipe_y, &img_piped0, NOTSRCERASE);					// 显示上一半的障碍物
	putimage(pipe_x, pipe_y, &img_piped, SRCINVERT);
	putimage(pipe_x, pipe_y+732, &img_pipeu0, NOTSRCERASE);					// 显示下一半的障碍物
	putimage(pipe_x, pipe_y+ 732, &img_pipeu, SRCINVERT);

	putimage(pipe_x1, pipe_y1, &img_piped0, NOTSRCERASE);					// 显示上一半的障碍物
	putimage(pipe_x1, pipe_y1, &img_piped, SRCINVERT);
	putimage(pipe_x1, pipe_y1 + 732, &img_pipeu0, NOTSRCERASE);				 // 显示下一半的障碍物
	putimage(pipe_x1, pipe_y1 + 732, &img_pipeu, SRCINVERT);
	
	putimage(land_x,land_y, &img_land);							//显示大地

	putimage(score_x1, score_y, &img_s10, NOTSRCERASE);					// 显示分数个位,SRCINVERT
	putimage(score_x1, score_y, &img_s1, SRCINVERT);
	if (s2 > 0)
	{
		putimage(score_x2, score_y, &img_s20, NOTSRCERASE);					// 显示分数个位,SRCINVERT
		putimage(score_x2, score_y, &img_s2, SRCINVERT);
	}
	switch (ring)
	{
	case 0:
	{
		putimage(bird_x, bird_y, &img_bd000,NOTSRCERASE);					// 显示小鸟0
		putimage(bird_x, bird_y, &img_bd00, SRCINVERT);	

		break;
	}
	case 1:
	{
		putimage(bird_x, bird_y, &img_black, NOTSRCERASE);
		putimage(bird_x, bird_y, &img_bd01, SRCINVERT);
		putimage(bird_x, bird_y, &img_bd010, NOTSRCERASE);				// 显示小鸟1	
		putimage(bird_x, bird_y, &img_bd01, SRCINVERT);	
		break;
	}
	case 2:
		putimage(bird_x, bird_y, &img_black, NOTSRCERASE);
		putimage(bird_x, bird_y, &img_bd02, SRCINVERT);
		putimage(bird_x, bird_y, &img_bd020, NOTSRCERASE);				 // 显示小鸟2	
		putimage(bird_x, bird_y, &img_bd02, SRCINVERT);
		break;
	}
	FlushBatchDraw();
}

void updateWithoutInput()
{
	if (gogogo&&again)
	{
		t = 0;
		bird_y = bird_y - 16;
		again--;
	}

	if (bird_y<635)							//模拟自由落体  
		bird_y = int(bird_y + 0.5*a*t*t);
	if (bird_y > 635)
		bird_y = 635;

	if (!bang)						//游戏过程中
	{
		if (land_x >-41)					 //大地运动
		{
			land_x = land_x -1; 
		}
		else
			land_x = 0;

		if (pipe_x > -92)					//1号水管运动
			pipe_x = pipe_x -1;
		else
		{
			pipe_x = Width;
			pipe_y = rand() % 250 - 125-296;
		}
		if (pipe_x1 > -92)                       //2号水管运动
			pipe_x1 = pipe_x1 - 1;
		else
		{
			pipe_x1 = Width;						// rand() % 160+ pipe_x +252;
			pipe_y1 = rand() % 250 - 125 - 296;
		}

		if (bird_x == pipe_x + 5 || bird_x == pipe_x1 +5)				//判定得分
		{
			score++;
		}
		s1 = score % 10;
		s2 = score / 10;

		switch (s1)			  //设置分数参数
		{
		case 1:  loadimage(&img_s1, _T("images\\font_049.JPG")); 	loadimage(&img_s10, _T("images\\font_0490.JPG")); break;
		case 2:  loadimage(&img_s1, _T("images\\font_050.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 3:  loadimage(&img_s1, _T("images\\font_051.JPG"));   	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 4:  loadimage(&img_s1, _T("images\\font_052.JPG"));  	loadimage(&img_s10, _T("images\\font_0520.JPG")); break;
		case 5:  loadimage(&img_s1, _T("images\\font_053.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 6:  loadimage(&img_s1, _T("images\\font_054.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 7:  loadimage(&img_s1, _T("images\\font_055.JPG"));  	loadimage(&img_s10, _T("images\\font_0550.JPG")); break;
		case 8:  loadimage(&img_s1, _T("images\\font_056.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 9:  loadimage(&img_s1, _T("images\\font_057.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		default:
		case 0:  loadimage(&img_s1, _T("images\\font_048.JPG")); loadimage(&img_s10, _T("images\\font_0480.JPG"));  break;
		}

		switch (s2)
		{
		case 1:  loadimage(&img_s2, _T("images\\font_049.JPG")); 	loadimage(&img_s20, _T("images\\font_0490.JPG")); break;
		case 2:  loadimage(&img_s2, _T("images\\font_050.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 3:  loadimage(&img_s2, _T("images\\font_051.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 4:  loadimage(&img_s2, _T("images\\font_052.JPG"));	loadimage(&img_s20, _T("images\\font_0520.JPG"));  break;
		case 5:  loadimage(&img_s2, _T("images\\font_053.JPG"));  	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 6:  loadimage(&img_s2, _T("images\\font_054.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 7:  loadimage(&img_s2, _T("images\\font_055.JPG"));  	loadimage(&img_s20, _T("images\\font_0550.JPG")); break;
		case 8:  loadimage(&img_s2, _T("images\\font_056.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 9:  loadimage(&img_s2, _T("images\\font_057.JPG"));	loadimage(&img_s20, _T("images\\font_0480.JPG"));  break;
		default:
		case 0:  loadimage(&img_s2, _T("images\\font_048.JPG"));  loadimage(&img_s20, _T("images\\font_0480.JPG"));  break;
		}
	}
	if (score > 9)
	{
		score_x1 = 252;
		score_x2 = 252-42;
	}

	if (ring_t <26)
		ring_t++;
	else
		ring_t = 0;

	ring=ring_t / 9;

	if (t < 200)				//update time
		  t++;
	else
		  t = 0;

	//判定GAMEOVER
	if ((bird_x == pipe_x -63 && (bird_y < pipe_y + 480 ||bird_y > pipe_y +860)) || bird_y >=635 ||
		((bird_x==pipe_x-68) && ((bird_y < pipe_y + 530 && bird_y > pipe_y + 480) ||
		(bird_y < pipe_y + 876 && bird_y > pipe_y + 800)))
		|| ((bird_x > pipe_x-68 && bird_x < pipe_x +79) && (bird_y < pipe_y + 530 || bird_y > pipe_y + 800)))

	{
		bang = 1;
		ring = 1;
	}
	if ((bird_x == pipe_x1 - 63&& (bird_y < pipe_y1 + 480 || (bird_y > pipe_y1 + 860))) || bird_y >= 635 ||
		((bird_x == pipe_x1 - 68) && ((bird_y < pipe_y1 + 530&& bird_y > pipe_y1 + 480) ||
		(bird_y < pipe_y1 + 876&& bird_y > pipe_y1 + 800)))
		|| (bird_x > pipe_x1- 68 && bird_x < pipe_x1 + 79 && (bird_y < pipe_y1 + 530|| bird_y > pipe_y1 + 800)))

	{
		bang = 1;
		ring = 1;
	}
}

void updateWithInput()
{
	if (!bang)
	{
		 if (_kbhit())					// 判断是否有输入
		{
			input = _getch();
			if (input == ' '  && bird_y>100 && again==0)
			{
				gogogo = 1;
				again = 6;
				//bird_y = bird_y -60;
				//again = 1;
			}
			//mciSendString("close jpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			//mciSendString("open D:\\Jump.mp3 alias jpmusic", NULL, 0, NULL); // 打开跳动音乐
			//mciSendString("play jpmusic", NULL, 0, NULL); // 仅播放一次
		}
	}
	else
	{
		if (_kbhit())			// 判断是否有输入
		{
			input = _getch();
			if (input == ' ' && bird_y==635)
			restart = 1;
		}
	}
}

void gameover()
{
	//EndBatchDraw();
	//_getch();
	//closegraph();
}

int main()
{
	do
	{
		startup();					// 数据初始化
		while (!restart)			//  游戏循环执行
		{
			//show();
			updateWithoutInput();  // 与用户输入无关的更新
			updateWithInput();		  // 与用户输入有关的更新
			show();
		}
	} while (restart);
	//_getch();
	//gameover();		// 游戏结束、后续处理
	return 0;
}