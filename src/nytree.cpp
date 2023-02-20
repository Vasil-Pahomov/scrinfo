#include "global.h"

const byte nytree_pic[WT*HT] PROGMEM = {
0, 0, 1, 0, 0, 0,
0, 0, 2, 0, 0, 0,
0, 0, 3, 0, 0, 0,
0, 1, 3, 1, 0, 0,
0, 2, 3, 2, 0, 0,
0, 3, 3, 3, 0, 0,
0, 3, 3, 3, 0, 0,
1, 3, 3, 3, 1, 0,
2, 3, 3, 3, 2, 0,
3, 3, 3, 3, 3, 0,
3, 3, 3, 3, 3, 0,
};

const RgbColor nytree_pal[] = {
{0,0,0},
{0,2,0},
{0,8,1},
{0,32,2}
};

const RgbColor nytree_pal_white[] = {
{0,0,0},
{2,2,2},
{8,8,8},
{32,32,32}
};

const RgbColor nytree_pal_brb[] = {
{0,0,0},
{4,4,4},
{16,16,16},
{64,64,64}
};

const RgbColor nytree_sparks_pal[] = {
{192,192,192},
{255,0,0},
{0,0,255},
{192,192,0},
{192,0,192},
{0,192,192}
};

const RgbColor nytree_sparks_pal_brb[] = {
{255,0,0}
};

const RgbColor nytree_sparks_pal_blu[] = {
{255,0,0}
};


#define NYT_SPARKS 10 //количество огоньков на дереве
#define NYT_SPARK_APPEAR_PROB 100 //шанс появления огонька (1 к XXX)
#define NYT_SPART_DURATION 100 //время появления и пропадания огонька, кадров

int nyt_spark_phases[NYT_SPARKS];
unsigned char nyt_spark_color[NYT_SPARKS],
              nyt_spark_x[NYT_SPARKS],
              nyt_spark_y[NYT_SPARKS];

void nytree_show_impl(int durationSec, const RgbColor * treePal, const RgbColor * sparksPal, int sparksPalSize)
{
    unsigned long endms = millis() + 1000L * durationSec;
    while (millis() < endms)
    {
        display_pic_buf(nytree_pic, 0, 0, treePal);
        for (byte i=0;i<NYT_SPARKS;i++) {
            if (nyt_spark_phases[i]) {
                //яркость огонька (0..1)
                float bri = (nyt_spark_phases[i] > NYT_SPART_DURATION/2) 
                        ? (float)(NYT_SPART_DURATION - nyt_spark_phases[i]) / NYT_SPART_DURATION / 2.0
                        : (float) nyt_spark_phases[i] / NYT_SPART_DURATION / 2.0;
                RgbColor tcol = get_pixel_color(nyt_spark_x[i], nyt_spark_y[i]);
                set_pixel_color(nyt_spark_x[i], nyt_spark_y[i], tcol.LinearBlend(tcol, sparksPal[nyt_spark_color[i]],bri));
                //set_pixel_color(nyt_spark_x[i], nyt_spark_y[i], sparksPal[nyt_spark_color[i]]);
                nyt_spark_phases[i]--;
            } else {
                if (!random(NYT_SPARK_APPEAR_PROB)) {
                    nyt_spark_phases[i] = NYT_SPART_DURATION;
                    nyt_spark_color[i] = random(sparksPalSize);
                    //Serial.print('*');
                    while (true)
                    {
                        nyt_spark_x[i] = random(WT);
                        nyt_spark_y[i] = random(HT);
                        if (get_pixel_color(nyt_spark_x[i], nyt_spark_y[i]).CalculateBrightness() != 0) break;
                    }
                }
            }
        }
        bus_show();
        //delay(10);
    }
    cls();
}

void nytree_show(int durationSec) {
    int treePalIdx = random(2);
    int sparksPalIdx = random(3);
    if (!digitalRead(10)) {
        if (treePalIdx == 1 && sparksPalIdx == 1) {
            sparksPalIdx = 2;
        }
    }

    switch (sparksPalIdx) {
        case 0:
            nytree_show_impl(durationSec, treePalIdx ? nytree_pal : nytree_pal_white, nytree_sparks_pal, sizeof(nytree_sparks_pal)/sizeof(RgbColor));
        break;
        case 1:
            nytree_show_impl(durationSec, nytree_pal_white, nytree_sparks_pal_brb, sizeof(nytree_sparks_pal_brb)/sizeof(RgbColor));
        break;
        default:
            nytree_show_impl(durationSec, nytree_pal_white, nytree_sparks_pal_blu, sizeof(nytree_sparks_pal_blu)/sizeof(RgbColor));
        break;
    }
      
}


