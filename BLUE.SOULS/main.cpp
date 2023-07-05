#define _CRT_SECURE_NO_WARNINGS
#include "FadeInandOut.h"
#include "CommunicationBar.h"
#include "ControlMain.h"

// 全局变量——IMAGE以及MUSIC
// 以及使像素画图片 -> https://imgonline.tools/zh/pixelate
IMAGE bkimage_Welcome;
IMAGE bkimage_Manu;

IMAGE bkA1;
IMAGE maincharacter1;
IMAGE maincharacter2;

IMAGE home_wall;
IMAGE boat1;
IMAGE boat2;

// 初始化加载图片
void Initimage(void)
{
	loadimage(&bkA1, _T("bkA1.png"));
	loadimage(&bkimage_Manu, _T("resP_sx2_Manu.png"), WIDTH, HEIGHT, true);
	loadimage(&bkimage_Welcome, _T("resP_sx1_Welcome.png"), WIDTH, HEIGHT, true);
	loadimage(&maincharacter1, _T("maincharacter1.bmp"));
	loadimage(&maincharacter2, _T("maincharacter2.bmp"));
	loadimage(&home_wall, _T("home_wall.png"));
	loadimage(&boat1, _T("boat1.bmp"));
	loadimage(&boat2, _T("boat2.bmp"));
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

	//船身
	for (int i = 16; i < 24; i++)
	{
		for (int j = 6; j < UNIHEIGHT; j++)
		{
			// 船头
			if (j == 6 && i < 20)
			{
				fallUni(i - 14, 15, i + 2, j, &boat1);
			}
			else if (j == 7 && i < 23)
			{
				fallUni(i - 7, 0, i + 1, j, &boat1);
			}
			else if (j == 8)
			{
				fallUni(i - 8, 1, i, j, &boat1);
			}
			else if (j == 9)
			{
				fallUni(i - 8, 2, i, j, &boat1);
			}

			// 甲板
			else if ((j > 9 && j < 18)&&(j!=16))
			{
				if (i == 16)
				{
					fallUni(8, 3, i, j, &boat1);
				}
				else if (i == 23)
				{
					fallUni(15, 3, i, j, &boat1);
				}
				else
				{
					if ((i * j) % 3 == 0 && i % j == 3)
					{
						fallUni(2, 1, i, j, &boat1);
					}
					else if ((i * j) % 3 == 0 && i % j == 1)
					{
						fallUni(2, 0, i, j, &boat1);
					}
					else if ((i * j) % 3 == 2 && i % j == 5)
					{
						fallUni(0, 0, i, j, &boat1);
					}
					else
						fallUni(0, 0, i, j, &boat1);
				}
			}
			else if (j == 16) {
				if (i == 16)
				{
					fallUni(8, 6, i, j, &boat1);
				}
				else if (i == 23)
				{
					fallUni(15, 6, i, j, &boat1);
				}
				else if (i == 17)
				{
					fallUni(9, 6, i, j, &boat1);
				}
				else if (i == 22)
				{
					fallUni(14, 6, i, j, &boat1);
				}
				else {
					fallUni(0, 0, i, j, &boat1);
				}
			}
			//台阶
			else if (j == 18)
			{
				if (i == 16) {
					fallUni(8, 4, i, j, &boat1);
				}
				else if (i == 23) {
					fallUni(15, 4, i, j, &boat1);
				}
				else {
					fallUni(9, 4, i, j, &boat1);
				}
				
			}
			else if (j == 19) {
				if (i == 16) {
					fallUni(8, 5, i, j, &boat1);
				}
				else if (i == 23) {
					fallUni(15, 5, i, j, &boat1);
				}
				else {
					fallUni(0, 0, i, j, &boat1);
					putBitimage(9, 5, i, j, &boat1, &boat2);
				}

			}
			
			//后甲板
			else if (j == 20) {
				if (i == 16)
				{
					fallUni(8, 3, i, j, &boat1);
				}
				else if (i == 23)
				{
					fallUni(15, 3, i, j, &boat1);
				}
				else
				{
					if ((i * j) % 3 == 0 && i % j == 3)
					{
						fallUni(2, 0, i, j, &boat1);
					}
					else if ((i * j) % 3 == 0 && i % j == 1)
					{
						fallUni(0, 0, i, j, &boat1);
					}
					else if ((i * j) % 3 == 2 && i % j == 5)
					{
						fallUni(1, 1, i, j, &boat1);
					}
					else
						fallUni(0, 0, i, j, &boat1);
				}
			
			}

			//入口
			else if (j == 21) {
				if (i == 16) {
					fallUni(8, 5, i, j, &boat1);
				}
				else if (i == 23) {
					fallUni(15, 5, i, j, &boat1);
				}
				else if (i == 18) {
					fallUni(0, 0, i, j, &boat1);
					putBitimage(13, 14, i, j, &boat1, &boat2);
				}
				else if (i == 21) {
					fallUni(0, 0, i, j, &boat1);
					putBitimage(15, 14, i, j, &boat1, &boat2);
				}
				else if (i < 21 && i>18) {
					fallUni(14, 14, i, j, &boat1);
				}else{
					fallUni(0, 0, i, j, &boat1);
				}
			}
			else if (j == 22) {
				fallUni(0, 0, i, j, &boat1);
				if (i == 16) {
					fallUni(8, 5, i, j, &boat1);
				}
				else if (i == 23) {
					fallUni(15, 5, i, j, &boat1);
				}
				else if (i == 18) {
					fallUni(0, 0, i, j, &boat1);
					putBitimage(13, 15, i, j, &boat1, &boat2);
				}
				else if (i == 21) {
					fallUni(0, 0, i, j, &boat1);
					putBitimage(15, 15, i, j, &boat1, &boat2);
				}
				else if (i < 21 && i>18) {
					putBitimage(14, 15, i, j, &boat1, &boat2);
				}
				else {
					fallUni(0, 0, i, j, &boat1);
				}

			}

			//后甲板
			else if (j > 22 && j < UNIHEIGHT && j != 23) {
				if (i == 16)
				{
					fallUni(8, 3, i, j, &boat1);
				}
				else if (i == 23)
				{
					fallUni(15, 3, i, j, &boat1);
				}
				else
				{
					if ((i * j) % 3 == 0 && i % j == 3)
					{
						fallUni(2, 0, i, j, &boat1);
					}
					else if ((i * j) % 3 == 0 && i % j == 1)
					{
						fallUni(0, 0, i, j, &boat1);
					}
					else if ((i * j) % 3 == 2 && i % j == 5)
					{
						fallUni(0, 0, i, j, &boat1);
					}
					else {
						fallUni(0, 0, i, j, &boat1);
					}
						
				}

				}
			else if (j == 23) {
				if (i == 16)
				{
					fallUni(8, 6, i, j, &boat1);
				}
				else if (i == 23)
				{
					fallUni(15, 6, i, j, &boat1);
				}
				else if (i == 17)
				{
					fallUni(9, 6, i, j, &boat1);
				}
				else if (i == 22)
				{
					fallUni(14, 6, i, j, &boat1);
				}
				else {
					fallUni(0, 0, i, j, &boat1);
				}
			}

		}
	}

	//点缀
	putBitimage(15, 10, 20, 12, &boat1, &boat2);
	putBitimage(15, 9, 20, 11, &boat1, &boat2);

	putBitimage(14, 12, 19, 13, &boat1, &boat2);
	putBitimage(14, 11, 19, 12, &boat1, &boat2);



	for (int i = 16; i < 24; i++)
	{
		for (int j = 6; j < UNIHEIGHT; j++) 
		{
			if ((i == 17 || i == 22) && (j > 9 && j < 16))  {
				if (j % 4 == 0 && i ==17) putBitimage(6, 14, i, j, &boat1, &boat2);
				if (j % 4 == 3 && i ==22) putBitimage(5, 14, i, j, &boat1, &boat2);
			}
		}
	}

				

			

	return 0;
}

int main()
{
	Initimage();
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	initgraph(WIDTH, HEIGHT);
	cleardevice();

	 //Game_Interface_1_Welcome();
	 //Game_Interface_2_Manu();


	setbkcolor(BLACK);
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