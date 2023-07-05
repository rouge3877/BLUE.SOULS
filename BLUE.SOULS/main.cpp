#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <map>

#define WIDTH 1280
#define HEIGHT 800
#define FPS 24
#define GRIDSIZE 32
#define UNIWIDTH WIDTH / GRIDSIZE
#define UNIHEIGHT HEIGHT / GRIDSIZE
// 40*25
#pragma comment(lib, "winmm.lib")

using namespace std;

// 定义一个结构体变量，用来存储RGB的值
typedef struct
{
	int rgb1;
	int rgb2;
	int rgb3;

} RGBS;

// 格子的全局变量
const int gridSize = GRIDSIZE; // 每个格子的大小
const int cols = UNIWIDTH;	   // 格子地图的列数
const int rows = UNIHEIGHT;	   // 格子地图的行数

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

// 下面的函数实现居中打印;RGBS是一个结构体，用来存储RGB的值;RECT是一个结构体，用来存储矩形的左上角和右下角坐标;LOGFONT是一个结构体，用来存储字体的信息
void beginprint_center(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// 下面的函数实现左上角打印;RGBS是一个结构体，用来存储RGB的值;RECT是一个结构体，用来存储矩形的左上角和右下角坐标;LOGFONT是一个结构体，用来存储字体的信息
void beginprint_topleft(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_LEFT | DT_TOP | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// 下面的函数实现渐入的效果，其中LOGFONT是一个结构体，用来存储字体的信息，x和y是输出的位置（左上角），times是分割次数，sleeptime是间隔时间
void lunixy_fade_in(const char* string, const LOGFONT* zfont, int x, int y, const RGBS* rgbs, int times, int sleeptime)
{
	setbkmode(TRANSPARENT);
	settextstyle(zfont);
	COLORREF bk_color = getbkcolor();
	int bk_color_arr[3] = { GetRValue(bk_color), GetGValue(bk_color), GetBValue(bk_color) };
	int text_color_arr[3] = { rgbs->rgb1, rgbs->rgb2, rgbs->rgb3 };
	double r_incr = static_cast<double>(text_color_arr[0] - bk_color_arr[0]) / times;
	double g_incr = static_cast<double>(text_color_arr[1] - bk_color_arr[1]) / times;
	double b_incr = static_cast<double>(text_color_arr[2] - bk_color_arr[2]) / times;
	BeginBatchDraw();
	for (int i = 0; i <= times; i++)
	{
		settextcolor(RGB(static_cast<int>(bk_color_arr[0] + r_incr * i), static_cast<int>(bk_color_arr[1] + g_incr * i), static_cast<int>(bk_color_arr[2] + b_incr * i)));
		outtextxy(x, y, string);
		FlushBatchDraw();
		Sleep(sleeptime);
	}
	EndBatchDraw();
}

// 下面的函数实现渐出的效果，其中LOGFONT是一个结构体，用来存储字体的信息，x和y是输出的位置（左上角），times是分割次数，sleeptime是间隔时间
void lunixy_fade_out(const char* string, const LOGFONT* zfont, int x, int y, const RGBS* rgbs, int times, int sleeptime)
{
	setbkmode(TRANSPARENT);
	settextstyle(zfont);
	COLORREF bk_color = getbkcolor();
	int bk_color_arr[3] = { GetRValue(bk_color), GetGValue(bk_color), GetBValue(bk_color) };
	int text_color_arr[3] = { rgbs->rgb1, rgbs->rgb2, rgbs->rgb3 };
	double r_incr = static_cast<double>(text_color_arr[0] - bk_color_arr[0]) / times;
	double g_incr = static_cast<double>(text_color_arr[1] - bk_color_arr[1]) / times;
	double b_incr = static_cast<double>(text_color_arr[2] - bk_color_arr[2]) / times;
	BeginBatchDraw();
	for (int i = 0; i <= times; i++)
	{
		settextcolor(RGB(static_cast<int>(text_color_arr[0] - r_incr * i), static_cast<int>(text_color_arr[1] - g_incr * i), static_cast<int>(text_color_arr[2] - b_incr * i)));
		outtextxy(x, y, string);
		FlushBatchDraw();
		Sleep(sleeptime);
	}
	EndBatchDraw();
}

// 下面的函数旨在实现图片的渐暗效果，其中pImg是一个IMAGE类的对象，times是分割次数，sleeptime是间隔时间
void Img2dark(IMAGE Img, int times, int sleeptime)
{
	DWORD* pBuffer;
	pBuffer = GetImageBuffer(&Img);

	int width = Img.getwidth();
	int height = Img.getheight();

	BeginBatchDraw();
	for (int j = 0; j <= times; j++)
	{
		Sleep(sleeptime);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				int index = y * width + x;
				int r = GetRValue(pBuffer[index]);
				int g = GetGValue(pBuffer[index]);
				int b = GetBValue(pBuffer[index]);
				double r_incr = static_cast<double>(r) / times;
				double g_incr = static_cast<double>(g) / times;
				double b_incr = static_cast<double>(b) / times;
				if (pBuffer[index] != 0)
					pBuffer[index] = RGB(static_cast<int>(r - r_incr * j), static_cast<int>(g - g_incr * j), static_cast<int>(b - b_incr * j));
			}
		}
		putimage(0, 0, &Img);
		FlushBatchDraw();
	}
	EndBatchDraw();
}

