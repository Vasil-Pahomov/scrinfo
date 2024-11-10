#include "global.h"
#include "snow.h"



//цвета "минимальные", при "росте" они складываются
RgbColor grass_color(0,6,0);
RgbColor stem_color(2,8,2);

const RgbColor flowers_pal[] = {
{192,192,192},
{254,0,0},
{0,0,254},
{192,192,0},
{0,192,192},
{192,0,192}
};
#define SPRING_FLOWER_X WT/2 //X-координата цветка
#define SPRING_STEM_HEIGHT (HT-2) //высота стебля цветка

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
    if (y == HT || green_diff < snow_diff) {
        //зелень
        if (pc.G >= 254 || y == HT) y--; //если уже доросли до максимума в этой точке, либо если ничего в точке не было, идём выше на следующую
        if (HT-y > maxHeight) return 0; //доросли до максимума, хватит
        if (get_pixel_color(x,y).CalculateBrightness() == 0) {
            //начало роста
            set_pixel_color(x,y,clr);
        } else {
            //продолжение роста
            set_pixel_color(x,y,color_multi(get_pixel_color(x,y),2));
        }
    } else {
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
                for (int x=0;x<WT;x++) {
                    for (int y=0;y<HT;y++) {
                        int r = 10 * ((x-SPRING_FLOWER_X)*(x-SPRING_FLOWER_X) + (y-HT+SPRING_STEM_HEIGHT)*(y-HT+SPRING_STEM_HEIGHT));
                        if (r <= flrad) {
                            set_pixel_color(x,y,flower_color);
                        } else if (r <= (flrad+10)) {
                            byte dr = 25*(10-r+flrad);
                            if (dr != 0) {
                                if (x == SPRING_FLOWER_X && y > (HT-SPRING_STEM_HEIGHT)) {
                                    //поверх стебля смешивать
                                    set_pixel_color(x,y,stem_color.LinearBlend(stem_color,flower_color,(float)dr/255.0F));
                                } else {
                                    //иначе просто рисовать
                                    set_pixel_color(x,y,flower_color.Dim(dr));
                                }
                            }

                        }
                    }
                }
            }
        }
        bus_show();
        delay(50);
    }
    cls();
}
