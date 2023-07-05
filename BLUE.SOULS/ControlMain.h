#pragma once
#include "init.h"

bool judgeBox(int x, int y, myBoxed* validBox, ...);

void Draw(int(*Game_Interface)(void));

void mainChrKeyDown(int(*Game_Interface)(void), bool (*judgeFunc)(int x, int y, myBoxed* validBox, ...), myBoxed* validBox, ...);

bool checkCoordinate(int x, int y, myBoxed* validBox, ...);

