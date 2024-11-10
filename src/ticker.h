#include <NeoPixelBus.h>

//runnign ticker text animation
void ticker_run_text(const char* text, RgbColor clr, bool flip = false);

typedef RgbColor (*TickerPixelColor)(int, int, bool);

void ticker_run_text(const char* test, TickerPixelColor pixclr, bool flip = false);
