// flappy_bird.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <graphics.h>
#include <conio.h>

// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define Width 504
#define High  896
#define PI  3.1415926

IMAGE img_bgd, img_bgn, img_land, img_bd000, img_bd00, img_bd010, img_bd01, img_bd020, img_bd02, img_black,
img_piped, img_piped0, img_pipeu0, img_pipeu, img_bar_down1, img_bar_down2, img_s1, img_s2, img_s10, img_s20,
img_title0, img_title, img_tblack, img_bdt000, img_bdt00, img_bdt010, img_bdt01, img_bdt020, img_bdt02;

int title_x, title_y;
int bird_x,bird_y;
int wing;
int wing_t;
int land_x, land_y;
int pipe_x, pipe_y;
int pipe_x1, pipe_y1;
int again;
double a;
double t;
int score;
int s1, s2;
bool bang;
bool restart;
int score_x1, score_x2, score_y;
int gogogo;
char input;
double  tangle;

void startup()
{
	initgraph(Width,High);
	loadimage(&img_bgd, _T("images\\bg_day.jpg"));
	//loadimage(&img_bgn, _T("images\\bg_night.jpg"));
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
	//mciSendString("open  sounds\\sfx_hit.mp3 alias hitmusic", NULL, 0, NULL);		// 打开碰撞音乐
	//mciSendString("open  sounds\\sfx_wing.mp3 alias wingmusic", NULL, 0, NULL);		 // 打开跳动音乐
	//mciSendString("open  sounds\\sfx_die.mp3 alias diemusic", NULL, 0, NULL);

	title_x = Width / 6;
	title_y = High / 3;
	bird_x =Width/4;
	bird_y =60;
	wing = 0;
	wing_t = 0;
	again = 0;
	land_x = 0;
	land_y = 700;
	pipe_x = 756;		//Width*1.5;         
	pipe_y = rand() %100 -50-296;
	pipe_x1 = pipe_x +298;	// pipe_x+0.5(Width+91);
	pipe_y1 = rand() % 100-50 - 296;
	a =0.0015;
	t = 0;
	bang = false;
	score = 0;
	restart = false;
	score_x1 = 252 - 21;
	score_x2 = score_x1-42;
	score_y = 140;
	gogogo = 0;
	BeginBatchDraw();
	tangle = 0;
}

void show()
{
	putimage(0, 0, &img_bgd);					// 显示背景	
	putimage(title_x, title_y, &img_title0, NOTSRCERASE); 
	putimage(title_x, title_y, &img_title, SRCINVERT);

	putimage(pipe_x, pipe_y, &img_piped0, NOTSRCERASE);					// 显示上一半的障碍物
	putimage(pipe_x, pipe_y, &img_piped, SRCINVERT);
	putimage(pipe_x, pipe_y+732, &img_pipeu0, NOTSRCERASE);					// 显示下一半的障碍物，空隙172
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
	switch (wing)
	{
	case 0:
	{
		putimage(bird_x, bird_y, &img_tblack, NOTSRCERASE);
		putimage(bird_x, bird_y, &img_bdt00, SRCINVERT);
		putimage(bird_x, bird_y, &img_bdt000,NOTSRCERASE);					// 显示小鸟0
		putimage(bird_x, bird_y, &img_bdt00, SRCINVERT);	

		break;
	}
	case 1:
	{
		putimage(bird_x, bird_y, &img_tblack, NOTSRCERASE);
		putimage(bird_x, bird_y, &img_bdt01, SRCINVERT);
		putimage(bird_x, bird_y, &img_bdt010, NOTSRCERASE);				// 显示小鸟1	
		putimage(bird_x, bird_y, &img_bdt01, SRCINVERT);	
		break;
	}
	case 2:
		putimage(bird_x, bird_y, &img_tblack, NOTSRCERASE);
		putimage(bird_x, bird_y, &img_bdt02, SRCINVERT);
		putimage(bird_x, bird_y, &img_bdt020, NOTSRCERASE);				 // 显示小鸟2	
		putimage(bird_x, bird_y, &img_bdt02, SRCINVERT);
		break;
	}
	FlushBatchDraw();
}

