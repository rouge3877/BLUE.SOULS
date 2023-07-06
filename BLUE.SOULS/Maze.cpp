#include "init.h"



extern IMAGE stn_grs1;
extern IMAGE stn_grs2;


int maze[13][13] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0,1,1,0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0,1,0,0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 0,1,1,0},
    {0, 1, 0, 0, 0, 1, 0, 1, 1, 0,0,1,0},
    {0, 1, 1, 1, 1, 1, 0, 1, 0, 0,0,0,1},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 1,0,1,0},
    {0, 1, 0, 1, 1, 1, 1, 1, 0, 0,0,0,0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0,1,1,0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 0,1,0,0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0,0,0,0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 0,1,0,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,1,0},
};




myBoxed firel[100];
int fireliboxndex = 0;


int drawMaze(void) {

    for (int x = 13; x < 27; x++) {
        for (int y = 6; y < 20; y++) {
           
            if (x * y % 6 == 0)  fallUni(3, 6, x, y, &stn_grs1);
            else if (x * y % 6 == 1) fallUni(4, 6, x, y, &stn_grs1);
            else if (x * y % 6 == 2) fallUni(3, 7, x, y, &stn_grs1);
            else if (x * y % 6 == 3) fallUni(4, 7, x, y, &stn_grs1);
            else if (x * y % 6 == 4) fallUni(3, 8, x, y, &stn_grs1);
            else fallUni(4, 8, x, y, &stn_grs1);

            if (maze[x-13][y-6] == 1) {
                // »æÖÆÃÔ¹¬Ç½±Ú
                if(x*y%2==0) putBitimage(4, 2, x, y, &stn_grs1, &stn_grs2);
                else if(x*y%3==0) putBitimage(2, 2, x, y, &stn_grs1, &stn_grs2);
                else putBitimage(0, 1, x, y, &stn_grs1, &stn_grs2);
                /*setfillcolor(WHITE);
                solidrectangle(x * GRIDSIZE, y * GRIDSIZE, (x + 1) * GRIDSIZE, (y + 1) * GRIDSIZE);*/
                firel[fireliboxndex] = { (x-1) * GRIDSIZE,(y-1) * GRIDSIZE,x  * GRIDSIZE,y * GRIDSIZE };
            }
        }
    }
    int ret = fireliboxndex;
    fireliboxndex = 0;
    return ret + 1;
}
