#define _CRT_SECURE_NO_WARNINGS
#include "FadeInandOut.h"
#include "CommunicationBar.h"


// 全局变量——IMAGE以及MUSIC
// 以及使像素画图片 -> https://imgonline.tools/zh/pixelate
IMAGE bkimage_Welcome;
IMAGE bkimage_Manu;

IMAGE bkA1;
IMAGE maincharacter1;
IMAGE maincharacter2;

IMAGE home_wall;
IMAGE boat;


// 人物移动的全局变量
int NumIndex = 0;
int NumOnto = 2; // 0-下；1-左；2-右；3-上
int mainChrx = WIDTH / 2, mainChry = HEIGHT / 2;

// 初始化加载图片
void Initimage(void)
{
	loadimage(&bkA1, _T("bkA1.png"));
	loadimage(&bkimage_Manu, _T("resP_sx2_Manu.png"), WIDTH, HEIGHT, true);
	loadimage(&bkimage_Welcome, _T("resP_sx1_Welcome.png"), WIDTH, HEIGHT, true);
	loadimage(&maincharacter1, _T("maincharacter1.bmp"));
	loadimage(&maincharacter2, _T("maincharacter2.bmp"));
	loadimage(&home_wall, _T("home_wall.png"));
	loadimage(&boat, _T("boat1.png"));
}



// 下面的函数实现welcome界面，具备按空格键进入下一个页面的功能
void Game_Interface_1_Welcome(void)
{

	setbkcolor(RGB(165, 134, 202));

	putimage(0, 0, &bkimage_Welcome);

	RGBS titlergb1 = { 0, 0, 0 };
	RECT titlebox1 = { 0, 0, WIDTH * 1.5, 120 };
	// https://docs.easyx.cn/zh-cn/logfont  <----(about struct LOGFONT)
	LOGFONT titlefont1 = { 80, 0, 0, 0, 500, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, "Times New Roman" };

	beginprint_center("BLUE. SOULS", &titlefont1, &titlebox1, &titlergb1);

	RGBS titlergb2 = { 255, 255, 255 };
	RECT titlebox2 = { 990, 680, WIDTH, HEIGHT };
	LOGFONT titlefont2 = { 27, 0, 0, 0, 100, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SCRIPT, "Script" };
	/*
	beginprint_center("Press SPACE to continue......", &titlefont2, &titlebox2, &titlergb2);
	*/

	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE))
			break;
		//"GetAsyncKeyState(VK_SPACE)" : about key value -> https://blog.csdn.net/mystonelxj/article/details/88184829
		lunixy_fade_in("Press SPACE to continue......", &titlefont2, 0, 0, &titlergb2, 100, 15);
		if (GetAsyncKeyState(VK_SPACE))
			break;
		lunixy_fade_out("Press SPACE to continue......", &titlefont2, 0, 0, &titlergb2, 100, 15);
		if (GetAsyncKeyState(VK_SPACE))
			break;
		Sleep(1000);
		if (GetAsyncKeyState(VK_SPACE))
			break;
	}
	Img2dark(bkimage_Welcome, 100, 1);
}

