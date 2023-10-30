#include <Arduino.h>
#include "global.h"

#define CANDLE_SCALE 8
#define CANDLE_FBALLS 3
#define CANDLE_SPEED_CHANGE_DIVIDER 1
#define CANDLE_MAX_SPEED 4
#define CANDLE_FBALL_PUSH_PROB 10

#if BRD == BRD_POL
  const byte candle_base[WT*HT] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1
  };
  #define CANDLE_FLAME_MAXY 4*CANDLE_SCALE
  #define CANDLE_FLAME_MINY 1*CANDLE_SCALE
#endif


static const RgbColor pal_candle[] = {
{0,0,0},      
{8,4,4},
{255,64,0},
{64,16,0},
{8,8,8}
};


void candle_show(int durationSecs)
{

  int x[CANDLE_FBALLS], y[CANDLE_FBALLS], xc[CANDLE_FBALLS], yc[CANDLE_FBALLS], xs[CANDLE_FBALLS], ys[CANDLE_FBALLS];
  RgbColor clr[CANDLE_FBALLS];

  for (int i=0;i<CANDLE_FBALLS;i++) {
    xc[i] = WT*CANDLE_SCALE/2 - CANDLE_SCALE/2;
    x[i] = xc[i];
    yc[i] = CANDLE_FLAME_MINY + i*(CANDLE_FLAME_MAXY-CANDLE_FLAME_MINY)/(CANDLE_FBALLS-1);
    y[i] = yc[i];
    xs[i] = 0;
    ys[i] = 0;
   
    clr[i] = RgbColor(255,64,0);
  }
  unsigned long endMs = millis() + durationSecs * 1000L;  
  int tct = 0;
  while ( millis() < endMs) {
        wait_start();
        display_pic_buf(candle_base,0,0,pal_candle);
        for (short xi=0;xi<WT;xi++) {
            for (short yi=0;yi<HT;yi++) {
                int xsc = xi*CANDLE_SCALE, ysc = yi*CANDLE_SCALE;
                RgbColor c = get_pixel_color(xi,yi);
                for (int i=0;i<CANDLE_FBALLS;i++) {
                    long r = (xsc-x[i])*(xsc-x[i]) + (ysc-y[i])*(ysc-y[i]);
                    RgbColor c2 = clr[i].Dim(max((int)(255-r),0)); 

                    int radd = max(0, c.G + c2.G - 255) + max(0, c.B + c2.B - 255);
                    int gadd = max(0, c.R + c2.R - 255) + max(0, c.B + c2.B - 255);
                    int badd = max(0, c.R + c2.R - 255) + max(0, c.G + c2.G - 255);
                    c.R = min(c.R + c2.R + radd, 255);
                    c.G = min(c.G + c2.G + gadd, 255);
                    c.B = min(c.B + c2.B + badd, 255);
                }
                set_pixel_color(xi,yi,c);
            }
        }

        bus_show();
        

        for (int i=0;i<CANDLE_FBALLS;i++) {

            x[i] += xs[i];
            y[i] += ys[i];

            if (tct == 0) {
                if (x[i] > xc[i]) {
                    if (xs[i] > -CANDLE_MAX_SPEED) xs[i]--;
                } else { 
                    if (xs[i] < CANDLE_MAX_SPEED) xs[i]++;
                }
                if (y[i] > yc[i]) {
                    if (ys[i] > -CANDLE_MAX_SPEED) ys[i]--;
                } else if (y[i] < yc[i]) { 
                    if (ys[i] < CANDLE_MAX_SPEED) ys[i]++;
                }
            }

            if (!random(CANDLE_FBALL_PUSH_PROB)) {
                if (xs[i] > 0) {
                    xs[i] = random((CANDLE_FBALLS - i));
                } else {
                    xs[i] = -random((CANDLE_FBALLS - i));
                } 
                
                if (ys[i] > 0) {
                    ys[i] = random(CANDLE_FBALLS - i);
                } else {
                    ys[i] = -random(CANDLE_FBALLS - i);
                } 
                
            }            
        }
        tct++; 
        if (tct > CANDLE_SPEED_CHANGE_DIVIDER) tct = 0;

        wait(20);
    }
}
