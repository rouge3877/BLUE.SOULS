#pragma once
#include "init.h"

// 下面的函数实现居中打印;RGBS是一个结构体，用来存储RGB的值;RECT是一个结构体，用来存储矩形的左上角和右下角坐标;LOGFONT是一个结构体，用来存储字体的信息
void beginprint_center(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs);

// 下面的函数实现左上角打印;RGBS是一个结构体，用来存储RGB的值;RECT是一个结构体，用来存储矩形的左上角和右下角坐标;LOGFONT是一个结构体，用来存储字体的信息
void beginprint_topleft(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs);

// 绘图函数，补充透明度 AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1);

// 对话框
void diabox(IMAGE Imgs, IMAGE chas, char* string);