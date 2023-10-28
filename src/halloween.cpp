#include <Arduino.h>
#include "global.h"
#include "ticker.h"

const byte hlw_1[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
0, 0, 0, 2, 0, 0,
0, 0, 2, 0, 0, 0,
0, 1, 1, 1, 1, 0,
1, 3, 1, 1, 3, 1,
1, 1, 1, 1, 1, 1,
1, 3, 3, 3, 3, 1,
1, 3, 3, 3, 3, 1,
0, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0
#elif BRD == BRD_POL
0, 0, 0, 2, 2, 0, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 1, 1, 1, 1, 1, 1, 0,
1, 1, 3, 1, 1, 3, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1,
1, 3, 3, 3, 3, 3, 3, 1,
1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 1, 0,
0, 0, 1, 1, 1, 1, 0, 0,
#endif
};

const byte hlw_2[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
0, 0, 0, 2, 0, 0,
0, 0, 2, 0, 0, 0,
0, 1, 1, 1, 1, 0,
1, 3, 1, 1, 3, 1,
1, 1, 1, 1, 1, 1,
1, 3, 3, 3, 3, 1,
1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0
#elif BRD == BRD_POL
0, 0, 0, 2, 2, 0, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 1, 1, 1, 1, 1, 1, 0,
1, 1, 3, 1, 1, 3, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1,
1, 3, 3, 3, 3, 3, 3, 1,
1, 3, 3, 3, 3, 3, 3, 1,
0, 1, 1, 1, 1, 1, 1, 0,
0, 0, 1, 1, 1, 1, 0, 0,
#endif
};

const byte hlw2_1[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
2, 0, 0, 0, 0, 2,
2, 2, 0, 0, 2, 2,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
0, 2, 2, 2, 2, 0,
2, 0, 0, 0, 0, 2,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0
#elif BRD == BRD_POL
0, 0, 0, 0, 0, 0, 0, 0,
2, 0, 0, 0, 0, 0, 0, 2,
2, 2, 0, 0, 0, 0, 2, 2,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 2, 2, 2, 2, 0, 0,
0, 2, 0, 0, 0, 0, 2, 0,
0, 0, 0, 0, 0, 0, 0, 0,
#endif
};

const byte hlw2_2[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
2, 0, 0, 0, 0, 2,
2, 2, 0, 0, 2, 2,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
0, 2, 2, 2, 2, 0,
2, 1, 1, 1, 1, 2,
2, 2, 2, 2, 2, 2,
0, 0, 0, 0, 0, 0
#elif BRD == BRD_POL
0, 0, 0, 0, 0, 0, 0, 0,
2, 0, 0, 0, 0, 0, 0, 2,
2, 2, 0, 0, 0, 0, 2, 2,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 2, 2, 2, 2, 0, 0,
0, 2, 1, 1, 1, 1, 2, 0,
0, 2, 2, 2, 2, 2, 2, 0,
#endif
};

const RgbColor pal_hlw[] = {
{0,0,0},      
{32,8,0},
{0,64,0},    
{255,0,0}
};

void halloween_faces()
{
  const int step = 5;
  //halloween faces

  switch (random(2)) {
    case 0:
      for (int i=0;i<10;i++) {
        for (int m=0;m<255;m+=step) {
          display_mixed_pics(hlw2_1,pal,hlw2_2,pal,m);
        }
        for (int m=0;m<255;m+=step) {
          display_mixed_pics(hlw2_2,pal,hlw2_1,pal,m);
        }
        display_pic(hlw2_1, 0, 0, pal);
        delay(500);
      }
    break;
    case 1:
      for (int i=0;i<10;i++) {
        for (int m=0;m<255;m+=step) {
          display_mixed_pics(hlw_1,pal_hlw,hlw_2,pal_hlw,m);
        }
        for (int m=0;m<255;m+=step) {
          display_mixed_pics(hlw_2,pal_hlw,hlw_1,pal_hlw,m);
        }
        display_pic(hlw_1, 0, 0, pal_hlw);
        delay(500);
      }
    break;
    default:
    break;
  }
  cls();
  ticker_run_text("HAPPY HALLOWEEN", pal[1+random(sizeof(pal)/sizeof(RgbColor)-1)]);
  cls();
  delay(500);
}
