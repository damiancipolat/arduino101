#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED width, pixel size
#define SCREEN_HEIGHT 64 // OLED height, pixel size
 
#define OLED_RESET    -1 // Resetpin # (or -1 if you are connecting the aduino to the resetpin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// 'f_0', 50x50px
const unsigned char myBitmap_1 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x3f, 0xff, 0x1f, 
  0xff, 0xc0, 0xff, 0xf3, 0xcf, 0xfc, 0xf3, 0xff, 0xc0, 0xff, 0xef, 0xf3, 0xf3, 0xfd, 0xff, 0xc0, 
  0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0x7c, 
  0x1e, 0xde, 0x0f, 0xbf, 0xc0, 0xff, 0x7e, 0x0f, 0x3f, 0x87, 0xbf, 0xc0, 0xff, 0xff, 0x07, 0x3f, 
  0x83, 0xff, 0xc0, 0xfe, 0xff, 0x07, 0x3f, 0x81, 0xdf, 0xc0, 0xfe, 0xfe, 0x07, 0xf7, 0x81, 0xdf, 
  0xc0, 0xfe, 0xe0, 0x03, 0xf0, 0x01, 0xdf, 0xc0, 0xfe, 0xe0, 0x03, 0xf0, 0x01, 0xdf, 0xc0, 0xfe, 
  0xe0, 0x03, 0xf0, 0x01, 0xdf, 0xc0, 0xfe, 0xe0, 0x03, 0xf0, 0x01, 0xdf, 0xc0, 0xfe, 0xe0, 0x07, 
  0xf0, 0x01, 0xdf, 0xc0, 0xfe, 0xe0, 0x67, 0x38, 0x39, 0xdf, 0xc0, 0xff, 0xf0, 0x67, 0x38, 0x13, 
  0xff, 0xc0, 0xff, 0x70, 0x0f, 0x3c, 0x03, 0xbf, 0xc0, 0xff, 0x7c, 0x1e, 0xde, 0x0f, 0xbf, 0xc0, 
  0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xef, 
  0xf3, 0xf3, 0xfd, 0xff, 0xc0, 0xff, 0xf3, 0xef, 0xfd, 0xf3, 0xff, 0xc0, 0xff, 0xfc, 0x3f, 0xff, 
  0x0f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

// 'f_1', 50x50px
const unsigned char myBitmap_2 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x3f, 0xff, 0x1f, 
  0xff, 0xc0, 0xff, 0xf3, 0xcf, 0xfc, 0xf3, 0xff, 0xc0, 0xff, 0xef, 0xf3, 0xf3, 0xfd, 0xff, 0xc0, 
  0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0x7f, 
  0xfe, 0xdf, 0xff, 0xbf, 0xc0, 0xff, 0x7f, 0xff, 0x3f, 0xff, 0xbf, 0xc0, 0xff, 0xff, 0xff, 0x3f, 
  0xff, 0xff, 0xc0, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 
  0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 
  0xff, 0xff, 0x7f, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xfe, 0x1f, 0xff, 0xdf, 0xc0, 0xfe, 0xe7, 0xf3, 
  0xf3, 0xf9, 0xdf, 0xc0, 0xfe, 0xe0, 0x67, 0x38, 0x39, 0xdf, 0xc0, 0xff, 0xf0, 0x67, 0x38, 0x13, 
  0xff, 0xc0, 0xff, 0x70, 0x0f, 0x3c, 0x03, 0xbf, 0xc0, 0xff, 0x7c, 0x1e, 0xde, 0x0f, 0xbf, 0xc0, 
  0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xef, 
  0xf3, 0xf3, 0xfd, 0xff, 0xc0, 0xff, 0xf3, 0xef, 0xfd, 0xf3, 0xff, 0xc0, 0xff, 0xfc, 0x3f, 0xff, 
  0x0f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

