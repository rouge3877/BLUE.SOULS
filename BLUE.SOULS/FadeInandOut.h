#pragma once
#include "init.h"


void lunixy_fade_in(const char* string, const LOGFONT* zfont, int x, int y, const RGBS* rgbs, int times, int sleeptime);

void lunixy_fade_out(const char* string, const LOGFONT* zfont, int x, int y, const RGBS* rgbs, int times, int sleeptime);

void Img2dark(IMAGE Img, int times, int sleeptime);

void dark2Img(IMAGE Img, int times, int sleeptime);

