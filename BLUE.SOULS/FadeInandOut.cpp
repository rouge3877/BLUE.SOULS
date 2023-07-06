#include "FadeInandOut.h"


// 下面的函数实现渐入的效果,其中LOGFONT是一个结构体,用来存储字体的信息,x和y是输出的位置（左上角）,times是分割次数,sleeptime是间隔时间
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

// 下面的函数实现渐出的效果,其中LOGFONT是一个结构体,用来存储字体的信息,x和y是输出的位置（左上角）,times是分割次数,sleeptime是间隔时间
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

// 下面的函数旨在实现图片的渐暗效果,其中pImg是一个IMAGE类的对象,times是分割次数,sleeptime是间隔时间
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

//*下面的函数旨在实现图片的渐显效果,其中pImg是一个IMAGE类的对象,times是分割次数,sleeptime是间隔时间(尚未完成,在处理rgb时有问题, 速度很慢)
//void dark2Img(IMAGE Img, int times, int sleeptime)
//{
//
//	DWORD* pBuffer;
//	pBuffer = GetImageBuffer(&Img);
//
//	map<int, RGBS> Index_rgb;
//
//	int width = Img.getwidth();
//	int height = Img.getheight();
//
//	double r_incr, g_incr, b_incr;
//
//	int x, y, index;
//
//	for (y = 0; y < height; y++)
//	{
//		for (x = 0; x < width; x++)
//		{
//			index = y * width + x;
//
//			Index_rgb[index].rgb1 = GetRValue(pBuffer[index]);
//			Index_rgb[index].rgb2 = GetGValue(pBuffer[index]);
//			Index_rgb[index].rgb3 = GetBValue(pBuffer[index]);
//		}
//	}
//
//	BeginBatchDraw();
//	for (int j = times; j >= 0; j--)
//	{
//
//		Sleep(sleeptime);
//		for (y = 0; y < height; y++)
//		{
//			for (x = 0; x < width; x++)
//			{
//				index = y * width + x;
//
//				r_incr = static_cast<double>(Index_rgb[index].rgb1) / times;
//				g_incr = static_cast<double>(Index_rgb[index].rgb2) / times;
//				b_incr = static_cast<double>(Index_rgb[index].rgb3) / times;
//				pBuffer[index] = RGB(static_cast<int>(r_incr * (times - j)), static_cast<int>(g_incr * (times - j)), static_cast<int>(b_incr * (times - j)));
//			}
//		}
//		putimage(0, 0, &Img);
//		FlushBatchDraw();
//	}
//	EndBatchDraw();
//}