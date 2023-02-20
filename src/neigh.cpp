#include <Arduino.h>
#include "global.h"

// 'neighbours', 35x11px
const unsigned char neigh []  = {
	0x30, 0x60, 0xc1, 0x83, 0x00, 0x30, 0x60, 0xc1, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 
	0xf1, 0xe3, 0xc7, 0x80, 0xb5, 0x6a, 0xd5, 0xab, 0x40, 0xb5, 0x6a, 0xd5, 0xab, 0x40, 0x30, 0x60, 
	0xc1, 0x83, 0x00, 0x48, 0x91, 0x22, 0x44, 0x80, 0x48, 0x91, 0x22, 0x44, 0x80, 0x48, 0x91, 0x22, 
	0x44, 0x80, 0xcd, 0x9b, 0x36, 0x6c, 0xc0
};

const RgbColor neigh_pal[] = {
{0,0,0},
{192,192,64},
{64,32,32},
{64,64,255},    
{192,64,64},
{64,64,8}
};

const byte neigh_m_norm[WT*HT] PROGMEM = {
0, 0, 1, 1, 0, 0,
0, 0, 1, 1, 0, 0,
0, 0, 0, 0, 0, 0,
0, 2, 2, 2, 2, 0,
1, 0, 2, 2, 0, 1,
1, 0, 2, 2, 0, 1,
0, 0, 2, 2, 0, 0,
0, 1, 0, 0, 1, 0,
0, 1, 0, 0, 1, 0,
0, 1, 0, 0, 1, 0,
1, 1, 0, 0, 1, 1,
};

const byte neigh_m_hand[WT*HT] PROGMEM = {
0, 0, 1, 1, 0, 0,
1, 0, 1, 1, 0, 0,
1, 0, 0, 0, 0, 0,
0, 2, 2, 2, 2, 0,
0, 0, 2, 2, 0, 1,
0, 0, 2, 2, 0, 1,
0, 0, 2, 2, 0, 0,
0, 1, 0, 0, 1, 0,
0, 1, 0, 0, 1, 0,
0, 1, 0, 0, 1, 0,
1, 1, 0, 0, 1, 1,
};

const byte neigh_m_zoom[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 0,
0, 0, 1, 1, 0, 0,
0, 0, 0, 0, 0, 0,
2, 2, 2, 2, 2, 2,
0, 2, 2, 2, 2, 0,
0, 2, 2, 2, 2, 0,
0, 2, 2, 2, 2, 0,
0, 2, 2, 2, 2, 0,
};

const byte neigh_m_face_norm[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 0,
1, 0, 0, 0, 0, 1,
1, 3, 0, 0, 3, 1,
1, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 1,
1, 0, 4, 4, 0, 1,
1, 0, 0, 0, 0, 1,
0, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
};

const byte neigh_m_face_wink[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 0,
1, 0, 0, 0, 0, 1,
1, 0, 0, 0, 3, 1,
1, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 1,
1, 0, 4, 4, 0, 1,
1, 0, 0, 0, 0, 1,
0, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
};

const byte neigh_m_face_smile[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 0,
1, 0, 0, 0, 0, 1,
1, 3, 0, 0, 3, 1,
1, 0, 0, 0, 0, 1,
1, 4, 0, 0, 4, 1,
1, 0, 4, 4, 0, 1,
1, 0, 0, 0, 0, 1,
0, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
};


const byte neigh_w_norm[WT*HT] PROGMEM = {
0, 0, 5, 5, 0, 0,
0, 5, 1, 1, 5, 0,
0, 5, 1, 1, 5, 0,
0, 1, 2, 2, 1, 0,
1, 0, 2, 2, 0, 1,
1, 2, 2, 2, 2, 1,
0, 2, 2, 2, 2, 0,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
0, 1, 0, 0, 1, 0,
1, 1, 0, 0, 1, 1,
};

