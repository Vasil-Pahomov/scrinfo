#include "global.h"

#define SNOWFLAKES 5 //количество снежинок

#define SNOWFLAKE_APPEAR_PROB 5 // шанс появления снежинки на очередном шаге, 1 к XX
#define SNOWFLAKE_STEP_PROB 2 // шанс продвижения снежинки вниз на очередном шаге, 1 к XX (величина, обратная средней скорости)
#define SNOWFLAKE_STEP_PAUSE 50 // задержка шага, миллисекунд

//координаты снежинок
byte snow_x[SNOWFLAKES];
byte snow_y[SNOWFLAKES];

RgbColor snowflake_color(255);
RgbColor snow_color(128,128,254);

void snow_show(int durationSec)
{
    for (int i=0;i<SNOWFLAKES;i++) {
        snow_x[i] = 255; //все снежинки неактивны
        snow_y[i] = 255;
    }
    cls();

    unsigned long endms = millis() + 1000L * durationSec;
    while (millis() < endms)
    {
        for (int i=0;i<SNOWFLAKES;i++) {
            if (snow_x[i] != 255) {
                if (snow_y[i] != 255) { //стираем предыдущее положение снежинки
                    set_pixel_color(snow_x[i], snow_y[i], RgbColor(0));
                }
                if (snow_y[i] >= HT-1 || get_pixel_color(snow_x[i], snow_y[i]+1) == snow_color) { // снежинка достигла "земли"?                    
                    //может ли снежинка "скатиться" влево или вправо?
                    bool canFallLeft = (snow_y[i] < HT-2) && (snow_x[i] > 0) && (get_pixel_color(snow_x[i]-1, snow_y[i]+2) != snow_color);
                    bool canFallRight = (snow_y[i] < HT-2) && (snow_x[i] < WT-1) && (get_pixel_color(snow_x[i]+1, snow_y[i]+2) != snow_color);
                    if (canFallLeft && canFallRight) { //если снежинка может скатиться в обе стороны, выбираем случайную сторону
                        if (random(2)) canFallLeft = false; else canFallRight = false;
                    }
                    if (canFallLeft) snow_x[i]--;
                    else if (canFallRight) snow_x[i]++;
                    else {
                        set_pixel_color(snow_x[i], snow_y[i], snow_color); // инактивируем снежинку, превращая её в снег
                        snow_x[i]=255; 
                        snow_y[i]=255;
                    }
                    
                } else { //снежинка не достигла "земли"
                    if (!random(SNOWFLAKE_STEP_PROB)) snow_y[i]++;  // продвигаем вниз
                    set_pixel_color(snow_x[i], snow_y[i], snowflake_color);
                }
            }
        }

        //если низ полностью заполнен снегом, опускаем вниз
        int i=0;
        while (i<WT) {
            if (get_pixel_color(i,HT-2) != snow_color) break;
            i++;
        }
        if (i>=WT) {
            for (i=0;i<WT;i++) {
                int j=HT-2;
                while (j>0) {
                    if (get_pixel_color(i,j) != snow_color) break;
                    j--;
                }
                set_pixel_color(i,j+1,RgbColor(0));
            }
        }
        if ((millis() < (endms - 3000)) && !random(SNOWFLAKE_APPEAR_PROB)) { //появляется новая снежинка
            int i=0;
            while (i<SNOWFLAKES && snow_x[i] != 255) i++; //ищем неактивную снежинку
            if (i<SNOWFLAKES) {  //нашли - активируем
                snow_x[i] = random(WT);
                snow_y[i] = 0;
            }
        }
        bus_show();
        delay(SNOWFLAKE_STEP_PAUSE);
    }
}

