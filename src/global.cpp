#include <NeoPixelBus.h>
#include "global.h"

#if defined(ESP8266)
#define NP_METHOD NeoEsp8266Uart1800KbpsMethod
#else 
#define NP_METHOD Neo800KbpsMethod
#endif

NeoPixelBus<NeoGrbFeature, NP_METHOD> * bus;

const RgbColor pal[5] = {
{0,0,0},      //0 - black 
{192,192,192},//1 - white
{255,0,0},    //2 - red
{0,255,0},    //3 - green
{255,128,128} //4 - light red
};

int inline pixind(int col,int row) {
  #if BRD == BRD_BEL
    return (col % 2) ? (row + col * HT) : ((HT - row) + col * HT - 1);
  #elif BRD == BRD_POL
    return !(col % 2) ? (row + (WT - 1 - col) * HT) : ((HT - row) + (WT - 1 - col) * HT - 1);
  #else 
    return row + col * HT;
  #endif
}

void global_setup() {
  bus = new NeoPixelBus<NeoGrbFeature,NP_METHOD> (WT*HT, 2);
  bus->Begin();
}

void fill_buffer(RgbColor color)
{
  for (int i=0; i<WT*HT; i++) { 
    bus->SetPixelColor(i, color);
  }
}

void cls()
{
  fill_buffer(RgbColor(0));
  bus_show();
}

void display_pic_buf(const byte* pic, byte darkenm, byte darkens, const RgbColor* pal)
{
  for (int i=0; i<WT*HT; i++) {
    int row = i / WT;
    int col = i % WT;
    RgbColor clr = pal[pgm_read_byte(pic+i)];
    clr.R = (int)clr.R * (256-darkenm) / 256;
    clr.G = (int)clr.G * (256-darkenm) / 256;
    clr.B = (int)clr.B * (256-darkenm) / 256;
    clr.Darken(darkens);
    set_pixel_color(col, row, clr);
  }
}

void display_pic(const byte* pic, byte darkenm, byte darkens, const RgbColor* pal)
{
  display_pic_buf(pic, darkenm, darkens, pal);
  bus_show();
}

void display_mixed_pics(const byte* pic1, const RgbColor* pal1, const byte* pic2, const RgbColor* pal2, byte mix) {
  for (int i=0; i<WT*HT; i++) {
    int row = i / WT;
    int col = i % WT;
    RgbColor clr1 = pal1[pgm_read_byte(pic1+i)];
    RgbColor clr2 = pal2[pgm_read_byte(pic2+i)];
    RgbColor clr;
    clr.R = (int)clr1.R + (int)mix * ((int)clr2.R - (int)clr1.R) / 255;
    clr.G = (int)clr1.G + (int)mix * ((int)clr2.G - (int)clr1.G) / 255;
    clr.B = (int)clr1.B + (int)mix * ((int)clr2.B - (int)clr1.B) / 255;
    set_pixel_color(col, row, clr);
  }
  bus_show();

}

void runad(const byte* ad, int adwt, int adwb, RgbColor clr) {
  for (int i=-WT;i<adwt+WT;i++) {
    for (byte col=0;col<WT;col++) {
      int byteoffset = (col+i) / 8;
      int bitmask = 1 << (7-((col+i) % 8));
      
      for (byte row=0;row<HT;row++) {
        byte pi = ((col+i) >= 0 && (col + i) <= adwt) 
          ? (ad[row*adwb+byteoffset] & bitmask)
          : 0;
          
        set_pixel_color(col, row, pi ? clr : RgbColor(0,0,0));
      }
    }
    bus_show();
    delay(100);
  }
}

void set_pixel_color(byte col, byte row, RgbColor clr) {
#if BRD == BRD_POL
  bus->SetPixelColor(pixind(col,row),RgbColor(clr.R, clr.G/2, clr.B/2));
#else
  bus->SetPixelColor(pixind(col,row), clr);
#endif
}

RgbColor get_pixel_color(byte col, byte row) {
#if BRD == BRD_POL
  //todo: think about removing this dirty hack 
  RgbColor c = bus->GetPixelColor(pixind(col,row));
  return RgbColor(c.R, c.G*2, c.B*2);
#else
  return bus->GetPixelColor(pixind(col,row));
#endif
}

void fade_buffer(uint8_t coef) {
  for (int i=0;i<HT*WT;i++) {
    bus->SetPixelColor(i, bus->GetPixelColor(i).Dim(coef));
  }
}

void bus_show() {
  bus->Show();
  /*
  Serial.println('*');
  for (byte row = 0; row < HT; row++) {
    for (byte col = 0; col < WT; col++) {
      Neo3Elements::ColorObject clr = bus->GetPixelColor(pixind(col, row));
      if (clr.CalculateBrightness()) {
        Serial.print('0');
      } else {
        Serial.print(' ');
      }
    }
    Serial.println();
  } /**/
}

int color_diff_norm(RgbColor c1, RgbColor c2) {
  if (c1==c2) return -1;

  int c1max = max(c1.R, max(c1.G, c1.B)) + 1;
  c1.R = (int)c1.R * (int)255 / c1max;
  c1.G = (int)c1.G * (int)255 / c1max;
  c1.B = (int)c1.B * (int)255 / c1max;

  int c2max = max(c2.R, max(c2.G, c2.B)) + 1;
  c2.R = (int)c2.R * (int)255 / c2max;
  c2.G = (int)c2.G * (int)255 / c2max;
  c2.B = (int)c2.B * (int)255 / c2max;

  return abs((int)c1.R-(int)c2.R) + abs((int)c1.G - (int)c2.G) + abs((int)c1.B - (int)c2.B);
}

RgbColor color_add(RgbColor c1, RgbColor c2) {
  RgbColor cr;
  cr.R = min((int)c1.R + (int)c2.R, (int)255);
  cr.G = min((int)c1.G + (int)c2.G, (int)255);
  cr.B = min((int)c1.B + (int)c2.B, (int)255);
  return cr;
}

RgbColor color_multi(RgbColor c, int factor) {
  RgbColor cr;
  cr.R = min((int)c.R * factor, (int)255);
  cr.G = min((int)c.G * factor, (int)255);
  cr.B = min((int)c.B * factor, (int)255);  
  return cr;
}

unsigned long wait_start_msec;

void wait_start() {
  wait_start_msec = millis();
}

void wait(int msec) {
  while (millis() < (wait_start_msec + msec)) delay(1);
}