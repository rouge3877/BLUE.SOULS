#pragma once
#include "init.h"

// ����ĺ���ʵ�־��д�ӡ;RGBS��һ���ṹ�壬�����洢RGB��ֵ;RECT��һ���ṹ�壬�����洢���ε����ϽǺ����½�����;LOGFONT��һ���ṹ�壬�����洢�������Ϣ
void beginprint_center(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs);

// ����ĺ���ʵ�����ϽǴ�ӡ;RGBS��һ���ṹ�壬�����洢RGB��ֵ;RECT��һ���ṹ�壬�����洢���ε����ϽǺ����½�����;LOGFONT��һ���ṹ�壬�����洢�������Ϣ
void beginprint_topleft(const char* string, const LOGFONT* zfont, RECT* rbox, const RGBS* rgbs);

// ��ͼ����������͸���� AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1);

// �Ի���
void diabox(IMAGE Imgs, IMAGE chas, char* string);