#include  "Arduino.h"
#include "U8glib.h"
const uint8_t Robotics[] U8G_PROGMEM = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xc0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xfe,0x0,0x0,0x3,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xc0,0x0,0x0,0x0,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xf8,0x0,0x0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x80,0x0,0x0,0x0,0x0,0x78,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xfe,0x0,0x0,0x0,0x0,0x0,0x78,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xf0,0x0,0x0,0x0,0x0,0x0,0x78,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x80,0x0,0x0,0x0,0x0,0x0,0x1,0xe0,
0x0,0x0,0x0,0x3e,0x0,0x0,0x1,0xfc,0x0,0x78,0x0,0x0,0x0,0x0,0x3,0xc0,0x0,0x0,0x1,0xff,0xc0,0xe0,0x7f,0xe0,0x60,0x7f,0xe0,0x30,0x3,0x0,0x7,0x80,0x0,0x0,0x3,0xf7,0xc7,0xfc,0x7f,0xe3,0xfc,0x7f,0xe1,0xfe,0x1f,0xf0,0xf,0x0,0x0,0x0,0x7,0xc1,0xcf,0xfe,0xff,0xe7,0xfc,0x7f,0xe3,0xff,0x3f,0xf0,0xf,0x0,0x0,0x0,0x7,0xc1,0xcf,0x1f,0xf9,0xe7,0xff,0x78,0x73,0xff,0x3c,0x78,0x1e,0x0,0x0,0x0,0x3,0xff,0xcf,0xf,0xff,0xe7,0xfe,0x7f,0xf3,0xff,0x3f,0xf8,0x78,0x0,0x0,0x0,0x1,0xff,0x8f,0x3f,0x7f,0xe1,0xfe,0x3f,0xe1,0xfe,0x1f,0xf0,0xf0,0x0,0x0,0x0,0x0,0x7e,0xf,0xfe,0x7f,0xe1,0xf8,0xf,0xc0,0xfc,0xf,0xc1,0xf0,0x0,
0x0,0x0,0x0,0x0,0x3,0xf8,0x7f,0xe3,0xc0,0x3,0xef,0xf3,0xfd,0xfb,0xc0,0x0,0x0,0x0,0x0,0x0,0xf,0xe0,0x3f,0xdf,0xf8,0x3,0xff,0xf7,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x3f,0xfc,0x3,0xdf,0xf7,0xff,0x9f,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x0,0x0,0x3f,0xfc,0x3,0xcf,0xf7,0xff,0xbe,0x0,0x0,0x0,0x0,0x0,0x1,0xfc,0x0,0x0,0x3f,0xfc,0x3,0xef,0xf7,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x3f,0xfc,0x3,0xef,0xe3,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0xf,0xc0,0x0,0x0,0x3f,0xfc,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x3f,0xfc,0x0,0x0,0x0,0xf,0x80,0x0,0x0,
0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x7f,0xfe,0x0,0x0,0x0,0x3e,0x0,0x0,0x0,0x0,0x0,0x1,0xf8,0x0,0x60,0x0,0x7f,0xfe,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x0,0x3,0xf0,0x3,0xfc,0x0,0x3f,0xfe,0x0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,0x7,0xe0,0x3,0xfc,0x0,0xc,0x38,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,0x0,0x1f,0x80,0x7,0xfe,0x0,0xc,0x38,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x0,0x0,0x3f,0x1,0xff,0xfc,0x0,0xc,0x38,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x3,0xff,0xe0,0x0,0xc,0x38,0x0,0x1,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x3,0xff,0xe0,0x0,0xc,0x38,0x0,0x3,0xf0,0x0,0x0,0x0,0x0,
0x0,0x1,0xf8,0x3,0xc7,0xe0,0x0,0xc,0x38,0x0,0xf,0xc0,0x0,0x0,0x0,0x0,0x0,0x7,0xe0,0x3,0xff,0xe0,0x0,0xc,0x38,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xc0,0x0,0xff,0xc1,0xf8,0xc,0x38,0x1,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x36,0x1,0xf8,0xc,0x38,0x3,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x3,0xf8,0xc,0x30,0x1f,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x0,0x0,0x0,0x7,0x80,0xc,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x0,0x0,0x3,0xff,0x0,0x0,0x3,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x7,0xfb,0x80,0x0,0xf,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0xf8,0x0,0x0,0x3e,0x73,0x80,0x0,0x7f,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xf8,0x0,0x0,0x7d,0xff,0x0,0x3,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xf8,0x0,0x0,0x1f,0x9e,0x0,0x1f,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x1e,0xc,0x0,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x3c,0x0,0x3,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x0,0x0,0x38,0x0,0x3f,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x0,0x0,0x0,0x3,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xfc,0x0,0x0,0x0,0x7f,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x7,0xfe,0x0,0x0,0x3,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xe0,0x1,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};