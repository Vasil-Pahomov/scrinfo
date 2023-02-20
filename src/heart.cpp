#include <Arduino.h>
#include "global.h"


const RgbColor pal_heart_w[] = {
{0,0,0},      
{48,48,48},
{192,192,192}
};

const RgbColor pal_heart_r[] = {
{0,0,0},      
{48,0,0},
{255,0,0}
};

const byte heart_1[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 1, 0, 0, 1, 0,
1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 0,
0, 0, 1, 1, 0, 0,
0, 0, 1, 1, 0, 0,
0, 0, 0, 0, 0, 0};

const byte heart_2[WT*HT] PROGMEM = {
0, 1, 0, 0, 1, 0,
1, 2, 1, 1, 2, 1,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
1, 2, 2, 2, 2, 1,
1, 2, 2, 2, 2, 1,
1, 2, 2, 2, 2, 1,
0, 1, 2, 2, 1, 0,
0, 1, 2, 2, 1, 0,
0, 0, 1, 1, 0, 0};

void heart_flash_brb()
{
  for (byte dk=0;dk<50;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_w);
    delay(10);
  }
  for (byte dk=0;dk<100;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_w);
    delay(10);
  }
  for (byte dk=0;dk<50;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_r);
    delay(10);
  }
  for (byte dk=0;dk<100;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_r);
    delay(10);
  }
  for (byte dk=0;dk<50;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_w);
    delay(10);
  }
  for (byte dk=0;dk<255;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_w);
    delay(10);
  }
  delay(500);
}

void heart_flash_red() 
{
  for (byte dk=0;dk<50;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_r);
    delay(10);
  }
  for (byte dk=0;dk<250;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_r);
    delay(10);
  }
  cls();
}

void heart_flash_white()
{
  for (byte dk=0;dk<50;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_w);
    delay(10);
  }
  for (byte dk=0;dk<250;dk+=1) {
    display_pic(heart_2,0,dk,pal_heart_w);
    delay(10);
  }
  cls();
}
