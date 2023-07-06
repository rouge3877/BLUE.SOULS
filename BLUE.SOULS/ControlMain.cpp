#include "ControlMain.h"
#include "CommunicationBar.h"

extern IMAGE maincharacter1;
extern IMAGE maincharacter2;

// 人物移动的全局变量
int NumIndex = 0;
int NumOnto = 3; // 0-下；1-左；2-右；3-上
int mainChrx = 20 * GRIDSIZE, mainChry = 9 * GRIDSIZE+10;


// 此函数用于角色移动函数中mainChrKeyDown
void Draw(int(*Game_Interface)(void))
{
	Game_Interface();

	putimage(mainChrx, mainChry, 32, 32, &maincharacter2, NumIndex * 32, 32 * NumOnto, SRCAND);	  // 掩码图或操作把人物放入
	putimage(mainChrx, mainChry, 32, 32, &maincharacter1, NumIndex * 32, 32 * NumOnto, SRCPAINT); // 掩码图以消除边框
}

//此函数用于判断碰撞体积,其中x,y为人物的坐标,box1为必须在其中的坐标,box2及以后为不可在其中的坐标
bool judgeBox(int x, int y, myBoxed* validBox, ...)
{
    // 检查坐标是否在有效区域内
    if (!(x >= validBox->lt_x && x <= validBox->rb_x && y >= validBox->lt_y && y <= validBox->rb_y)) {
        return false;
    }

    va_list ap;
    myBoxed* p;
    va_start(ap, validBox);

    // 检查坐标是否在非法区域内
    for (p = va_arg(ap, myBoxed*); p != NULL; p = va_arg(ap, myBoxed*)) {
        if (x >= p->lt_x && x <= p->rb_x && y >= p->lt_y && y <= p->rb_y) {
            va_end(ap);
            return false;
        }
    }

    va_end(ap);

    return true;
}

// 此函数用于控制主角的移动
void mainChrKeyDown(int(*Game_Interface)(void), bool (*judgeFunc)(int x, int y, myBoxed* validBox, ...), myBoxed* validBox, ...)
{
    int c;
    bool result = true;
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
            mainChrx -= 5;
            break;
        case 'd':
        case 'D':
        case 77:
            mainChrx += 5;
            break;
        case 'w':
        case 'W':
        case 72:
            mainChry -= 5;
            break;
        case 's':
        case 'S':
        case 80:
            mainChry += 5;
            break;
        }

        va_list ap;
        myBoxed* p;
        va_start(ap, validBox);
        result = judgeBox(mainChrx, mainChry, validBox, ap, NULL);
        if (!result) {
            result = false;
        }
        else {
            for (p = va_arg(ap, myBoxed*); p != NULL; p = va_arg(ap, myBoxed*)) {
                if (!judgeBox(mainChrx, mainChry, validBox, p, NULL)) {
                    result = false;
                    break;
                }
            }
        }
        va_end(ap);

        if (!result) {
            switch (c) {
            case 'a':
            case 'A':
            case 75:
                mainChrx += 5;
                break;
            case 'd':
            case 'D':
            case 77:
                mainChrx -= 5;
                break;
            case 'w':
            case 'W':
            case 72:
                mainChry += 5;
                break;
            case 's':
            case 'S':
            case 80:
                mainChry -= 5;
                break;
            }
        }

        NumOnto = (result) ? ((c == 'a' || c == 'A' || c == 75) ? 1 : (c == 'd' || c == 'D' || c == 77) ? 2 : (c == 'w' || c == 'W' || c == 72) ? 3 : 0) : NumOnto;

        Draw(Game_Interface);
        NumIndex = (NumIndex + 1) % 3;

        char xoy[12];
        snprintf(xoy, 12, "x=%3d,y=%3d", mainChrx, mainChry);

        RGBS titlergb11 = { 255, 255, 255 };
        RECT titlebox11 = { 0, 0, WIDTH * 1.5, 120 };
        LOGFONT titlefont11 = { 8, 0, 0, 0, 500, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, "Times New Roman" };

        beginprint_center(xoy, &titlefont11, &titlebox11, &titlergb11);
        EndBatchDraw();
    }
}