// 'f_2', 50x50px
const unsigned char myBitmap_3 [] PROGMEM = {
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x3f, 0xff, 0x1f, 
  0xff, 0xc0, 0xff, 0xf3, 0xcf, 0xfc, 0xf3, 0xff, 0xc0, 0xff, 0xef, 0xf3, 0xf3, 0xfd, 0xff, 0xc0, 
  0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0x7f, 
  0xfe, 0xdf, 0xff, 0xbf, 0xc0, 0xff, 0x7f, 0xff, 0x3f, 0xff, 0xbf, 0xc0, 0xff, 0xff, 0xff, 0x3f, 
  0xff, 0xff, 0xc0, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 
  0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 
  0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 
  0xff, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xdf, 0xc0, 0xff, 0xff, 0xff, 0x3f, 0xff, 
  0xff, 0xc0, 0xff, 0x7f, 0xff, 0x3f, 0xff, 0xbf, 0xc0, 0xff, 0x7f, 0xfe, 0xdf, 0xff, 0xbf, 0xc0, 
  0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xef, 
  0xf3, 0xf3, 0xfd, 0xff, 0xc0, 0xff, 0xf3, 0xef, 0xfd, 0xf3, 0xff, 0xc0, 0xff, 0xfc, 0x3f, 0xff, 
  0x0f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

// 'f_3', 50x50px
const unsigned char myBitmap_4 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x3f, 0xff, 0x1f, 
  0xff, 0xc0, 0xff, 0xf3, 0xcf, 0xfc, 0xf3, 0xff, 0xc0, 0xff, 0xef, 0xf3, 0xf3, 0xfd, 0xff, 0xc0, 
  0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0x7f, 
  0xfe, 0xdf, 0xff, 0xbf, 0xc0, 0xff, 0x7f, 0xff, 0x3f, 0xff, 0xbf, 0xc0, 0xff, 0xff, 0xff, 0x3f, 
  0xff, 0xff, 0xc0, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 
  0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xc0, 0xfe, 
  0xff, 0xff, 0x7f, 0xff, 0xdf, 0xc0, 0xfe, 0xff, 0xfe, 0x1f, 0xff, 0xdf, 0xc0, 0xfe, 0xe7, 0xf3, 
  0xf3, 0xf9, 0xdf, 0xc0, 0xfe, 0xe0, 0x67, 0x38, 0x39, 0xdf, 0xc0, 0xff, 0xf0, 0x67, 0x38, 0x13, 
  0xff, 0xc0, 0xff, 0x70, 0x0f, 0x3c, 0x03, 0xbf, 0xc0, 0xff, 0x7c, 0x1e, 0xde, 0x0f, 0xbf, 0xc0, 
  0xff, 0xbf, 0xfd, 0xef, 0xff, 0x7f, 0xc0, 0xff, 0xdf, 0xfd, 0xef, 0xfe, 0xff, 0xc0, 0xff, 0xef, 
  0xf3, 0xf3, 0xfd, 0xff, 0xc0, 0xff, 0xf3, 0xef, 0xfd, 0xf3, 0xff, 0xc0, 0xff, 0xfc, 0x3f, 0xff, 
  0x0f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

// 'a', 50x50px
const unsigned char myBitmap [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xf8, 0x07, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 
  0xc0, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0xff, 
  0xf0, 0x07, 0xf0, 0x07, 0xff, 0xc0, 0xff, 0xe0, 0x1f, 0xfc, 0x03, 0xff, 0xc0, 0xff, 0xc0, 0x7f, 
  0xff, 0x01, 0xff, 0xc0, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff, 0xc0, 0xff, 0x81, 0xff, 0xff, 0xc0, 
  0xff, 0xc0, 0xff, 0x03, 0xff, 0xff, 0xe0, 0x7f, 0xc0, 0xff, 0x07, 0xff, 0xff, 0xf0, 0x7f, 0xc0, 
  0xfe, 0x07, 0xc7, 0xf1, 0xf0, 0x3f, 0xc0, 0xfe, 0x0f, 0x83, 0xe0, 0xf8, 0x3f, 0xc0, 0xfe, 0x0f, 
  0x83, 0xe0, 0x78, 0x3f, 0xc0, 0xfc, 0x0f, 0x83, 0xe0, 0x7c, 0x1f, 0xc0, 0xfc, 0x1f, 0xc3, 0xf0, 
  0x7c, 0x1f, 0xc0, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 0xc0, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 
  0xc0, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 0xc0, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 0xc0, 0xfc, 
  0x1f, 0xef, 0xff, 0xfc, 0x1f, 0xc0, 0xfc, 0x0f, 0xc7, 0xfb, 0xfc, 0x1f, 0xc0, 0xfe, 0x0f, 0xc3, 
  0xf1, 0xf8, 0x3f, 0xc0, 0xfe, 0x0f, 0xe0, 0x01, 0xf8, 0x3f, 0xc0, 0xfe, 0x07, 0xf0, 0x01, 0xf0, 
  0x3f, 0xc0, 0xff, 0x07, 0xf8, 0x01, 0xf0, 0x3f, 0xc0, 0xff, 0x03, 0xff, 0xff, 0xe0, 0x7f, 0xc0, 
  0xff, 0x81, 0xff, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff, 0xc0, 0xff, 0xc0, 
  0x7f, 0xff, 0x01, 0xff, 0xc0, 0xff, 0xe0, 0x1f, 0xfe, 0x03, 0xff, 0xc0, 0xff, 0xe0, 0x07, 0xf0, 
  0x03, 0xff, 0xc0, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 
  0xc0, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0xf0, 0x07, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.invertDisplay(true);
}

void loop()
{

  //1
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap_1, 50, 50, WHITE);
  display.display();
  delay(100);

  //2
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap_2, 50, 50, WHITE);
  display.display();
  delay(100);

  //3
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap_3, 50, 50, WHITE);
  display.display();
  delay(100);

  //4
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap_4, 50, 50, WHITE);
  display.display();
  delay(100);      
}