void updateWithoutInput()
{
	if (bang)
	{
		if (tangle >(-PI / 2))
		{
			tangle = tangle - 0.04;
		}
	}

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
		if (tangle >( -PI / 3))
		{
			tangle = tangle - 0.01;
		}

		if (land_x > -41)					 //大地运动
		{
			land_x = land_x - 1;
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
		case 0:  loadimage(&img_s1, _T("images\\font_048.JPG")); loadimage(&img_s10, _T("images\\font_0480.JPG"));  break;
		case 1:  loadimage(&img_s1, _T("images\\font_049.JPG")); 	loadimage(&img_s10, _T("images\\font_0490.JPG")); break;
		case 2:  loadimage(&img_s1, _T("images\\font_050.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 3:  loadimage(&img_s1, _T("images\\font_051.JPG"));   	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 4:  loadimage(&img_s1, _T("images\\font_052.JPG"));  	loadimage(&img_s10, _T("images\\font_0520.JPG")); break;
		case 5:  loadimage(&img_s1, _T("images\\font_053.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 6:  loadimage(&img_s1, _T("images\\font_054.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 7:  loadimage(&img_s1, _T("images\\font_055.JPG"));  	loadimage(&img_s10, _T("images\\font_0550.JPG")); break;
		case 8:  loadimage(&img_s1, _T("images\\font_056.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		case 9:  loadimage(&img_s1, _T("images\\font_057.JPG")); 	loadimage(&img_s10, _T("images\\font_0480.JPG")); break;
		}

		switch (s2)
		{
		case 0:  loadimage(&img_s2, _T("images\\font_048.JPG"));  loadimage(&img_s20, _T("images\\font_0480.JPG"));  break;
		case 1:  loadimage(&img_s2, _T("images\\font_049.JPG")); 	loadimage(&img_s20, _T("images\\font_0490.JPG")); break;
		case 2:  loadimage(&img_s2, _T("images\\font_050.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 3:  loadimage(&img_s2, _T("images\\font_051.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 4:  loadimage(&img_s2, _T("images\\font_052.JPG"));	loadimage(&img_s20, _T("images\\font_0520.JPG"));  break;
		case 5:  loadimage(&img_s2, _T("images\\font_053.JPG"));  	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 6:  loadimage(&img_s2, _T("images\\font_054.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 7:  loadimage(&img_s2, _T("images\\font_055.JPG"));  	loadimage(&img_s20, _T("images\\font_0550.JPG")); break;
		case 8:  loadimage(&img_s2, _T("images\\font_056.JPG")); 	loadimage(&img_s20, _T("images\\font_0480.JPG")); break;
		case 9:  loadimage(&img_s2, _T("images\\font_057.JPG"));	loadimage(&img_s20, _T("images\\font_0480.JPG"));  break;
		}
	}
	if (score > 9)
	{
		score_x1 = 252;
		score_x2 = 252-42;
	}

	if (wing_t <26)
		wing_t++;
	else
		wing_t = 0;

	wing=wing_t / 9;

	if (t < 200)				//update time
		  t++;
	else
		  t = 0;
	rotateimage(&img_bdt000, &img_bd000, tangle);
	rotateimage(&img_bdt00, &img_bd00, tangle);
	rotateimage(&img_bdt010, &img_bd010, tangle);
	rotateimage(&img_bdt01, &img_bd01, tangle);
	rotateimage(&img_bdt020, &img_bd020, tangle);
	rotateimage(&img_bdt02, &img_bd02, tangle);
	rotateimage(&img_tblack, &img_black, tangle);

	//判定GAMEOVER，间隙172

	if  (	(bird_x == pipe_x - 63 && (bird_y < pipe_y + 520-64 || bird_y > pipe_y + 560+172+40-22)) 
		|| (bird_y >= 635) 
		||(bird_x == pipe_x - 68 && 
			((bird_y < pipe_y + 560 + 172 + 40 - 22 && bird_y > pipe_y + 560 + 172-64) ||(bird_y < pipe_y +560-22 && bird_y > pipe_y + 520 - 64)))
		|| (bird_x > pipe_x - 68 && bird_x < pipe_x + 79 && (bird_y < pipe_y + 560 - 22 || bird_y > pipe_y + 560 + 172 - 64))	)
	{
		bang = true;
		wing = 1;
		mciSendString("open  sounds\\sfx_hit.mp3 alias hitmusic", NULL, 0, NULL);		// 打开碰撞音乐
		mciSendString("play hitmusic", NULL, 0, NULL);			// 仅播放一次
		mciSendString("open  sounds\\sfx_die.mp3 alias diemusic", NULL, 0, NULL);
		mciSendString("play diemusic", NULL, 0, NULL);

	}
	if ((bird_x == pipe_x - 63 && (bird_y < pipe_y1 + 520 - 64 || bird_y > pipe_y1 + 560 + 172 + 40 - 22))
		|| (bird_y >= 635)
		|| (bird_x == pipe_x1 - 68 &&
		((bird_y < pipe_y1 + 560 + 172 + 40 - 22 && bird_y > pipe_y1 + 560 + 172 - 64) || (bird_y < pipe_y1 + 560 - 22 && bird_y > pipe_y1 + 520 - 64)))
		|| (bird_x > pipe_x1 - 68 && bird_x < pipe_x1 + 79 && (bird_y < pipe_y1 + 560 - 22 || bird_y > pipe_y1 + 560 + 172 - 64)))
	{
		bang = true;
		wing = 1;
		mciSendString("open  sounds\\sfx_hit.mp3 alias hitmusic", NULL, 0, NULL);			// 打开碰撞音乐
		mciSendString("play hitmusic", NULL, 0, NULL);			// 仅播放一次
		mciSendString("open  sounds\\sfx_die.mp3 alias diemusic", NULL, 0, NULL);
		mciSendString("play diemusic", NULL, 0, NULL);
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
				tangle = PI / 4;
				mciSendString("close wingmusic", NULL, 0, NULL);		 // 先把前面一次的音乐关闭
				mciSendString("open  sounds\\sfx_wing.mp3 alias wingmusic", NULL, 0, NULL);		 // 打开跳动音乐
				mciSendString("play wingmusic", NULL, 0, NULL);			// 仅播放一次
			}
		}
	}
	else
	{
		if (_kbhit())			// 判断是否有输入
		{
			input = _getch();
			if (input == ' ' && bird_y==635)
			restart = true;
		}
	}
}

int main()
{
	do
	{
		startup();					// 数据初始化
		while (!restart)			//  游戏循环执行
		{
			show();
			updateWithoutInput();  // 与用户输入无关的更新
			updateWithInput();		  // 与用户输入有关的更新
		}
	} while (restart);
	return 0;
}