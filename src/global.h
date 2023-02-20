#include <NeoPixelBus.h>

#define WT 6   //screen width in pixels
#define HT 11  //screen height in pixels

extern const RgbColor pal[];

void global_setup();

void set_pixel_color(byte col, byte row, RgbColor clr);

RgbColor get_pixel_color(byte col, byte row);

//displays pixel buffer physically to the panel
void bus_show();

//fills buffer with specified color
void fill_buffer(RgbColor color);

//clears the panel
void cls();

//faldes a pixel buffer with coef (when coef=128 the color values are halved)
void fade_buffer(uint8_t coef);

//displays a picture to the buffer
void display_pic_buf(const byte* pic, byte darkenm, byte darkens, const RgbColor* pal);

//displays a picture to the panel 
void display_pic(const byte* pic, byte darkenm, byte darkens, const RgbColor* pal);


//отображение двух картинок с заданной степенью "наложения"
void display_mixed_pics(const byte* pic1, const RgbColor* pal1, const byte* pic2, const RgbColor* pal2, byte mix);


//отображение "бегущей строки" из битовой картинки
void runad(const byte* ad, int adwt, int adwb, RgbColor col);

//складывает покомпонентно цвета (с насыщением)
RgbColor color_add(RgbColor c1, RgbColor c2);

//умножает компоненты цвета на заданное число (с насыщением)
RgbColor color_multi(RgbColor c, int factor);

//расчёт разницы между цветами после нормализации максимального уровня к 255; -1 если цвета полностью идентичны
int color_diff_norm(RgbColor c1, RgbColor c2);