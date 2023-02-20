#include "global.h"
#include "Arduino.h"

const RgbColor rain_pal[] = {
{255,255,255},
{255,128,128},
{128,128,255},
{255,255,128},
{255,128,255},
{128,255,255}
};

#define RAIN_NUM 10 // количество "капель"
#define RAIN_PROB 10 // шанс появления капли в очередном кадре (1 к XXX)

byte rain_color[RAIN_NUM],
    rain_x[RAIN_NUM],
    rain_y[RAIN_NUM];

void rain_show(int durationSec) {
    unsigned long endms = millis() + 1000L * durationSec;

    for (byte i=0;i<RAIN_NUM;i++) rain_y[i] = HT; //капли нет

    while (millis() < endms)
    {
        fade_buffer(128);

        for (byte i=0;i<RAIN_NUM;i++) {
            if (rain_y[i] < HT) {
                set_pixel_color(rain_x[i], rain_y[i], rain_pal[rain_color[i]]);
                rain_y[i]++;
            } else {
                if ((millis() < (endms - 3000)) && !random(RAIN_PROB)) {
                    rain_color[i] = random(sizeof(rain_pal)/sizeof(RgbColor));
                    rain_x[i] = random(WT);
                    rain_y[i] = 0;
                }
            }
        }
        bus_show();
        delay(50);
    }
    cls();
}