// 下面的函数实现Manu界面, 返回值决定下一步的操作
int Game_Interface_2_Manu(void)
{

	setbkcolor(RGB(255, 255, 255));

	cleardevice();
	// dark2Img(bkimage_Manu, 50, 1);
	putimage(0, 0, &bkimage_Manu);

	// 绘制四个按钮
	solidroundrect(850, 100, 1200, 150, 20, 20);
	floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

	solidroundrect(850, 210, 1200, 260, 20, 20);
	floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

	solidroundrect(850, 320, 1200, 370, 20, 20);
	floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

	solidroundrect(850, 430, 1200, 480, 20, 20);
	floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);

	MOUSEMSG mmsg;
	Sleep(1000);
	int ret = 0;

	// 对于鼠标选中按钮的判定
	while (1)
	{
		BeginBatchDraw();
		mmsg = GetMouseMsg(); // 获得鼠标信息

		if (mmsg.uMsg == WM_LBUTTONDOWN)
		{
			if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 100 && mmsg.y < 150)
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);
				solidroundrect(870, 107, 1180, 143, 20, 20);
				floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 210, 1200, 260, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 320, 1200, 370, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 430, 1200, 480, 20, 20);
				floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);
				ret = 1;
				EndBatchDraw();
				break;
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 210 && mmsg.y < 260)
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);
				solidroundrect(850, 100, 1200, 150, 20, 20);
				floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(870, 217, 1180, 253, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 320, 1200, 370, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 430, 1200, 480, 20, 20);
				floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);
				ret = 2;
				EndBatchDraw();
				break;
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 320 && mmsg.y < 370)
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);
				solidroundrect(850, 100, 1200, 150, 20, 20);
				floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 210, 1200, 260, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(870, 327, 1180, 363, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 430, 1200, 480, 20, 20);
				floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);
				ret = 3;
				EndBatchDraw();
				break;
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 430 && mmsg.y < 480)
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);
				solidroundrect(850, 100, 1200, 150, 20, 20);
				floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 210, 1200, 260, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 320, 1200, 370, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(870, 437, 1190, 473, 20, 20);
				floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);
				ret = 4;
				EndBatchDraw();
				break;
			}
		}
		if (mmsg.uMsg == WM_MOUSEMOVE)
		{
			if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 100 && mmsg.y < 150)
			{
				setlinecolor(WHITE);
				roundrect(840, 90, 1210, 160, 20, 20);
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 210 && mmsg.y < 260)
			{
				setlinecolor(WHITE);
				roundrect(840, 200, 1210, 270, 20, 20);
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 320 && mmsg.y < 370)
			{
				setlinecolor(WHITE);
				roundrect(840, 310, 1210, 380, 20, 20);
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 430 && mmsg.y < 480)
			{
				setlinecolor(WHITE);
				roundrect(840, 420, 1210, 490, 20, 20);
			}
			else
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);
				solidroundrect(850, 100, 1200, 150, 20, 20);
				floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 210, 1200, 260, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 320, 1200, 370, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

				solidroundrect(850, 430, 1200, 480, 20, 20);
				floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);
			}
		}

		EndBatchDraw();
	}

	Sleep(400); // 延时0.4秒,但小于这个值会出现闪屏现象
	cleardevice();
	BeginBatchDraw();
	putimage(0, 0, &bkimage_Manu);
	solidroundrect(850, 100, 1200, 150, 20, 20);
	floodfill(1000, 100, RGB(255, 255, 255), FLOODFILLBORDER);

	solidroundrect(850, 210, 1200, 260, 20, 20);
	floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);

	solidroundrect(850, 320, 1200, 370, 20, 20);
	floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);

	solidroundrect(850, 430, 1200, 480, 20, 20);
	floodfill(1000, 440, RGB(255, 255, 255), FLOODFILLBORDER);
	EndBatchDraw();
	Sleep(400);
	Img2dark(bkimage_Manu, 100, 1);
	return ret;
}

// 下面的函数实现填入方格，输入坐标（在源图像中的以及要填入的目标位置）
void fallUni(int IndexInImgx, int IndexInImgy, int IndexInFallx, int IndexInFally, IMAGE* pimg)
{

	putimage(IndexInFallx * gridSize, IndexInFally * gridSize, 32, 32, pimg, IndexInImgx * 32, 32 * IndexInImgy);
}

// 下面的函数实现三元光栅操作码抠图填入
void putBitimage(int IndexInImgx, int IndexInImgy, int IndexInFallx, int IndexInFally, IMAGE* psrc, IMAGE* pmarking)
{

	putimage(IndexInFallx * gridSize, IndexInFally * gridSize, 32, 32, pmarking, IndexInImgx * 32, 32 * IndexInImgy, SRCAND); // 掩码图或操作把人物放入
	putimage(IndexInFallx * gridSize, IndexInFally * gridSize, 32, 32, psrc, IndexInImgx * 32, 32 * IndexInImgy, SRCPAINT);	  // 掩码图以消除边框
}

// 下面的函数实现绘制home界面
int Game_Interface_3_Fire(void)
{
	setbkcolor(BLACK);
	for (int i = 10; i < 30; i++)
	{
		for (int j = 3; j < 23; j++)
		{

			if (i == 10 && (j > 3 && j < 22))
			{
				fallUni(5, 10, i, j, &home_wall);
			}
			else if (i == 29 && (j > 3 && j < 22))
			{
				fallUni(7, 10, i, j, &home_wall);
			}
			else if (j == 3 && (i > 10 && i < 29))
			{
				fallUni(6, 9, i, j, &home_wall);
			}
			else if (j == 22 && (i > 10 && i < 29))
			{
				fallUni(6, 11, i, j, &home_wall);
			}
			else if (j == 22 && i == 29)
			{
				fallUni(7, 11, i, j, &home_wall);
			}
			else if (j == 22 && i == 10)
			{
				fallUni(5, 11, i, j, &home_wall);
			}
			else if (i == 10 && j == 3)
			{
				fallUni(5, 9, i, j, &home_wall);
			}
			else if (i == 29 && j == 3)
			{
				fallUni(7, 9, i, j, &home_wall);
			}
			else
			{

				if ((i * j) % 7 == 0 && i % j == 1)
				{
					fallUni(7, 5, i, j, &home_wall);
				}
				else
					fallUni(7, 4, i, j, &home_wall);
			}
		}
	}
	return 0;
}

