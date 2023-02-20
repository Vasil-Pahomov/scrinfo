#include <NeoPixelBus.h>
#include "global.h"

const RgbColor egg_pal[] = {
{0,0,0},
{8,8,8},
{32,32,32},
{192,192,192},
{255,0,0},
{0,0,255},
{192,0,192},
{8,2,0},
{32,8,0},
{192,48,0},

};

const byte egg_pic[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 0, 1, 1, 0, 0,
0, 1, 2, 2, 1, 0,
1, 2, 3, 3, 2, 1,
2, 3, 3, 3, 3, 2,
2, 3, 3, 3, 3, 2,
3, 3, 3, 3, 3, 3,
3, 3, 3, 3, 3, 3,
2, 3, 3, 3, 3, 2,
0, 2, 3, 3, 2, 0,
0, 0, 0, 0, 0, 0,
};

const byte egg_pic_2[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 0, 1, 1, 0, 0,
0, 1, 2, 2, 1, 0,
1, 2, 3, 3, 2, 1,
2, 3, 3, 3, 3, 2,
4, 4, 4, 4, 4, 4,
4, 4, 4, 4, 4, 4,
3, 3, 3, 3, 3, 3,
2, 3, 3, 3, 3, 2,
0, 2, 3, 3, 2, 0,
0, 0, 0, 0, 0, 0,
};

const byte egg_pic_3[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 0, 1, 1, 0, 0,
0, 1, 2, 2, 1, 0,
1, 2, 3, 3, 2, 1,
2, 3, 3, 3, 3, 2,
5, 5, 5, 5, 5, 5,
5, 5, 5, 5, 5, 5,
3, 3, 3, 3, 3, 3,
2, 3, 3, 3, 3, 2,
0, 2, 3, 3, 2, 0,
0, 0, 0, 0, 0, 0,
};

const byte egg_pic_4[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 0, 1, 1, 0, 0,
0, 1, 2, 2, 1, 0,
1, 2, 3, 3, 2, 1,
2, 3, 3, 3, 3, 2,
6, 6, 6, 6, 6, 6,
6, 6, 6, 6, 6, 6,
3, 3, 3, 3, 3, 3,
2, 3, 3, 3, 3, 2,
0, 2, 3, 3, 2, 0,
0, 0, 0, 0, 0, 0,
};

const byte egg_pic_5[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 0, 7, 7, 0, 0,
0, 7, 8, 8, 7, 0,
7, 8, 9, 9, 8, 7,
8, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 8,
9, 9, 9, 9, 9, 9,
9, 9, 9, 9, 9, 9,
8, 9, 9, 9, 9, 8,
0, 8, 9, 9, 8, 0,
0, 0, 0, 0, 0, 0,
};



void egg_show()
{
    display_pic(egg_pic, 0,0, egg_pal);
    delay(5000);
    for (int i=0;i<255;i++) {
        display_mixed_pics(egg_pic,egg_pal,egg_pic_2,egg_pal,i);
        delay(5);
    }
    for (int i=0;i<255;i++) {
        display_mixed_pics(egg_pic_2,egg_pal,egg_pic_3,egg_pal,i);
        delay(5);
    }
    for (int i=0;i<255;i++) {
        display_mixed_pics(egg_pic_3,egg_pal,egg_pic_4,egg_pal,i);
        delay(5);
    }
    for (int i=0;i<255;i++) {
        display_mixed_pics(egg_pic_4,egg_pal,egg_pic_5,egg_pal,i);
        delay(5);
    }
    delay(5000);

}