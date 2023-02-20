# scrinfo
Using Adruino and WS2812 LED screen to display various animations and ticker texts.

All animations are set up with code change, there's no external control of any kind (yet). 

Use Visual Studio Code and PlatformIO to compile.

## Circuit diagram
Connect D2 pin of your Arduino to the input of the first LED in a chain. Leds in my case form "snake" as shown in image below.

![](/schematic.png)

## Running with no hardware
There's a scrinfo.simu file which is project file for [SimulIDE](https://www.simulide.com/p/home.html) curcuit simulator 
