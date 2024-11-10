// êàë³ ãýòû

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
#include "flag.h"

#ifdef ESP8266
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <ArduinoOTA.h>
#include <sunset.h>
#define LATITUDE 51.759445
#define LONGITUDE 19.457216
#define DST_OFFSET 1
WiFiManager wifiManager;
WiFiUDP ntpUdp;
NTPClient ntpClient(ntpUdp, DST_OFFSET*3600);
SunSet sun;

struct tm datetime;
byte night_show;
#define NIGHT_SHOW_STARS 0
#define NIGHT_SHOW_CANDLE 1
#define NIGHT_SHOW_NYTREE 2


#endif

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
  Serial.begin(115200);
  randomSeed(analogRead(0)*analogRead(1));
  global_setup();
#ifdef ESP8266
  wifiManager.autoConnect();
  ntpClient.begin();
  sun.setPosition(LATITUDE, LONGITUDE, DST_OFFSET);
  delay(5000);
#endif
}

RgbColor _ticker_color_wrw(int x, int y, bool pixel) {
  if (pixel) {
    if (y >= HT / 3 && y < HT * 2 / 3) {
      return RgbColor(255,0,0);
    } else {
      return RgbColor(192,192,192);
    }
  } else {
    return RgbColor(0);
  }
}

RgbColor _ticker_color_yb(int x, int y, bool pixel) {
  if (pixel) {
    if (y >= HT / 2) {
      return RgbColor(255,255,0);
    } else {
      return RgbColor(128,128,255);
    }
  } else {
    return RgbColor(0);
  }
}

RgbColor _ticker_color_wr(int x, int y, bool pixel) {
  if (pixel) {
    if (y >= HT / 2) {
      return RgbColor(255,0,0);
    } else {
      return RgbColor(192,192,192);
    }
  } else {
    return RgbColor(0);
  }
}

void show_random_neutral() {
  cls();
  switch (random(7)) {
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
#ifdef ESP8266
      if (datetime.tm_mon == 2) {
        snow_show(30);
        spring_show();
      }
      else if (datetime.tm_mon >= 3 && datetime.tm_mon <= 4) {
        spring_show();
      }
      else if (datetime.tm_mon >= 11 || datetime.tm_mon <= 1) {
        snow_show(60);
      } else 
#endif
      { 
        heart_flash_white();
        heart_flash_red();
      }
      break;
    case 4:
      heart_flash_red();
      break;
    case 5:
      heart_flash_white();
      break;
    default:
        candle_show(60);
      break;
  }
}


/*  (Win-1251 encoding for text) */
void normalOp() {

#ifdef ESP8266
  night_show = NIGHT_SHOW_STARS;

  if (datetime.tm_mon == 1 && datetime.tm_mday == 14) {
    heart_flash_br();
    switch (random(7)) {
      case 0:
        ticker_run_text("Szczº¾liwych Walentynek!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
      case 1:
        ticker_run_text("Z cašego serca gratulujº Ci wspaniašego Dnia Zakochanych!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
      case 2:
        ticker_run_text("Niech mišo¾Ÿ rozkwita w ka´dym dniu Twojego ´ycia!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
      case 3:
        ticker_run_text("¥yczº Ci wiele rado¾ci, mišo¾ci i sšodkich chwil w Dniu Zakochanych!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
      case 4:
        ticker_run_text("Niech mišo¾Ÿ bºdzie Twoim najwiºkszym skarbem w Dniu Zakochanych i ka´dego dnia!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
      case 5:
        ticker_run_text("Z okazji Dnia Zakochanych ´yczº Ci wielu cudownych chwil z ukochanž osobž!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
      default:
        ticker_run_text("Mišego dnia zakochanych!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
        break;
    }
  }
  else if (datetime.tm_mon == 7 && datetime.tm_mday == 15) {
    ticker_run_text("Chwaša bohaterom, obroœcom Polski!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
    for (int i=0;i<10;i++) firewx_show();
    flag_show(30);
    candle_show(120);
    night_show = NIGHT_SHOW_CANDLE;
  } else if (datetime.tm_year == 125 && datetime.tm_mon == 05 && datetime.tm_mday == 19) {
    ticker_run_text("Bšogosšawionych ½wižt Bo´ego Ciaša!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
    candle_show(60);
  } else if ((datetime.tm_mon == 9 && datetime.tm_mday == 31) || (datetime.tm_mon == 10 && datetime.tm_mday == 1)) {
    candle_show(30);
    ticker_run_text("Dzieœ Wszystkich ½wiºtych",text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
    halloween_faces();
    night_show = NIGHT_SHOW_CANDLE;
  } else if (datetime.tm_mon == 10 && (datetime.tm_mday == 10 || datetime.tm_mday == 11)) {
    ticker_run_text("NIECH ¥YJE POLSKA", _ticker_color_wr);
    heart_flash_br();
    flag_show(60);
#ifdef BRD_POL
  } else if (datetime.tm_mon == 10 && (datetime.tm_mday == 14 || datetime.tm_mday == 24)) {
    ticker_run_text("ÂÅÐÎÍÈÊÀ, Ñ ÄÍ¨Ì ÐÎÆÄÅÍÈß!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)], true);
    show_random_neutral();
#endif    
  } else
  #endif
  {
    show_random_neutral();
  }


  //candle_show(60);
  //ticker_run_text("WIEKLANOC", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);

  /*
  //XMas
  //ticker_run_text("WESOï¿½YCH ï¿½WIï¿½T!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);

  switch (random(3)) {
    case 0:
      //ticker_run_text("SZCZï¿½ï¿½LIWEGO NOWEGO ROKU!", text_pal[random(sizeof(text_pal))/sizeof(RgbColor)]);
      nytree_show(60);
      break;
    default:
      show_random_neutral();
      break;
  }
  */


  //11.11
}

void nightOp() {
#ifdef ESP8266
  switch (night_show) {
    case NIGHT_SHOW_CANDLE:
      candle_show(600);
      break;
    case NIGHT_SHOW_NYTREE:
      nytree_show(600);
      break;
    default:
      stars_show(600, true);
      break;
  }
#else
  stars_show(600, true);
#endif
}


void loop() {

#ifdef ESP8266
  ntpClient.update();
  if (ntpClient.isTimeSet())
  {
    time_t tt = ntpClient.getEpochTime();
    gmtime_r(&tt,&datetime);
    //Serial.print(ntpClient.getFormattedTime());
    //Serial.printf(" %d.%d.%d\r\n", 1900+datetime.tm_year, 1+datetime.tm_mon, datetime.tm_mday);    

    sun.setCurrentDate(1900+datetime.tm_year, 1+datetime.tm_mon, datetime.tm_mday);
    int sunrise = static_cast<int>(sun.calcSunrise());
    int sunset = static_cast<int>(sun.calcSunset());
    
    //Serial.printf("Sunrise at %2d:%2d, Sunset at %2d:%2d\r\n", (sunrise/60), (sunrise%60), (sunset/60), (sunset%60));    

    int curdayminutes = ntpClient.getHours()*60 + ntpClient.getMinutes();

    if (curdayminutes < sunrise || curdayminutes > 22 * 60) {
      nightOp();
    } else if (curdayminutes > sunset) {
      normalOp();
    } else {
      cls();
      delay(60000);
    }
  } else
  {
    Serial.println(F("Time not set"));
    ticker_run_text("!!!!!!", RgbColor(1,1,1));
  }
#else
  if (millis() > 5*3600000) {
    nightOp();
  } else {
    normalOp();
  }
#endif 
}