//*下面的函数旨在实现图片的渐显效果，其中pImg是一个IMAGE类的对象，times是分割次数，sleeptime是间隔时间(尚未完成，在处理rgb时有问题, 速度很慢)
void dark2Img(IMAGE Img, int times, int sleeptime)
{

	DWORD* pBuffer;
	pBuffer = GetImageBuffer(&Img);

	map<int, RGBS> Index_rgb;

	int width = Img.getwidth();
	int height = Img.getheight();

	double r_incr, g_incr, b_incr;

	int x, y, index;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			index = y * width + x;

			Index_rgb[index].rgb1 = GetRValue(pBuffer[index]);
			Index_rgb[index].rgb2 = GetGValue(pBuffer[index]);
			Index_rgb[index].rgb3 = GetBValue(pBuffer[index]);
		}
	}

	BeginBatchDraw();
	for (int j = times; j >= 0; j--)
	{

		Sleep(sleeptime);
		for (y = 0; y < height; y++)
		{
			for (x = 0; x < width; x++)
			{
				index = y * width + x;

				r_incr = static_cast<double>(Index_rgb[index].rgb1) / times;
				g_incr = static_cast<double>(Index_rgb[index].rgb2) / times;
				b_incr = static_cast<double>(Index_rgb[index].rgb3) / times;
				pBuffer[index] = RGB(static_cast<int>(r_incr * (times - j)), static_cast<int>(g_incr * (times - j)), static_cast<int>(b_incr * (times - j)));
			}
		}
		putimage(0, 0, &Img);
		FlushBatchDraw();
	}
	EndBatchDraw();
}

// 绘图函数，补充透明度 AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer(); // GetImageBuffer() 函数，用于获取绘图设备的显存指针， EasyX 自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);	  // 获取 picture 的显存指针
	int imageWidth = image->getwidth();	  // 获取图片宽度
	int imageHeight = image->getheight(); // 获取图片宽度
	int dstX = 0;						  // 在 绘图区域 显存里像素的角标
	int srcX = 0;						  // 在 image 显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// 防止越界
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < WIDTH && iy + y >= 0 && iy + y < HEIGHT)
			{
				// 获取像素角标
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * WIDTH;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA; // 0xAArrggbb; AA 是透明度
				int sr = ((src[srcX] & 0xff0000) >> 16);		// 获取 RGB 里的 R
				int sg = ((src[srcX] & 0xff00) >> 8);			// G
				int sb = src[srcX] & 0xff;						// B

				// 设置对应的绘图区域像素信息
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  // 公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8) // αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);		  // αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

// 对话框
void diabox(IMAGE Imgs, IMAGE chas, char* string)
{
	IMAGE* dg = &Imgs;
	IMAGE* chara = &chas;
	DWORD* pBuffer;
	pBuffer = GetImageBuffer(dg);
	int x = 0, y = 480;
	int width = 1280, height = 300;
	int pic_x = 0, pic_y = 0;
	drawAlpha(dg, x, y, width, height, pic_x, pic_y, 0.9);
	char str[] = "色如果是";
	//_stprintf(str,_ ,_T("一二三"));
	settextcolor(RGB(255, 255, 255));
	settextstyle(50, 0, _T("黑体"));
	outtextxy(100, 550, string);
	Sleep(20);

	// putimage(0, 480, dg);
	// putimage(50, 530, chara);
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
void Draw(void)
{

	Game_Interface_4_Boat();

	putimage(mainChrx, mainChry, 32, 32, &maincharacter2, NumIndex * 32, 32 * NumOnto, SRCAND);	  // 掩码图或操作把人物放入
	putimage(mainChrx, mainChry, 32, 32, &maincharacter1, NumIndex * 32, 32 * NumOnto, SRCPAINT); // 掩码图以消除边框
}

// 此函数用于控制主角的移动
void mainChrKeyDown()
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
		Draw();
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

	Draw();
	while (1)
	{
		mainChrKeyDown();
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