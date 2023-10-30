#include "global.h"

const RgbColor stars_pal[] = {
{255,255,255},
{255,128,128},
{128,128,255},
{255,255,128},
{255,128,255},
{128,255,255}
};

#define STARS_NUM 10 // max. stars quantity
#define STAR_APPEAR_PROB 100 // star appearance probability at each frame (1 to XXX)
#define STAR_DURATION 255 //time to appear and fade a star, frames

int star_phase[STARS_NUM];
unsigned char star_x[STARS_NUM],
              star_y[STARS_NUM];
RgbColor star_color[STARS_NUM];
byte lvls[]={0, 8, 16, 32, 64, 128, 255};


void stars_show(int durationSec, bool useRandomColors) {

    cls();
    unsigned long endms = millis() + 1000L * durationSec;

    while (millis() < endms)
    {
        for (byte i=0;i<STARS_NUM;i++) {
            if (star_phase[i]) {
                //яркость огонька (0..1)
                int bri = (star_phase[i] > STAR_DURATION/2) 
                        ? 511 * (STAR_DURATION - star_phase[i]) / STAR_DURATION
                        : 511 * (star_phase[i]-1) / STAR_DURATION ;
                set_pixel_color(star_x[i], star_y[i], star_color[i].Dim(bri));
                star_phase[i]--;
            } else {
                if ((millis() < (endms - 3000)) && !random(STAR_APPEAR_PROB)) {
                    //Serial.print(millis());Serial.print('M');Serial.print(enduams);Serial.println('E');
                    star_phase[i] = STAR_DURATION;
                    while (true)
                    {
                        star_x[i] = random(WT);
                        star_y[i] = random(HT);
                        if (get_pixel_color(star_x[i], star_y[i]).CalculateBrightness() == 0) break;
                    }
                    if (useRandomColors) {
                        do {
                            star_color[i] = RgbColor(lvls[random(sizeof(lvls))], lvls[random(sizeof(lvls))], lvls[random(sizeof(lvls))]);
                        } while (star_color[i].CalculateBrightness() < 8);
                    } else {
                        star_color[i] = stars_pal[random(sizeof(stars_pal)/sizeof(RgbColor))];
                    }
                }
            }
        }
        bus_show();

        delay(10);
    }
    cls();
}