#include "ControlMain.h"


extern IMAGE maincharacter1;
extern IMAGE maincharacter2;


// 人物移动的全局变量
int NumIndex = 0;
int NumOnto = 3; // 0-下；1-左；2-右；3-上
int mainChrx = WIDTH / 2, mainChry = HEIGHT / 2;

// 此函数用于角色移动函数中mainChrKeyDown
void Draw(int(*Game_Interface)(void))
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

void while_mainChrKeyDown(int(*Game_Interface)(void)) {

	cleardevice();
	Draw(Game_Interface);
	while (1)
	{
		mainChrKeyDown(Game_Interface);
	}
}