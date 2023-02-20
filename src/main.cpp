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

}

void show_random_neutral() {
  switch (random(10)) {
    case 0:
      fill_show(60);
      break;
    case 1:
      flights_show(60);
      break;
    case 2:
      rain_show(60);
      break;
    case 3:
      switch(random(2)) {
        case 0:
          heart_flash_white();
          cls();
          break;
        case 1:
          heart_flash_red();
          break;
      }
      break;
    case 4:
      neighbours_run();
      break;
    case 5:
      neighbours_man_hand_and_wink();
      break;
    default:
    snow_show(60);
  }
}

void loop() {

  /* dzyady series (Win-1251 encoding for text)
  candle_show(120);
  ticker_run_text("�����",text_pal[random(sizeof(text_pal))]);
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
    ticker_run_text("Happy",text_pal[random(sizeof(text_pal))]);
    ticker_run_text("Halloween!",text_pal[random(sizeof(text_pal))]);
  }
  cls();
  /**/

  show_random_neutral();
  /*
  for (int i=0;i<10;i++) {
    firewx_show();
  }
  candle_show(60);

  if (random(2)) {
    ticker_run_text("� ����������!",text_pal[random(sizeof(text_pal))]);
  } else {
    ticker_run_text("� ������̲!",text_pal[random(sizeof(text_pal))]);
  }
  cls();
  delay(2000);
  */
  
  if (millis() > 4*3600000) {
    while (true) 
    {
      //candle_show(120);
      stars_show(3600, true);
    }
  }
}
