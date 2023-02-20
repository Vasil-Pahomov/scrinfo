#include "global.h"
#include "snow.h"



//цвета "минимальные", при "росте" они складываются
RgbColor grass_color(0,6,0);
RgbColor stem_color(1,8,1);

const RgbColor flowers_pal[] = {
{192,192,192},
{255,0,0},
{0,0,255},
{192,192,0},
{0,192,192},
{192,0,192}
};
#define SPRING_FLOWER_X 3 //X-координата цветка
#define SPRING_STEM_HEIGHT 9 //высота стебля цветка

byte spring_melt_grow(byte x, RgbColor clr, byte maxHeight) {
    byte y = HT-1;
    while (y>0 && get_pixel_color(x,y).CalculateBrightness() > 0) {
        y--;
    }

    y++;
    RgbColor pc = get_pixel_color(x,y);

    RgbColor grc = color_multi(clr, 32);
    int green_diff = color_diff_norm(pc, grc);
    int snow_diff = color_diff_norm(pc, snow_color);

    /*Serial.print("Point at at x="); Serial.print(x); Serial.print(" y="); Serial.print(y); 
    Serial.print(" grc=");Serial.print(grc.R);Serial.print(',');Serial.print(grc.G);Serial.print(',');Serial.print(grc.B);
    Serial.print(" clr=");Serial.print(pc.R);Serial.print(',');Serial.print(pc.G);Serial.print(',');Serial.print(pc.B);
    Serial.print(" green_diff=");Serial.print(green_diff); Serial.print(" ,snow_diff=");Serial.println(snow_diff);*/

    if (y == HT || green_diff < snow_diff) {
        //Serial.println("Green"); 
        //зелень
        if (green_diff < 0 || y == HT) y--; //если уже доросли до максимума в этой точке, либо если ничего в точке не было, идём выше на следующую
        if (HT-y > maxHeight) return 0; //доросли до максимума, хватит
        if (get_pixel_color(x,y).CalculateBrightness() == 0) {
            //начало роста
            set_pixel_color(x,y,clr);
            //Serial.print("Start grow at x="); Serial.print(x); Serial.print(" y="); Serial.println(y);
        } else {
            //продолжение роста
            //Serial.print("Go on grow at x="); Serial.print(x); Serial.print(" y="); Serial.println(y);
            set_pixel_color(x,y,color_multi(get_pixel_color(x,y),2));
        }
    } else {
        //Serial.println("Snow"); 
        //снег - таем
        set_pixel_color(x,y,get_pixel_color(x,y).Dim(32));
    }
    return 1;
}


void spring_show()
{
    unsigned long endms = millis() + 20000L;


    RgbColor flower_color = flowers_pal[random(sizeof(flowers_pal)/sizeof(RgbColor))];

    int flrad = -10;
    
    while (millis() < endms)
    {
        if (random(3)) {
            //растим траву
            int x;
            do {
                x = random(WT);
            } while (x == SPRING_FLOWER_X);

            spring_melt_grow(x, grass_color, 3);
        } else {
            //растим цветок
            if (flrad > -10 || !spring_melt_grow(SPRING_FLOWER_X, stem_color, SPRING_STEM_HEIGHT)) {
                //стебель вырос, теперь сам цветок
                if (flrad<60) flrad+=2;
                //Serial.println(flrad);
                for (int x=0;x<WT;x++) {
                    for (int y=0;y<HT;y++) {
                        int r = 10 * ((x-SPRING_FLOWER_X)*(x-SPRING_FLOWER_X) + (y-HT+SPRING_STEM_HEIGHT)*(y-HT+SPRING_STEM_HEIGHT));
                        Serial.print(r);
                        if (r <= flrad) {
                            set_pixel_color(x,y,flower_color);
                            //Serial.print("-*");
                        } else if (r <= (flrad+10)) {
                            byte dr = 25*(10-r+flrad);
                            //Serial.print('-');Serial.print(dr);
                            if (dr != 0) {
                                if (x == SPRING_FLOWER_X && y > (HT-SPRING_STEM_HEIGHT)) {
                                    //Serial.print('b');
                                    //поверх стебля смешивать
                                    set_pixel_color(x,y,stem_color.LinearBlend(stem_color,flower_color,(float)dr/255.0));
                                } else {
                                    //иначе просто рисовать
                                    set_pixel_color(x,y,flower_color.Dim(dr));
                                }
                            }

                        }
                        //Serial.print('\t');
                    }
                    //Serial.println();
                }
            }
        }
        bus_show();
        delay(50);
    }
    cls();
}
