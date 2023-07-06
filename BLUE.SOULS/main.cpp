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
IMAGE alice1;
IMAGE alice2;

IMAGE stn_grs1;
IMAGE stn_grs2;

IMAGE statue1;
IMAGE statue2;

IMAGE fl;

IMAGE tree1;
IMAGE tree2;

IMAGE wolf1;
IMAGE wolf2;
IMAGE wolfbar1;
IMAGE wolfbar2;

IMAGE alicebar1;
IMAGE alicebar2;
IMAGE dia;


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
	loadimage(&alice1, _T("alicecharacter1.bmp"));
	loadimage(&alice2, _T("alicecharacter2.bmp"));
	loadimage(&stn_grs1, _T("stone_grass1.bmp"));
	loadimage(&stn_grs2, _T("stone_grass2.bmp"));
	loadimage(&statue1, _T("statue1.bmp"));
	loadimage(&statue2, _T("statue2.bmp"));
	loadimage(&fl, _T("fl.bmp"));
	loadimage(&tree1, _T("tree1.bmp"));
	loadimage(&tree2, _T("tree2.bmp"));
	loadimage(&alicebar1, _T("alicebar1.bmp"));
	loadimage(&alicebar2, _T("alicebar2.bmp"));
	loadimage(&dia, _T("dia.png"));
	loadimage(&wolf1, _T("wolf1.bmp"));
	loadimage(&wolf2, _T("wolf2.bmp"));
	loadimage(&wolfbar1, _T("wolfbar1.bmp"));
	loadimage(&wolfbar2, _T("wolfbar2.bmp"));
}


extern int mainChrx;
extern int mainChry;
extern int NumOnto;


// 下面的函数实现welcome界面,具备按空格键进入下一个页面的功能
void Game_Interface_1_Welcome(void)
{

	setbkcolor(RGB(165, 134, 202));

	putimage(0, 0, &bkimage_Welcome);

	RGBS titlergb1 = { 0, 0, 0 };
	RECT titlebox1 = { 0, 0, WIDTH * 1.5, 120 };
	// https://docs.easyx.cn/zh-cn/logfont  <----(Start Game struct LOGFONT)
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
		//"GetAsyncKeyState(VK_SPACE)" : Start Game key value -> https://blog.csdn.net/mystonelxj/article/details/88184829
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

	LOGFONT titlefont2 = { 27, 0, 0, 0, 100, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SCRIPT, "Script" };
	RGBS titlergb2 = { 0, 0, 0 };
	RECT titlebox1 = { 850, 100, 1200, 150 };
	RECT titlebox2 = { 850, 210, 1200, 260 };
	RECT titlebox3 = { 850, 320, 1200, 370 };
	RECT titlebox4 = { 850, 430, 1200, 480 };

	// 绘制四个按钮

	solidroundrect(850, 210, 1200, 260, 20, 20);
	floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);
	beginprint_center("Start Game", &titlefont2, &titlebox2, &titlergb2);

	solidroundrect(850, 320, 1200, 370, 20, 20);
	floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);
	beginprint_center("Quit Game", &titlefont2, &titlebox3, &titlergb2);

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
			 if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 210 && mmsg.y < 260)
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);


				solidroundrect(870, 217, 1180, 253, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);
				beginprint_center("Start Game", &titlefont2, &titlebox2, &titlergb2);

				solidroundrect(850, 320, 1200, 370, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);
				beginprint_center("Quit Game", &titlefont2, &titlebox3, &titlergb2);

				ret = 1;
				EndBatchDraw();
				break;
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 320 && mmsg.y < 370)
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);


				solidroundrect(850, 210, 1200, 260, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);
				beginprint_center("Start Game", &titlefont2, &titlebox2, &titlergb2);

				solidroundrect(870, 327, 1180, 363, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);
				beginprint_center("Quit Game", &titlefont2, &titlebox3, &titlergb2);

				ret = 0;
				EndBatchDraw();
				break;
			}
		}
		if (mmsg.uMsg == WM_MOUSEMOVE)
		{
			if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 210 && mmsg.y < 260)
			{
				setlinecolor(WHITE);
				roundrect(840, 200, 1210, 270, 20, 20);
			}
			else if (mmsg.x > 850 && mmsg.x < 1200 && mmsg.y > 320 && mmsg.y < 370)
			{
				setlinecolor(WHITE);
				roundrect(840, 310, 1210, 380, 20, 20);
			}	
			else
			{
				cleardevice();
				putimage(0, 0, &bkimage_Manu);


				solidroundrect(850, 210, 1200, 260, 20, 20);
				floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);
				beginprint_center("Start Game", &titlefont2, &titlebox2, &titlergb2);

				solidroundrect(850, 320, 1200, 370, 20, 20);
				floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);
				beginprint_center("Quit Game", &titlefont2, &titlebox3, &titlergb2);

			}
		}

		EndBatchDraw();
	}

	Sleep(400); // 延时0.4秒,但小于这个值会出现闪屏现象
	cleardevice();
	BeginBatchDraw();
	putimage(0, 0, &bkimage_Manu);


	solidroundrect(850, 210, 1200, 260, 20, 20);
	floodfill(1000, 250, RGB(255, 255, 255), FLOODFILLBORDER);
	beginprint_center("Start Game", &titlefont2, &titlebox2, &titlergb2);

	solidroundrect(850, 320, 1200, 370, 20, 20);
	floodfill(1000, 330, RGB(255, 255, 255), FLOODFILLBORDER);
	beginprint_center("Quit Game", &titlefont2, &titlebox3, &titlergb2);

	EndBatchDraw();
	Sleep(400);
	Img2dark(bkimage_Manu, 100, 1);
	return ret;
}

