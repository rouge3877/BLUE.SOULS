#include "init.h"


// ����ĺ���ʵ�־��д�ӡ;RGBS��һ���ṹ�壬�����洢RGB��ֵ;RECT��һ���ṹ�壬�����洢���ε����ϽǺ����½�����;LOGFONT��һ���ṹ�壬�����洢�������Ϣ
void beginprint_center(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// ����ĺ���ʵ�����ϽǴ�ӡ;RGBS��һ���ṹ�壬�����洢RGB��ֵ;RECT��һ���ṹ�壬�����洢���ε����ϽǺ����½�����;LOGFONT��һ���ṹ�壬�����洢�������Ϣ
void beginprint_topleft(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_LEFT | DT_TOP | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}



// ��ͼ����������͸���� AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer(); // GetImageBuffer() ���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬 EasyX �Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);	  // ��ȡ picture ���Դ�ָ��
	int imageWidth = image->getwidth();	  // ��ȡͼƬ����
	int imageHeight = image->getheight(); // ��ȡͼƬ����
	int dstX = 0;						  // �� ��ͼ���� �Դ������صĽǱ�
	int srcX = 0;						  // �� image �Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// ��ֹԽ��
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < WIDTH && iy + y >= 0 && iy + y < HEIGHT)
			{
				// ��ȡ���ؽǱ�
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * WIDTH;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA; // 0xAArrggbb; AA ��͸����
				int sr = ((src[srcX] & 0xff0000) >> 16);		// ��ȡ RGB ��� R
				int sg = ((src[srcX] & 0xff00) >> 8);			// G
				int sb = src[srcX] & 0xff;						// B

				// ���ö�Ӧ�Ļ�ͼ����������Ϣ
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  // ��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8) // ��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);		  // ��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

// �Ի���
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
	char str[] = "ɫ�����";
	//_stprintf(str,_ ,_T("һ����"));
	settextcolor(RGB(255, 255, 255));
	settextstyle(50, 0, _T("����"));
	outtextxy(100, 550, string);
	Sleep(20);

	// putimage(0, 480, dg);
	// putimage(50, 530, chara);
}