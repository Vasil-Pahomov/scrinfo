#include <Arduino.h>

#include "global.h"

#define FLAG_WAVE_SCALE 127
#define FLAG_WAVE_INC 3

const int8_t flag_wave[] = {16,32,47,61,75,87,98,107,115,121,125,127,127,125,121,115,107,98,87,75,61,47,32,16,0,-16,-32,-47,-61,-75,-87,-98,-107,-115,-121,-125,-127,-127,-125,-121,-115,-107,-98,-87,-75,-61,-47,-32,-16,0};

const RgbColor flag_pal[] = {
{0,0,0},
{192,192,192},
{255,0,0}};
const byte flag_pl[WT*HT] PROGMEM = {
#if BRD == BRD_BEL
0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
#elif BRD == BRD_POL
1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2,
0, 0, 0, 0, 0, 0, 0, 0,
#endif
};

void flag_show(int durationSec) {
    unsigned long endms = millis() + 1000L * durationSec;

    int wavepos = 40;

    while (millis() < endms) {
        wait_start();
        
        for (int row = 0; row < HT; row++) {
            //Serial.print(row);Serial.print(':');
            for (int col = 0; col < WT; col++) {
                int vdisp = 2*(int)flag_wave[(wavepos + col * FLAG_WAVE_INC) % sizeof(flag_wave)];
                int row1 =  row + ( (vdisp > 0) ? vdisp / 256 : -vdisp / 256 - 1 );
                int row2 = row1 + 1;
                RgbColor clr1 = (row1 >= 0 && row1 < HT) ? flag_pal[pgm_read_byte(flag_pl + row1 * WT + col)] : RgbColor(0);
                RgbColor clr2 = (row2 >= 0 && row2 < HT) ? flag_pal[pgm_read_byte(flag_pl + row2 * WT + col)] : RgbColor(0);
                int mix = (vdisp > 0) ? vdisp % 256 : 255 - ((-vdisp) % 256);
                RgbColor clr;
                clr.R = (int)clr1.R + (int)mix * ((int)clr2.R - (int)clr1.R) / 255;
                clr.G = (int)clr1.G + (int)mix * ((int)clr2.G - (int)clr1.G) / 255;
                clr.B = (int)clr1.B + (int)mix * ((int)clr2.B - (int)clr1.B) / 255;
                set_pixel_color(col, row, clr);
                //Serial.print(row1);Serial.print(',');Serial.print(row2);Serial.print(' ');
                //Serial.print(mix);Serial.print(' ');
            }
            //Serial.println();
        }
        bus_show();
        wavepos = (wavepos + 1 ) % sizeof(flag_wave);
        //Serial.println();
        //delay(100000);


        wait(20);
    }


}