#include "CommunicationBar.h"


// ����ĺ���ʵ�־��д�ӡ;RGBS��һ���ṹ��,�����洢RGB��ֵ;RECT��һ���ṹ��,�����洢���ε����ϽǺ����½�����;LOGFONT��һ���ṹ��,�����洢�������Ϣ
void beginprint_center(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// ����ĺ���ʵ�����ϽǴ�ӡ;RGBS��һ���ṹ��,�����洢RGB��ֵ;RECT��һ���ṹ��,�����洢���ε����ϽǺ����½�����;LOGFONT��һ���ṹ��,�����洢�������Ϣ
void beginprint_topleft(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs)
{

	settextcolor(RGB(rgbs->rgb1, rgbs->rgb2, rgbs->rgb3));
	settextstyle(zfont);
	setbkmode(TRANSPARENT);
	drawtext(string, rbox, DT_LEFT | DT_TOP | DT_VCENTER | DT_SINGLELINE);
	setbkmode(OPAQUE);
}

// ��ͼ����,����͸���� AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA)
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer(); // GetImageBuffer() ����,���ڻ�ȡ��ͼ�豸���Դ�ָ��, EasyX �Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);	  // ��ȡ picture ���Դ�ָ��
	int imageWidth = image->getwidth();	  // ��ȡͼƬ���
	int imageHeight = image->getheight(); // ��ȡͼƬ���
	int dstX = 0;						  // �� ��ͼ���� �Դ������صĽǱ�
	int srcX = 0;						  // �� image �Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP , ��Ҷ˹���������е���ɫ�ĸ��ʼ���
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

