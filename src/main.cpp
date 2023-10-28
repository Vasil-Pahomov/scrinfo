#include <Arduino.h>
#include <NeoPixelBus.h>
#include "global.h"
#include "heart.h"
#include "stars.h"
#include "candle.h"
#include "ticker.h"
#include "neigh.h"
#include "rain.h"
#include "spring.h"
#include "egg.h"
#include "firewx.h"
#include "halloween.h"
#include "snow.h"
#include "nytree.h"
#include "fill.h"
#include "flights.h"
#include "egg.h"

const RgbColor text_pal[] = {
{192,192,192},
{255,32,32},
{32,32,255},
{32,255,32},
{255,255,32},
{32,255,255},
{255,32,255}
};

void setup() {
  randomSeed(analogRead(0)*analogRead(1));
  global_setup();
  Serial.begin(115200);
  pinMode(10, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

void show_random_neutral() {
  switch (random(5)) {
    case 0:
      Serial.println("fill");
      fill_show(60);
      break;
    case 1:
      Serial.println("flights");
      flights_show(60);
      break;
    case 2:
      rain_show(60);
      Serial.println("rain");
      break;
    case 3:
      heart_flash_br();
      break;
    case 4:
      Serial.println("firewx");
      for (int i=0;i<10;i++) {
        candle_show(60);
      }
      break;
    default:
      cls();
      Serial.println("stars-rn");
      stars_show(60, true);
      break;
  }
}

/*  (Win-1251 encoding for text) */
void loop() {


  /* dzyady series
  candle_show(120);
  ticker_run_text("�����",text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
  /**/
  /* halloween series
  stars_show(120, true);
  cls();
  switch(random(2)) {
    case 0:
      halloween_faces();
      cls();
      break;
    case 1:
      candle_show(60);
      break;
  }
  if (random(2)) {
    ticker_run_text("Happy",text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
    ticker_run_text("Halloween!",text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
  }
  cls();
  /**/

  /* March 8 series 
  if (random(2)) {
    ticker_run_text("� ���������� �����, ����� � �������!",text_pal[random(sizeof(text_pal)/sizeof(RgbColor))]);
  } else {
    ticker_run_text("�� ������ �����, ������� �� �����!",text_pal[random(sizeof(text_pal)/sizeof(RgbColor))]);
  }

  if (random(2)) {
    heart_flash_red();
  } else {
    heart_flash_red();
  }
  spring_show();
  if (random(2)) {
    heart_flash_red();
  } else {
    heart_flash_red();
  }
  /**/

  /*
  for (int i=0;i<10;i++) {
    firewx_show();
  }
  candle_show(60);

  if (random(2)) {
    ticker_run_text("� ����������!",text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
  } else {
    ticker_run_text("� ������̲!",text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
  }
  cls();
  delay(2000);
  */

  ticker_run_text("Happy Halloween!", RgbColor(255,255,255));

  halloween_faces();

  show_random_neutral();
  
  if (millis() > 5*3600000) {
    while (true) 
    {
      //candle_show(120);
      Serial.println("stars-to");
      stars_show(3600, true);
    }
  }
}