// 下面的函数实现填入方格,输入坐标（在源图像中的以及要填入的目标位置）
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
				}
				else {
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
	if (1) {

		putBitimage(14, 12, 19, 8, &boat1, &boat2);
		putBitimage(14, 11, 19, 7, &boat1, &boat2);


		putBitimage(2, 2, 17, 20, &boat1, &boat2);

		putBitimage(7, 0, 22, 20, &boat1, &boat2);
		putBitimage(7, 1, 22, 21, &boat1, &boat2);


		putBitimage(15, 11, 22, 9, &boat1, &boat2);
		putBitimage(15, 11, 21, 9, &boat1, &boat2);
		putBitimage(15, 11, 19, 9, &boat1, &boat2);
		putBitimage(15, 11, 18, 9, &boat1, &boat2);
		putBitimage(15, 11, 17, 9, &boat1, &boat2);

		putBitimage(15, 11, 21, 8, &boat1, &boat2);
		putBitimage(15, 11, 20, 8, &boat1, &boat2);
		putBitimage(15, 11, 19, 8, &boat1, &boat2);
		putBitimage(15, 11, 18, 8, &boat1, &boat2);


		putBitimage(15, 11, 21, 23, &boat1, &boat2);
		putBitimage(15, 11, 20, 23, &boat1, &boat2);
		putBitimage(15, 11, 19, 23, &boat1, &boat2);
		putBitimage(15, 11, 18, 23, &boat1, &boat2);

		putBitimage(15, 10, 20, 9, &boat1, &boat2);
		putBitimage(15, 9, 20, 8, &boat1, &boat2);

		putBitimage(6, 14, 17, 11, &boat1, &boat2);
		putBitimage(5, 14, 22, 11, &boat1, &boat2);

		//putBitimage(4, 8, 18, 11, &boat1, &boat2);
		//putBitimage(5, 8, 19, 11, &boat1, &boat2);
		//putBitimage(6, 8, 20, 11, &boat1, &boat2);
		//putBitimage(7, 8, 21, 11, &boat1, &boat2);


		putBitimage(4, 0, 19, 13, &boat1, &boat2);
		putBitimage(4, 1, 19, 14, &boat1, &boat2);
		putBitimage(5, 1, 20, 13, &boat1, &boat2);
		putBitimage(6, 1, 20, 14, &boat1, &boat2);

		putBitimage(1, 2, 17, 10, &alice1, &alice2);

	}
		
	return 0;
}


myBoxed boatBoxed_boat =
{
	525,298,715,708
};

myBoxed inyBoxed1_boat = {
   535,323,555,358
};

