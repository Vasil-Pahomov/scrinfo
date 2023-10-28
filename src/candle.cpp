#include <Arduino.h>
#include "global.h"

const byte candle_1[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 3, 0, 0, 0,
0, 0, 2, 3, 0, 0,
0, 3, 2, 2, 3, 0,
0, 3, 2, 2, 3, 0,
0, 0, 2, 2, 0, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0
#elif BRD == BRD_POL
0, 0, 0, 3, 0, 0, 0, 0,
0, 0, 0, 2, 3, 0, 0, 0,
0, 0, 3, 2, 2, 3, 0, 0,
0, 0, 3, 2, 2, 3, 0, 0,
0, 0, 0, 2, 2, 0, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0
#endif
};

const byte candle_2[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0,
0, 0, 3, 2, 0, 0,
0, 0, 2, 3, 0, 0,
0, 0, 2, 0, 0, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0
#elif BRD == BRD_POL
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 3, 0, 0, 0,
0, 0, 0, 3, 2, 0, 0, 0,
0, 0, 0, 2, 3, 0, 0, 0,
0, 0, 0, 2, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
#endif
};

const byte candle_3[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 3, 0, 0,
0, 0, 3, 2, 0, 0,
0, 3, 2, 2, 3, 0,
0, 3, 2, 2, 3, 0,
0, 0, 2, 2, 0, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0
#elif BRD == BRD_POL
0, 0, 0, 0, 3, 0, 0, 0,
0, 0, 0, 3, 2, 0, 0, 0,
0, 0, 3, 2, 2, 3, 0, 0,
0, 0, 3, 2, 2, 3, 0, 0,
0, 0, 0, 2, 2, 0, 0, 0,
0, 0, 1, 1, 4, 4, 0, 0,
0, 0, 1, 1, 4, 4, 0, 0,
0, 0, 1, 1, 4, 4, 0, 0,
0, 0, 1, 1, 4, 4, 0, 0
#endif
};

const byte candle_4[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
0, 0, 3, 0, 0, 0,
0, 0, 2, 3, 0, 0,
0, 0, 3, 2, 0, 0,
0, 0, 0, 2, 0, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0,
0, 1, 1, 4, 4, 0
#elif BRD == BRD_POL
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0,
0, 0, 0, 2, 3, 0, 0, 0,
0, 0, 0, 3, 2, 0, 0, 0,
0, 0, 0, 0, 2, 0, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 0, 0,
#endif
};
static const RgbColor pal_candle[] = {
{0,0,0},      
{8,4,4},
{255,64,0},
{64,16,0},
{8,8,8}
};


void candle_show(int durationSecs)
{
  const byte * prevPic = candle_1, 
             * nextPic = prevPic;
  unsigned long startMs = millis();
  while ( (millis() - startMs) < (unsigned long)durationSecs * 1000L ) {
    while (nextPic == prevPic) {
      switch (random(4)) {
        case 0: 
          nextPic = candle_1;
          break;
        case 1: 
          nextPic = candle_2;
          break;
        case 2: 
          nextPic = candle_3;
          break;
        case 3: 
          nextPic = candle_4;
          break;
      }
    }
    for (int m=0;m<255;m+=5) {
      display_mixed_pics(prevPic, pal_candle, nextPic, pal_candle, m);
    }
    prevPic = nextPic;
  }
  cls();
}
