#include "ControlMain.h"


extern IMAGE maincharacter1;
extern IMAGE maincharacter2;


// �����ƶ���ȫ�ֱ���
int NumIndex = 0;
int NumOnto = 3; // 0-�£�1-��2-�ң�3-��
int mainChrx = WIDTH / 2, mainChry = HEIGHT / 2;

// �˺������ڽ�ɫ�ƶ�������mainChrKeyDown
void Draw(int(*Game_Interface)(void))
{
	Game_Interface();

	putimage(mainChrx, mainChry, 32, 32, &maincharacter2, NumIndex * 32, 32 * NumOnto, SRCAND);	  // ����ͼ��������������
	putimage(mainChrx, mainChry, 32, 32, &maincharacter1, NumIndex * 32, 32 * NumOnto, SRCPAINT); // ����ͼ�������߿�
}

// �˺������ڿ������ǵ��ƶ�
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
		NumIndex = (NumIndex + 1) % 3; // ��ѭ��������0-3֮��ѭ����ѡ����ͼ
		EndBatchDraw();
	}
}

void while_mainChrKeyDown(int(*Game_Interface)(void)) {

	cleardevice();
	Draw(Game_Interface);
	while (1)
	{
		mainChrKeyDown(Game_Interface);
	}
}