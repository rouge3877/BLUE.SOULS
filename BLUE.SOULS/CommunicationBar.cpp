#include "CommunicationBar.h"


// 下面的函数实现居中打印;RGBS是一个结构体,用来存储RGB的值;RECT是一个结构体,用来存储矩形的左上角和右下角坐标;LOGFONT是一个结构体,用来存储字体的信息
void beginprint_center(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// 下面的函数实现左上角打印;RGBS是一个结构体,用来存储RGB的值;RECT是一个结构体,用来存储矩形的左上角和右下角坐标;LOGFONT是一个结构体,用来存储字体的信息
void beginprint_topleft(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_LEFT | DT_TOP | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// 绘图函数,补充透明度 AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA)
{

	// 变量初始化
	DWORD* dst = GetImageBuffer(); // GetImageBuffer() 函数,用于获取绘图设备的显存指针, EasyX 自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);	  // 获取 picture 的显存指针
	int imageWidth = image->getwidth();	  // 获取图片宽度
	int imageHeight = image->getheight(); // 获取图片宽度
	int dstX = 0;						  // 在 绘图区域 显存里像素的角标
	int srcX = 0;						  // 在 image 显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP , 贝叶斯定理来进行点颜色的概率计算
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
void diabox(IMAGE Imgs, IMAGE chas1, IMAGE chas2,const char* string)
{
	IMAGE* dg = &Imgs;
	IMAGE* chara1 = &chas1;
	IMAGE* chara2 = &chas2;
	DWORD* pBuffer;
	pBuffer = GetImageBuffer(dg);
	int x = 0, y = 620;
	int width = 1280, height = 300;
	int pic_x = 0, pic_y = 0;
	drawAlpha(dg, x, y, width, height, pic_x, pic_y, 0.7);
	putimage(50, 650, chara2, SRCAND);
	putimage(50, 650, chara1, SRCPAINT);

	LOGFONT titlefontbar = { 40, 0, 0, 0, 100, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SCRIPT, "Times New Roman" };
	RGBS titlergbbar = { 255, 255, 255 };
	RECT titleboxbar = {200, 650, WIDTH -100, HEIGHT-100 };
	beginprint_topleft(string, &titlefontbar, &titleboxbar, &titlergbbar);

}

