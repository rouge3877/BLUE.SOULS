#pragma once
#include <graphics.h>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <map>
#include <stdarg.h>
#include <stdbool.h>

#define WIDTH 1280
#define HEIGHT 800
#define FPS 24
#define GRIDSIZE 32

#define UNIWIDTH WIDTH / GRIDSIZE
#define UNIHEIGHT HEIGHT / GRIDSIZE
// ����40*25�ĸ���
#pragma comment(lib, "winmm.lib")


using namespace std;

// ����һ���ṹ������������洢RGB��ֵ
typedef struct
{
	int rgb1;
	int rgb2;
	int rgb3;

} RGBS;


// ���ӵ�ȫ�ֱ���
const int gridSize = GRIDSIZE; // ÿ�����ӵĴ�С
const int cols = UNIWIDTH;	   // ���ӵ�ͼ������
const int rows = UNIHEIGHT;	   // ���ӵ�ͼ������

typedef struct
{
	int lt_x;
	int lt_y;

	int rb_x;
	int rb_y;

} myBoxed;

