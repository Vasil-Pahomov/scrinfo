#include <global.h>

#define FLS_SCALE 8
#define FLS_MAX_NUM 3
#define FLS_MAX_SPEED 4
#define FLS_SPEED_CHANGE_DIVIDER 4

void flights_show(int durationSec) {

    unsigned long lastms = millis();

    int x[FLS_MAX_NUM], y[FLS_MAX_NUM], xs[FLS_MAX_NUM], ys[FLS_MAX_NUM],
        xc[FLS_MAX_NUM], yc[FLS_MAX_NUM], xcs[FLS_MAX_NUM], ycs[FLS_MAX_NUM];
    RgbColor clr[FLS_MAX_NUM];

    int flsNum = 2 + random(FLS_MAX_NUM-1);
    if (flsNum > FLS_MAX_NUM) flsNum = FLS_MAX_NUM;

    for (int i=0;i<flsNum;i++) {
        x[i] = random(WT*FLS_SCALE);
        y[i] = random(HT*FLS_SCALE);
        xs[i] = 0;
        ys[i] = 0;
        xc[i] = random(WT*FLS_SCALE);
        yc[i] = random(HT*FLS_SCALE);
        do {
            xcs[i] = random(FLS_SCALE) - FLS_SCALE/2;
            ycs[i] = random(FLS_SCALE) - FLS_SCALE/2;
        } while (xcs[i] == 0 || ycs[i] == 0);

        clr[i] = RgbColor(random(255), random(255), random(255));
    }

    byte lightmode = random(2);
    unsigned long endms = millis() + 1000L * durationSec;
    int tct = 0;

    while (millis() < endms) {
        wait_start();

        for (short xi=0;xi<WT;xi++) {
            for (short yi=0;yi<HT;yi++) {
                int xsc = xi*FLS_SCALE, ysc = yi*FLS_SCALE;
                RgbColor c = RgbColor(0);
                for (int i=0;i<flsNum;i++) {
                    long r = (xsc-x[i])*(xsc-x[i]) + (ysc-y[i])*(ysc-y[i]);
                    RgbColor c2 = lightmode 
                                ? clr[i].Dim(max((int)(255-r/2),0))
                                : clr[i].Dim(min(r ? (int)(4096/r) : 255,255));
                    /*if (i==0) {
                        Serial.print('(');Serial.print(xs);Serial.print(',');Serial.print(ys);Serial.print(')');
                        Serial.print(r);Serial.print('-');Serial.print(c2.CalculateBrightness());Serial.print(' ');
                    }*/
                    int radd = 0;//max(0, c.G + c2.G - 255) + max(0, c.B + c2.B - 255);
                    int gadd = 0;//max(0, c.R + c2.R - 255) + max(0, c.B + c2.B - 255);
                    int badd = 0;//max(0, c.R + c2.R - 255) + max(0, c.G + c2.G - 255);
                    c.R = min(c.R + c2.R + radd, 255);
                    c.G = min(c.G + c2.G + gadd, 255);
                    c.B = min(c.B + c2.B + badd, 255);
                }
                set_pixel_color(xi,yi,c);
            }
//Serial.println();
        }

        bus_show();
        
        for (int i=0;i<flsNum;i++) {

            x[i] += xs[i];
            y[i] += ys[i];

            if (tct == 0) {
                if (x[i] > xc[i]) {
                    if (xs[i] > -FLS_MAX_SPEED) xs[i]--;
                } else { 
                    if (xs[i] < FLS_MAX_SPEED) xs[i]++;
                }
                if (y[i] > yc[i]) {
                    if (ys[i] > -FLS_MAX_SPEED) ys[i]--;
                } else { 
                    if (ys[i] < FLS_MAX_SPEED) ys[i]++;
                }
            }
            
            xc[i] += xcs[i];
            yc[i] += ycs[i];
            if (xc[i] < 0) { xcs[i] = abs(xcs[i]); }
            if (xc[i] > (WT-1)*FLS_SCALE) { xcs[i] = -abs(xcs[i]); }
            if (yc[i] < 0) { ycs[i] = abs(ycs[i]); }
            if (yc[i] > (HT-1)*FLS_SCALE) { ycs[i] = -abs(ycs[i]); }
            
        }
        tct++; 
        if (tct > FLS_SPEED_CHANGE_DIVIDER) tct = 0;

        wait(20);
    }
}