//下面的函数实现绘制boat界面
int Game_Interface_4_Boat(void)
{
	// putimage(0, 0, &bkimage_Welcome);
	setbkcolor(BLACK);
	for (int i = 16; i < 24; i++)
	{
		for (int j = 6; j < UNIHEIGHT; j++)
		{
			// 船头

			if (j == 6 && i < 20)
			{
				fallUni(i - 14, 15, i + 2, j, &boat);
			}
			else if (j == 7 && i < 23)
			{
				fallUni(i - 7, 0, i + 1, j, &boat);
			}
			else if (j == 8)
			{
				fallUni(i - 8, 1, i, j, &boat);
			}
			else if (j == 9)
			{
				fallUni(i - 8, 2, i, j, &boat);
			}

			// 甲板
			else if (j > 9 && j < 18)
			{
				if (i == 16)
				{
					fallUni(8, 3, i, j, &boat);
				}
				else if (i == 23)
				{
					fallUni(15, 3, i, j, &boat);
				}
				else
				{
					if ((i * j) % 3 == 0 && i % j == 3)
					{
						fallUni(2, 1, i, j, &boat);
					}
					else if ((i * j) % 3 == 0 && i % j == 1)
					{
						fallUni(2, 0, i, j, &boat);
					}
					else if ((i * j) % 3 == 2 && i % j == 5)
					{
						fallUni(1, 0, i, j, &boat);
					}
					else
						fallUni(0, 0, i, j, &boat);
				}
			}
			else if (j == 18)
			{
				fallUni(9, 4, i, j, &boat);
			}
		}
	}
	return 0;
}

// 此函数用于角色移动函数中mainChrKeyDown
void Draw(int(* Game_Interface)(void))
{
	Game_Interface();

	putimage(mainChrx, mainChry, 32, 32, &maincharacter2, NumIndex * 32, 32 * NumOnto, SRCAND);	  // 掩码图或操作把人物放入
	putimage(mainChrx, mainChry, 32, 32, &maincharacter1, NumIndex * 32, 32 * NumOnto, SRCPAINT); // 掩码图以消除边框
}

// 此函数用于控制主角的移动
void mainChrKeyDown(int(*Game_Interface)(void))
{
	int c;
	if (_kbhit())
	{
		BeginBatchDraw();
		cleardevice();
		c = _getch();
		switch (c)
		{
		case 'a':
		case 'A':
		case 75:
			NumOnto = 1;
			mainChrx -= 5;
			break;
		case 'd':
		case 'D':
		case 77:
			NumOnto = 2;
			mainChrx += 5;
			break;
		case 'w':
		case 'W':
		case 72:
			NumOnto = 3;
			mainChry -= 5;
			break;
		case 's':
		case 'S':
		case 80:
			NumOnto = 0;
			mainChry += 5;
			break;
		}
		Draw(Game_Interface);
		NumIndex = (NumIndex + 1) % 3; // 按循环次数在0-3之间循，以选择贴图
		EndBatchDraw();
	}
}

int main()
{
	Initimage();
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	initgraph(WIDTH, HEIGHT);
	cleardevice();

	// Game_Interface_1_Welcome();
	// Game_Interface_2_Manu();

	// 以下是测试代码
	cleardevice();

	Draw(Game_Interface_4_Boat);
	while (1)
	{
		mainChrKeyDown(Game_Interface_4_Boat);
	}

	while (1)
	{
		//	BeginBatchDraw();
		//	IMAGE dia;
		//	IMAGE alice;
		//	loadimage(&dia, _T("dia.png"), 1280, 300, true);
		//	loadimage(&alice, _T("alice.png"), 120, 120, true);
		//	diabox(dia, alice);
		//	EndBatchDraw();
	}

	_getch();
	closegraph();
	return 0;
}