#include "ControlMain.h"
#include "CommunicationBar.h"

extern IMAGE maincharacter1;
extern IMAGE maincharacter2;

// �����ƶ���ȫ�ֱ���
int NumIndex = 0;
int NumOnto = 3; // 0-�£�1-��2-�ң�3-��
int mainChrx = 20 * GRIDSIZE, mainChry = 9 * GRIDSIZE+10;


// �˺������ڽ�ɫ�ƶ�������mainChrKeyDown
void Draw(int(*Game_Interface)(void))
{
	Game_Interface();

	putimage(mainChrx, mainChry, 32, 32, &maincharacter2, NumIndex * 32, 32 * NumOnto, SRCAND);	  // ����ͼ��������������
	putimage(mainChrx, mainChry, 32, 32, &maincharacter1, NumIndex * 32, 32 * NumOnto, SRCPAINT); // ����ͼ�������߿�
}

//�˺��������ж���ײ���,����x,yΪ���������,box1Ϊ���������е�����,box2���Ժ�Ϊ���������е�����
bool judgeBox(int x, int y, myBoxed* validBox, ...)
{
    // ��������Ƿ�����Ч������
    if (!(x >= validBox->lt_x && x <= validBox->rb_x && y >= validBox->lt_y && y <= validBox->rb_y)) {
        return false;
    }

    va_list ap;
    myBoxed* p;
    va_start(ap, validBox);

    // ��������Ƿ��ڷǷ�������
    for (p = va_arg(ap, myBoxed*); p != NULL; p = va_arg(ap, myBoxed*)) {
        if (x >= p->lt_x && x <= p->rb_x && y >= p->lt_y && y <= p->rb_y) {
            va_end(ap);
            return false;
        }
    }

    va_end(ap);

    return true;
}

// �˺������ڿ������ǵ��ƶ�
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

