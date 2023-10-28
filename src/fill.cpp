#include "global.h"
#include "Arduino.h"

void fill_show(int durationSec) {
    byte block[WT][HT];
    byte rndx[WT*HT], rndy[WT*HT]; //random coordinates
    unsigned long endms = millis() + 1000L * durationSec;
    while (millis() < endms) {

        //randomize coordinates
        for (byte i=0;i<HT*WT;i++) {
            rndx[i] = i % WT;
            rndy[i] = i / WT;
        }
        for (byte i=0;i<HT*WT;i++) {

            byte newi = random(HT*WT);
            
            byte tx = rndx[i],
                 ty = rndy[i];

            rndx[i] = rndx[newi],
            rndy[i] = rndy[newi];

            rndx[newi] = tx;
            rndy[newi] = ty;
        }

        memset(block, 0, HT*WT);
        byte x,y;
        byte dir = random(4);  //direction
        byte mode = random(2); //mode
        byte spnt = random(4); //starting point
        if (mode == 1) {
            if (!random(1)) {
                switch (dir) {
                    case 0:  // left
                        spnt = random(2)*3;
                        break;
                    case 1:  // up 
                        spnt = random(2);
                        break;
                    case 2:  // right
                        spnt = 1+random(2);
                        break;
                    case 3:  // down
                        spnt = 2+random(2);
                        break;
                }
            } else {
                spnt = 4;
            }
        }

        switch (spnt) 
        {
            case 0: // top left
                x=0;y=0;
                break;
            case 1: // top right
                x=WT-1;y=0;
                break;
            case 2: // bottom right
                x=WT-1;y=HT-1;
                break;
            case 3: // bottom left
                x=0;y=HT-1;
                break;
            default: // random
                x = 1 + random(WT-2);
                y = 1 + random(HT-2);
                break;
        }
        int steps = HT * WT;
        RgbColor clr;
        do {
            clr = RgbColor(random(255),random(256),random(256));
        } while (clr.CalculateBrightness() < 128);

        while (true) {
            set_pixel_color(x,y,clr);
            block[x][y] = 1;
            bool canGoRight = (x<WT-1) && !block[x+1][y];
            bool canGoLeft = (x>0) && !block[x-1][y];
            bool canGoUp = (y>0) && !block[x][y-1];
            bool canGoDown = (y<HT-1) && !block[x][y+1];

            switch (mode) {
                case 0: //ring in - clockwise (dir=1) and counterclockwise (dir=0) 
                    if (dir & 1) {
                        if (canGoRight && !canGoUp) { x++; }
                        else if (canGoDown && !canGoRight) { y++; }
                        else if (canGoLeft && !canGoDown) { x--;} 
                        else if (canGoUp && !canGoLeft) { y--; }
                    } else {
                        if (canGoRight && !canGoDown) { x++; }
                        else if (canGoDown && !canGoLeft) { y++; }
                        else if (canGoLeft && !canGoUp) { x--;} 
                        else if (canGoUp && !canGoRight) { y--; }
                    }
                    break;
                case 1: //directed snake - horizontal (dir=1) and vertical (dir=0)
                    switch (dir) {
                        case 0: //left
                            if (canGoLeft) { x--; }
                            else {
                                if (!canGoUp && !canGoDown) {
                                    x ++;
                                }
                                else if (canGoUp && canGoDown) {
                                    if (random(1)) { y--; } else { y++; }
                                } else {
                                    if (canGoUp) { y--; } 
                                    else if (canGoDown) { y++; } 
                                }
                            }
                            break;
                        case 1: //up
                            if (canGoUp) { y--; }
                            else {
                                if (!canGoLeft && !canGoRight) {
                                    y ++;
                                }
                                else if (canGoLeft && canGoRight) {
                                    if (random(1)) { x--; } else { x++; }
                                } else {
                                    if (canGoLeft) { x--; } 
                                    else if (canGoRight) { x++; } 
                                }
                            }
                            break;
                        case 2: //right
                            if (canGoRight) { x++; }
                            else {
                                if (!canGoUp && !canGoDown) {
                                    x --;
                                }
                                else if (canGoUp && canGoDown) {
                                    if (random(1)) { y--; } else { y++; }
                                } else {
                                    if (canGoUp) { y--; } 
                                    else if (canGoDown) { y++; } 
                                }
                            }
                            break;
                        case 3: //down
                            if (canGoDown) { y++; }
                            else {
                                if (!canGoLeft && !canGoRight) {
                                    y--;
                                }
                                else if (canGoLeft && canGoRight) {
                                    if (random(1)) { x--; } else { x++; }
                                } else {
                                    if (canGoLeft) { x--; } 
                                    else if (canGoRight) { x++; } 
                                }
                            }
                            break;
                    }
                    break;
                case 2: //random
                    x = rndx[steps];
                    y = rndy[steps];
                    break;
                default:
                    break;
            }

            fade_buffer(240);
            bus_show();
            delay(50);
            if (!(--steps)) break;

        }
    }
}