const byte neigh_w_hand[WT*HT] PROGMEM = {
0, 0, 5, 5, 0, 0,
1, 5, 1, 1, 5, 0,
1, 5, 1, 1, 5, 0,
0, 1, 2, 2, 1, 0,
0, 0, 2, 2, 0, 1,
0, 2, 2, 2, 2, 1,
0, 2, 2, 2, 2, 0,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
0, 1, 0, 0, 1, 0,
1, 1, 0, 0, 1, 1,
};

const byte neigh_w_zoom[WT*HT] PROGMEM = {
0, 0, 5, 5, 0, 0,
0, 5, 1, 1, 5, 0,
0, 5, 1, 1, 5, 0,
0, 5, 1, 1, 5, 0,
0, 5, 0, 0, 5, 0,
0, 5, 2, 2, 5, 0,
1, 1, 2, 2, 1, 1,
0, 2, 2, 2, 2, 0,
0, 2, 2, 2, 2, 0,
2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2,
};

const byte neigh_w_face_norm[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 5, 5, 5, 5, 0,
5, 5, 5, 5, 5, 5,
5, 3, 0, 0, 3, 5,
5, 0, 0, 0, 0, 5,
5, 0, 0, 0, 0, 5,
5, 0, 4, 4, 0, 5,
5, 1, 1, 1, 1, 5,
5, 0, 0, 0, 0, 5,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
};

const byte neigh_w_face_wink[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 5, 5, 5, 5, 0,
5, 5, 5, 5, 5, 5,
5, 0, 0, 0, 3, 5,
5, 0, 0, 0, 0, 5,
5, 0, 0, 0, 0, 5,
5, 0, 4, 4, 0, 5,
5, 1, 1, 1, 1, 5,
5, 0, 0, 0, 0, 5,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
};

const byte neigh_w_face_smile[WT*HT] PROGMEM = {
0, 0, 0, 0, 0, 0,
0, 5, 5, 5, 5, 0,
5, 5, 5, 5, 5, 5,
5, 3, 0, 0, 3, 5,
5, 0, 0, 0, 0, 5,
5, 4, 0, 0, 4, 5,
5, 0, 4, 4, 0, 5,
5, 1, 1, 1, 1, 5,
5, 0, 0, 0, 0, 5,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
};
void neighbours_run()
{
    runad(neigh,35,5, RgbColor(192,192,192));  
}

void neighbours_man_hand_and_wink()
{
	for (int i=255;i>0;i--) {
		display_pic(neigh_m_norm, i, 0, neigh_pal);
	}
	delay(1000);
	display_pic(neigh_m_hand, 0, 0, neigh_pal);
	delay(2000);
	display_pic(neigh_m_zoom, 0, 0, neigh_pal);
	delay(500);
	display_pic(neigh_m_face_norm, 0, 0, neigh_pal);
	delay(2000);
	for (int i=0;i<255;i+=5) {
		display_mixed_pics(neigh_m_face_norm, neigh_pal, neigh_m_face_wink, neigh_pal, i);
	}
	for (int i=0;i<255;i+=5) {
		display_mixed_pics(neigh_m_face_wink, neigh_pal, neigh_m_face_smile, neigh_pal, i);
	}
	delay(5000);
	for (int i=0;i<255;i++) {
		display_pic(neigh_m_face_smile, i, 0, neigh_pal);
	}
	for (int i=255;i>0;i--) {
		display_pic(neigh_w_norm, i, 0, neigh_pal);
	}
	delay(1000);
	display_pic(neigh_w_hand, 0, 0, neigh_pal);
	delay(2000);
	display_pic(neigh_w_zoom, 0, 0, neigh_pal);
	delay(500);
	display_pic(neigh_w_face_norm, 0, 0, neigh_pal);
	delay(2000);
	for (int i=0;i<255;i+=5) {
		display_mixed_pics(neigh_w_face_norm, neigh_pal, neigh_w_face_wink, neigh_pal, i);
	}
	for (int i=0;i<255;i+=5) {
		display_mixed_pics(neigh_w_face_wink, neigh_pal, neigh_w_face_smile, neigh_pal, i);
	}
	delay(5000);
	for (int i=0;i<255;i++) {
		display_pic(neigh_w_face_smile, i, 0, neigh_pal);
	}
}
