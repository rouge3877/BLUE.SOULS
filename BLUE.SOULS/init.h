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
// 定义40*25的格子
#pragma comment(lib, "winmm.lib")


using namespace std;

// 定义一个结构体变量,用来存储RGB的值
typedef struct
{
	int rgb1;
	int rgb2;
	int rgb3;

} RGBS;


// 格子的全局变量
const int gridSize = GRIDSIZE; // 每个格子的大小
const int cols = UNIWIDTH;	   // 格子地图的列数
const int rows = UNIHEIGHT;	   // 格子地图的行数

typedef struct
{
	int lt_x;
	int lt_y;

	int rb_x;
	int rb_y;

} myBoxed;

void Initimage(void);
void Game_Interface_1_Welcome(void);
int Game_Interface_2_Manu(void);
void fallUni(int IndexInImgx, int IndexInImgy, int IndexInFallx, int IndexInFally, IMAGE* pimg);
void putBitimage(int IndexInImgx, int IndexInImgy, int IndexInFallx, int IndexInFally, IMAGE* psrc, IMAGE* pmarking);
int Game_Interface_3_Fire(void);
int Game_Interface_4_Boat(void);
void Draw_grs(int i, int j);
int Game_Iterface_5_Grass(void);

int drawMaze(void);