myBoxed inyBoxed2_boat = {
	685,328,710,353
};

myBoxed inyBoxed3_boat = {
   590,388,655,453
};

myBoxed inyBoxed4_boat = {
	525,483,560,518
};

myBoxed inyBoxed5_boat = {
	680,488,715,518
};

myBoxed inyBoxed6_boat = {
	680,628,715,663
};

myBoxed judgeBox_boat = {
	595,673,655,683
};

myBoxed alice_boat = {
	565,308,580,323
};



void Draw_grs(int i, int j) {
	fallUni(7, 3, i, j, &fl);
}

typedef pair<int, int> XOY;

//用于生成第五个场地
int Game_Iterface_5_Grass(void) {

	setbkcolor(BLACK);
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 25; j++) {
			fallUni(9, 1, i, j, &stn_grs1);
		}
	}

	XOY Stngrs_sc[UNIWIDTH * UNIHEIGHT];
	Stngrs_sc[0] = make_pair(20, 12);
	Stngrs_sc[1] = make_pair(20, 13);
	Stngrs_sc[2] = make_pair(19, 12);
	Stngrs_sc[3] = make_pair(19, 13);


	putBitimage(1, 2, 17, 13, &alice1, &alice2);
	//装饰
	Stngrs_sc[4] = make_pair(12, 3);
	Stngrs_sc[5] = make_pair(8, 6);
	Stngrs_sc[6] = make_pair(3, 3);
	Stngrs_sc[7] = make_pair(25, 9);
	Stngrs_sc[8] = make_pair(3, 20);
	Stngrs_sc[9] = make_pair(27, 23);
	Stngrs_sc[10] = make_pair(29, 24);
	Stngrs_sc[11] = make_pair(35, 3);
	Stngrs_sc[12] = make_pair(36, 19);

	Stngrs_sc[13] = make_pair(12, 10);
	Stngrs_sc[14] = make_pair(23, 13);
	Stngrs_sc[15] = make_pair(12, 16);
	Stngrs_sc[16] = make_pair(11, 13);
	Stngrs_sc[17] = make_pair(21, 8);
	Stngrs_sc[18] = make_pair(28, 10);
	Stngrs_sc[19] = make_pair(11, 13);
	Stngrs_sc[20] = make_pair(22, 10);
	Stngrs_sc[21] = make_pair(27, 7);
	Stngrs_sc[22] = make_pair(20, 18);
	Stngrs_sc[23] = make_pair(24, 9);
	Stngrs_sc[24] = make_pair(14, 18);
	Stngrs_sc[25] = make_pair(28, 14);
	Stngrs_sc[26] = make_pair(21, 10);
	Stngrs_sc[27] = make_pair(18, 12);
	Stngrs_sc[28] = make_pair(17, 14);
	Stngrs_sc[29] = make_pair(27, 8);

	//井 etc
	Stngrs_sc[30] = make_pair(2, 19);
	Stngrs_sc[31] = make_pair(2, 20);
	Stngrs_sc[32] = make_pair(2, 21);
	Stngrs_sc[33] = make_pair(3, 19);
	Stngrs_sc[34] = make_pair(3, 20);
	Stngrs_sc[35] = make_pair(3, 21);
	Stngrs_sc[36] = make_pair(4, 19);
	Stngrs_sc[37] = make_pair(4, 20);
	Stngrs_sc[38] = make_pair(4, 21);

	Stngrs_sc[39] = make_pair(1, 18);
	Stngrs_sc[40] = make_pair(1, 19);
	Stngrs_sc[41] = make_pair(1, 20);
	Stngrs_sc[42] = make_pair(1, 21);
	Stngrs_sc[43] = make_pair(1, 22);
	Stngrs_sc[44] = make_pair(2, 22);
	Stngrs_sc[45] = make_pair(2, 18);
	Stngrs_sc[46] = make_pair(3, 22);
	Stngrs_sc[47] = make_pair(3, 18);
	Stngrs_sc[48] = make_pair(4, 22);
	Stngrs_sc[49] = make_pair(4, 18);
	Stngrs_sc[50] = make_pair(5, 22);
	Stngrs_sc[51] = make_pair(5, 21);
	Stngrs_sc[52] = make_pair(5, 20);
	Stngrs_sc[53] = make_pair(5, 19);
	Stngrs_sc[54] = make_pair(4, 17);
	Stngrs_sc[55] = make_pair(3, 23);
	Stngrs_sc[56] = make_pair(0, 19);
	Stngrs_sc[57] = make_pair(6, 15);
	Stngrs_sc[58] = make_pair(5, 18);
	Stngrs_sc[59] = make_pair(2, 16);

	//岩浆
	Stngrs_sc[60] = make_pair(38, 8);
	Stngrs_sc[61] = make_pair(39, 8);
	Stngrs_sc[62] = make_pair(39, 9);
	Stngrs_sc[63] = make_pair(37, 12);
	Stngrs_sc[64] = make_pair(37, 13);
	Stngrs_sc[65] = make_pair(38, 13);
	Stngrs_sc[66] = make_pair(39, 13);
	Stngrs_sc[67] = make_pair(39, 7);
	Stngrs_sc[68] = make_pair(39, 14);
	Stngrs_sc[69] = make_pair(38, 14);
	Stngrs_sc[70] = make_pair(36, 16);
	Stngrs_sc[71] = make_pair(36, 17);
	Stngrs_sc[72] = make_pair(37, 17);

	//花
	Stngrs_sc[73] = make_pair(16, 0);
	Stngrs_sc[74] = make_pair(17, 0);
	Stngrs_sc[75] = make_pair(18, 0);
	Stngrs_sc[76] = make_pair(19, 0);
	Stngrs_sc[77] = make_pair(20, 0);
	Stngrs_sc[78] = make_pair(21, 0);

	Stngrs_sc[78] = make_pair(16, 1);
	Stngrs_sc[79] = make_pair(17, 2);
	Stngrs_sc[80] = make_pair(18, 1);
	Stngrs_sc[81] = make_pair(19, 2);
	Stngrs_sc[82] = make_pair(20, 3);
	Stngrs_sc[83] = make_pair(21, 1);
	Stngrs_sc[84] = make_pair(15, 1);

	//路
	Stngrs_sc[85] = make_pair(19, 16);
	Stngrs_sc[86] = make_pair(19, 17);
	Stngrs_sc[87] = make_pair(19, 18);
	Stngrs_sc[88] = make_pair(19, 19);
	Stngrs_sc[89] = make_pair(19, 20);
	Stngrs_sc[90] = make_pair(19, 21);
	Stngrs_sc[91] = make_pair(19, 22);
	Stngrs_sc[92] = make_pair(19, 23);
	Stngrs_sc[93] = make_pair(19, 24);
	Stngrs_sc[94] = make_pair(20, 16);
	Stngrs_sc[95] = make_pair(20, 17);
	Stngrs_sc[96] = make_pair(20, 18);
	Stngrs_sc[97] = make_pair(20, 19);
	Stngrs_sc[98] = make_pair(20, 20);
	Stngrs_sc[99] = make_pair(20, 21);
	Stngrs_sc[100] = make_pair(20, 22);
	Stngrs_sc[101] = make_pair(20, 23);
	Stngrs_sc[102] = make_pair(20, 24);


	Stngrs_sc[103] = make_pair(20, 15);
	Stngrs_sc[104] = make_pair(20, 16);
	Stngrs_sc[105] = make_pair(21, 15);
	Stngrs_sc[106] = make_pair(21, 16);

	XOY Stat_rc[UNIWIDTH * UNIHEIGHT];
	Stat_rc[0] = make_pair(11, 5);
	Stat_rc[1] = make_pair(11, 6);
	Stat_rc[2] = make_pair(12, 5);
	Stat_rc[3] = make_pair(12, 6);


	XOY Stngrs_rc[UNIWIDTH * UNIHEIGHT];
	Stngrs_rc[0] = make_pair(12, 3);
	Stngrs_rc[1] = make_pair(8, 6);
	Stngrs_rc[2] = make_pair(2, 2);
	Stngrs_rc[3] = make_pair(12, 6);
	Stngrs_rc[4] = make_pair(11, 5);
	Stngrs_rc[5] = make_pair(11, 6);
	Stngrs_rc[6] = make_pair(12, 5);
	Stngrs_rc[7] = make_pair(12, 6);




	for (int i = 0; i < 4; i++) {
		putBitimage(Stat_rc[i].first, Stat_rc[i].second, Stngrs_sc[i].first, Stngrs_sc[i].second, &statue1, &statue2);
	}

	for (int i = 4; i < 13; i++) {
		putBitimage(14, 6, Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 13; i < 21; i++) {
		putBitimage(11, 10, Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 21; i < 30; i++) {
		putBitimage(14, 4, Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 30; i < 39; i++) {
		putBitimage((Stngrs_sc[i].first - 2), (Stngrs_sc[i].second - 16), Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 39; i < 60; i++) {
		putBitimage(6, 5, Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 60; i < 73; i++) {
		fallUni(9, 8, Stngrs_sc[i].first, Stngrs_sc[i].second, &fl);
	}

	for (int i = 73; i < 85; i++) {
		putBitimage(14, 6, Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 85; i < 103; i++) {
		putBitimage(14, 6, Stngrs_sc[i].first, Stngrs_sc[i].second, &stn_grs1, &stn_grs2);
	}

	for (int i = 103; i < 107; i++) {
		putBitimage((Stngrs_sc[i].first - 14), (Stngrs_sc[i].second - 13), Stngrs_sc[i].first - 1, Stngrs_sc[i].second - 1, &stn_grs1, &stn_grs2);
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < (10 - i) && (j * i) % 5 != 2; j++) {
			Draw_grs(i, j);
		}
	}


	return 0;
}

myBoxed fall_grass = {
	0,0,WIDTH,HEIGHT
};

myBoxed statue_grass = {
	580,358,660,483
};

myBoxed hole_grass = {
	65,598,125,658
};

myBoxed alice_grass = {
	515,403,570,433
};


//用于生成第六个场地
int Game_Iterface_6_Grave(void) {
	setbkcolor(BLACK);
	for (int i = 15; i < 25; i++) {
		for (int j = 7; j < 18; j++) {
			if (i * j % 4 == 1) fallUni(6, 5, i, j, &stn_grs1);
			else if(i * j % 4 == 2) fallUni(4,6, i, j, &stn_grs1);
			else if (i * j % 4 == 3) fallUni(4, 7, i, j, &stn_grs1);
			else if (i * j % 4 == 0) fallUni(4, 8, i, j, &stn_grs1);
			
		}
	}

	putBitimage(13, 10, 16, 12, &statue1, &statue2);
	putBitimage(14, 10, 17, 12, &statue1, &statue2);
	putBitimage(13, 11, 16, 13, &statue1, &statue2);
	putBitimage(14, 11, 17, 13, &statue1, &statue2);
	putBitimage(15, 11, 18, 13, &statue1, &statue2);
	putBitimage(15, 10, 18, 12, &statue1, &statue2);

	putBitimage(2, 2, 18, 13, &wolf1, &wolf2);
	putBitimage(3, 2, 19, 13, &wolf1, &wolf2);

	putBitimage(5, 2, 15, 7,&stn_grs1, &stn_grs2);
	putBitimage(5, 3, 15, 8, &stn_grs1, &stn_grs2);
	putBitimage(5, 2, 15, 16, &stn_grs1, &stn_grs2);
	putBitimage(5, 3, 15, 17, &stn_grs1, &stn_grs2);
	putBitimage(5, 2, 24, 7, &stn_grs1, &stn_grs2);
	putBitimage(5, 3, 24, 8, &stn_grs1, &stn_grs2);
	putBitimage(5, 2, 24, 16, &stn_grs1, &stn_grs2);
	putBitimage(5, 3,24 , 17, &stn_grs1, &stn_grs2);


	return 0;
}

myBoxed doorandwolf = {
	500,353,590,423
};

myBoxed wolf_grave = {
	595, 373,630,433
};


int main()
{
	Initimage();
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	initgraph(WIDTH, HEIGHT);
	cleardevice();


//	//欢迎界面
//	Game_Interface_1_Welcome();
//	int Game_Interface_2_Manu_get = Game_Interface_2_Manu();
//	if (Game_Interface_2_Manu_get == 0) {
//		closegraph();
//		return 0;
//	}
//
//	else if (Game_Interface_2_Manu_get == 1) {
//		goto beginGame;
//	}
//
//	beginGame:
//	setbkcolor(BLACK);
//	cleardevice();
//
//
//	//船界面以及对话
//	Draw(Game_Interface_4_Boat);
//	while (1)
//	{
//		if (judgeBox(mainChrx, mainChry, &judgeBox_boat, NULL)) { 
//			mainChrx = 625;
//			mainChry = 768;
//			NumOnto = 0;
//			setbkcolor(BLACK);
//			cleardevice();
//			Sleep(1000);
//			break;
//		}
//		if (judgeBox(mainChrx, mainChry, &alice_boat, NULL)&& _kbhit() && _getch()=='e') {
//			goto alicecommunication;
//		}
//alicecommunicationed:
//		mainChrKeyDown(Game_Interface_4_Boat,judgeBox, &boatBoxed_boat, &inyBoxed1_boat, &inyBoxed2_boat, &inyBoxed3_boat, &inyBoxed4_boat, &inyBoxed5_boat, &inyBoxed6_boat, NULL);
//	}

wolfcommunicationed:


	Draw(Game_Iterface_5_Grass);
	while (1)
	{

		if (judgeBox(mainChrx, mainChry, &hole_grass, NULL)) {
			setbkcolor(BLACK);
			cleardevice();
			Sleep(1000);
			mainChrx = 630;
			mainChry = 198;
			NumOnto = 0;
			break;
		}

		if (judgeBox(mainChrx, mainChry, &alice_grass, NULL) && _kbhit() && _getch() == 'e') {
			goto alicecommunication2;
		}

alicecommunicationed2:
		mainChrKeyDown(Game_Iterface_5_Grass, judgeBox, &fall_grass, &statue_grass, NULL);

	}


	extern myBoxed firel[100];
	extern int maze[13][13];

	Draw(Game_Iterface_6_Grave);

	while (1) {

		if (judgeBox(mainChrx, mainChry, &wolf_grave, NULL) && _kbhit() && _getch() == 'e') {
			goto wolfcommunication;
		}


		mainChrKeyDown(Game_Iterface_6_Grave, judgeBox, &fall_grass, &doorandwolf, NULL);
	}
	_getch();
	closegraph();
	return 0;


alicecommunication:
	cleardevice();

	NumOnto = 1;
	Draw(Game_Interface_4_Boat);
	diabox(dia, alicebar1, alicebar2, "Hello");
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		diabox(dia, alicebar1, alicebar2, "Good afternoon");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}	
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		diabox(dia, alicebar1, alicebar2, "Good afternoon");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}

	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Interface_4_Boat);
		//goto alicecommunicationed;
	}

alicecommunication2:
	cleardevice();

	NumOnto = 1;
	Draw(Game_Iterface_5_Grass);
	diabox(dia, alicebar1, alicebar2, "Hello");
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		diabox(dia, alicebar1, alicebar2, "Good afternoon");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		diabox(dia, alicebar1, alicebar2, "Good afternoon");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		diabox(dia, alicebar1, alicebar2, "Good moning");
	}

	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_5_Grass);
		goto alicecommunicationed2;
	}

wolfcommunication:
	cleardevice();

	NumOnto = 1;
	Draw(Game_Iterface_6_Grave);
	diabox(dia, wolfbar1, wolfbar2, "Hello");
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		diabox(dia, wolfbar1, wolfbar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		diabox(dia, wolfbar1, wolfbar2, "Good afternoon");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		diabox(dia, wolfbar1, wolfbar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		diabox(dia, wolfbar1, wolfbar2, "Good moning");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		diabox(dia, wolfbar1, wolfbar2, "Good afternoon");
	}
	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		diabox(dia, wolfbar1, wolfbar2, "Good moning");
	}

	if (_getch() == 'e' || _getch() == 'E') {
		cleardevice();
		Draw(Game_Iterface_6_Grave);
		mainChrx = 140;
		mainChry = 583;
		NumOnto = 3;
		cleardevice();
		Sleep(1000);
		goto wolfcommunicationed;
	}

}