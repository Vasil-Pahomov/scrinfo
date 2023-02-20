
#include <NeoPixelBus.h>
#include "global.h"

#define FWX_NUM 10
#define FWX_SCALE 8

//общая "таблица скоростей", много градаций, нормированная, https://dotnetfiddle.net/TnTej6
#define FWX_SPEEDS 100
const short fwx_xsp[] PROGMEM = {0,7,15,23,31,39,46,54,61,68,74,80,86,92,97,102,107,111,114,118,120,123,124,125,126,127,126,125,124,123,120,118,114,111,107,102,97,92,86,80,74,68,61,54,46,39,31,23,15,7,0,-7,-15,-23,-31,-39,-46,-54,-61,-68,-74,-80,-86,-92,-97,-102,-107,-111,-114,-118,-120,-123,-124,-125,-126,-127,-126,-125,-124,-123,-120,-118,-114,-111,-107,-102,-97,-92,-86,-80,-74,-68,-61,-54,-46,-39,-31,-23,-15,-7};
const short fwx_ysp[] PROGMEM = {127,126,125,124,123,120,118,114,111,107,102,97,92,86,80,74,68,61,54,46,39,31,23,15,7,0,-7,-15,-23,-31,-39,-46,-54,-61,-68,-74,-80,-86,-92,-97,-102,-107,-111,-114,-118,-120,-123,-124,-125,-126,-127,-126,-125,-124,-123,-120,-118,-114,-111,-107,-102,-97,-92,-86,-80,-74,-68,-61,-54,-46,-39,-31,-23,-15,-7,0,7,15,23,31,39,46,54,61,68,74,80,86,92,97,102,107,111,114,118,120,123,124,125,126};

//текущая таблица скоростей (подмножество общей, случайно масштабированная)
short fwx_xs[FWX_NUM], fwx_ys[FWX_NUM];
//текущие координаты "частиц"
short fwx_x[FWX_NUM], fwx_y[FWX_NUM];

const RgbColor fwx_pal[] = {
{255,255,255},
{255,0,0},
{0,255,0},
{255,255,0},
{0,255,255},
{255,0,255}
};


void fwx_draw_blast(short xc, short yc, RgbColor clr) {
    for (short x=0;x<WT;x++) {
        for (short y=0;y<HT;y++) {
            short xs = x*FWX_SCALE, ys = y*FWX_SCALE;
            int r = (xs-xc)*(xs-xc) + (ys-yc)*(ys-yc);
            //Serial.print('(');Serial.print(x);Serial.print(',');Serial.print(y);Serial.print(')');Serial.print(r);Serial.print(' ');
            set_pixel_color(x, y, clr.Dim(max(255-r/16,0)));
        }
        //Serial.println();
    }
    bus_show();
}

void firewx_show() {
    //координаты центра взрыва (масштаб)
    short xc = random(WT*FWX_SCALE), yc=random(HT*FWX_SCALE);
    //short xc = 0*FWX_SCALE, yc=0*FWX_SCALE;

    
    for (int i=0;i<FWX_NUM;i++) {
        int gind = i*FWX_SPEEDS/FWX_NUM + random(FWX_SPEEDS/FWX_NUM/2);
        int gscl = 32+random(32);
        fwx_xs[i] = ((short)pgm_read_word(fwx_xsp + gind))/gscl;
        fwx_ys[i] = ((short)pgm_read_word(fwx_ysp + gind))/gscl;
        fwx_x[i] = xc;
        fwx_y[i] = yc;
    }

    fwx_draw_blast(xc,yc,RgbColor(255));
    delay(20);
    RgbColor clr = fwx_pal[random(sizeof(fwx_pal)/sizeof(RgbColor))];

    int cnt = 30+random(50);
    while (cnt>0) {
        
        /*for (int i=0;i<FWX_NUM;i++) {
            Serial.print(fwx_x[i]);Serial.print(',');Serial.print(fwx_y[i]);Serial.println('\t');
        }
        Serial.println();*/

        for (short x=0;x<WT;x++) {
            for (short y=0;y<HT;y++) {
                short xs = x*FWX_SCALE, ys = y*FWX_SCALE;
                RgbColor c = RgbColor(0);
                for (int i=0;i<FWX_NUM;i++) {
                    long r = (xs-fwx_x[i])*(xs-fwx_x[i]) + (ys-fwx_y[i])*(ys-fwx_y[i]);
                    RgbColor c2 = (r<64) ? clr.Dim(max(255-r*4,0)) : RgbColor(0);
                    /*if (i==9) {
                        Serial.print('(');Serial.print(x);Serial.print(',');Serial.print(y);Serial.print(')');
                        Serial.print(r);Serial.print('-');Serial.print(c2.CalculateBrightness());Serial.print(' ');
                    }*/
                    c.R = min(c.R+c2.R,255);
                    c.G = min(c.G+c2.G,255);
                    c.B = min(c.B+c2.B,255);
                }
                set_pixel_color(x,y,c);
            }
            //Serial.println();
        }
        bus_show();
        delay(10);

        for (int i=0;i<FWX_NUM;i++) {
            fwx_x[i] = min(max(fwx_x[i]+fwx_xs[i],-2*FWX_SCALE),(WT+2)*FWX_SCALE);
            fwx_y[i] = min(max(fwx_y[i]+fwx_ys[i],-2*FWX_SCALE),(HT+2)*FWX_SCALE);
        }

        cnt--;
    }

}