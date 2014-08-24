#include <Wire.h>
#include <SeeedOLED.h>
#include <avr/pgmspace.h>

//const int buttonPin = 7;     // the number of the pushbutton pin
const int a = 1;
const int b = 0;
const int c = 11;
const int d = 12;
const int e = 13;
const int f = 3;
const int g = 5;
const int p = 6;
const int pins[] = {a, b, c, d, e, f, g, p};
//const int pins[] = {0,1,3,5,6,11,12,13};      // the number port of the board pin
//const int pinsLED[] = {6,7,9,10,5,4,2,1};//the pins in LED(bafgpcde)764219a5
//display code lib
const int nd[][7] = {
  //0
  {a, b, c, d, e, f},
  //1
  {b, c},
  //2
  {a, b, d, e, g},
  //3
  {a, b, c, d, g},
  //4
  {b, c, f, g},
  //5
  {a, f, g, c, d},
  //6
  {a, f, g, c, d, e},
  //7
  {a, b, c},
  //8
  {a, b, c, d, e, f, g},
  //9
  {a, b, c, d, f, g},
  //p dot
  {p}
};
const int ndsize[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 1};

static const unsigned char fontDatas[11][32] PROGMEM = {
  //超
  {
    0x40, 0x48, 0x48, 0xFF, 0x48, 0x48, 0x82, 0x42,
    0x3E, 0x02, 0x22, 0x42, 0x3F, 0x02, 0x00, 0x00,
    0x40, 0x3F, 0x10, 0x1F, 0x22, 0x42, 0x40, 0x5F,
    0x51, 0x51, 0x51, 0x51, 0x5F, 0x60, 0x20, 0x00
  }
  ,
  //声
  {
    0x04, 0x14, 0xD4, 0x54, 0x54, 0x54, 0x54, 0xDF,
    0x54, 0x54, 0x54, 0x54, 0xF4, 0x56, 0x04, 0x00,
    0x80, 0x60, 0x1F, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x02, 0x02, 0x02, 0x02, 0x07, 0x00, 0x00, 0x00
  }
  ,
  //波
  {
    0x20, 0x42, 0x04, 0x0C, 0x80, 0xF8, 0x88, 0x88,
    0x88, 0xFF, 0x88, 0x88, 0xA8, 0x18, 0x00, 0x00,
    0x04, 0x04, 0xFE, 0x41, 0x30, 0x8F, 0x40, 0x22,
    0x14, 0x08, 0x14, 0x22, 0x41, 0xC0, 0x40, 0x00
  }
  ,
  //距
  {
    0x00, 0x3E, 0x22, 0xE2, 0x22, 0x3E, 0x00, 0xFE,
    0x22, 0x22, 0x22, 0x22, 0xF3, 0x22, 0x00, 0x00,
    0x20, 0x7F, 0x20, 0x3F, 0x12, 0x12, 0x00, 0x7F,
    0x42, 0x42, 0x42, 0x42, 0x47, 0x60, 0x40, 0x00
  }
  ,
  //离
  {
    0x04, 0x04, 0x04, 0xF4, 0x04, 0x8C, 0x55, 0x26,
    0x54, 0x8C, 0x04, 0xF4, 0x04, 0x06, 0x04, 0x00,
    0x00, 0xFC, 0x04, 0x05, 0x25, 0x35, 0x2D, 0x27,
    0x25, 0x35, 0x25, 0x45, 0x84, 0x7E, 0x04, 0x00
  }
  ,
  //探
  {
    0x10, 0x10, 0x10, 0xFF, 0x90, 0x58, 0x06, 0x22,
    0x12, 0x0A, 0xC2, 0x0A, 0x12, 0xAA, 0x06, 0x00,
    0x02, 0x42, 0x81, 0x7F, 0x00, 0x00, 0x21, 0x11,
    0x09, 0x05, 0xFF, 0x05, 0x09, 0x31, 0x11, 0x00
  }
  ,
  //测
  {
    0x10, 0x22, 0x6C, 0x00, 0x80, 0xFC, 0x04, 0xF4,
    0x04, 0xFE, 0x04, 0xF8, 0x00, 0xFE, 0x00, 0x00,
    0x04, 0x04, 0xFE, 0x01, 0x40, 0x27, 0x10, 0x0F,
    0x10, 0x67, 0x00, 0x47, 0x80, 0x7F, 0x00, 0x00
  }
  ,
  //仪
  {
    0x80, 0x40, 0x20, 0xF8, 0x07, 0x00, 0x38, 0xC0,
    0x02, 0x04, 0x0C, 0x80, 0x60, 0x1C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0x80, 0x40, 0x20, 0x10,
    0x0B, 0x04, 0x0A, 0x11, 0x60, 0xC0, 0x40, 0x00
  },
  //wen
  {
    0x10, 0x22, 0x64, 0x0C, 0x80, 0x00, 0xFE, 0x92,
    0x92, 0x92, 0x92, 0x92, 0xFF, 0x02, 0x00, 0x00,
    0x04, 0x04, 0xFE, 0x01, 0x40, 0x7E, 0x42, 0x42,
    0x7E, 0x42, 0x7E, 0x42, 0x42, 0x7E, 0x40, 0x00
  },
  //shi
  {
    0x10, 0x22, 0x64, 0x0C, 0x80, 0xFE, 0x92, 0x92,
    0x92, 0x92, 0x92, 0x92, 0xFF, 0x02, 0x00, 0x00,
    0x04, 0x04, 0xFE, 0x41, 0x44, 0x48, 0x50, 0x7F,
    0x40, 0x40, 0x7F, 0x50, 0x48, 0x64, 0x40, 0x00
  },
  //du
  {
    0x00, 0x00, 0xFC, 0x24, 0x24, 0x24, 0xFC, 0xA5,
    0xA6, 0xA4, 0xFC, 0x24, 0x34, 0x26, 0x04, 0x00,
    0x40, 0x20, 0x9F, 0x80, 0x42, 0x42, 0x26, 0x2A,
    0x12, 0x2A, 0x26, 0x42, 0x40, 0xC0, 0x40, 0x00
  }
};

//0-9 :
static const unsigned char fontDigital[11][32] PROGMEM = {
  //0
  {
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0x0C, 0x04,
    0x04, 0x04, 0x0C, 0xF8, 0xF0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x30, 0x20,
    0x20, 0x20, 0x30, 0x1F, 0x0F, 0x00, 0x00, 0x00
  }
  ,
  //1
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xF8,
    0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3F,
    0x3F, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //2
  {
    0x00, 0x00, 0x00, 0x00, 0x30, 0x38, 0x0C, 0x04,
    0x04, 0x0C, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x38, 0x2C,
    0x26, 0x23, 0x21, 0x38, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //3
  {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x0C, 0x84,
    0x84, 0xCC, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x30, 0x20,
    0x20, 0x31, 0x1F, 0x0E, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //4
  {
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x70, 0x18,
    0xFC, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x07, 0x05, 0x04, 0x24,
    0x3F, 0x3F, 0x24, 0x04, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //5
  {
    0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xC4, 0x44,
    0x44, 0xC4, 0x84, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x30, 0x20,
    0x20, 0x30, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //6
  {
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0x8C, 0x44,
    0x44, 0xCC, 0x98, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x30, 0x20,
    0x20, 0x30, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //7
  {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x0C, 0x0C, 0x0C,
    0xCC, 0xEC, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x3F,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //8
  {
    0x00, 0x00, 0x00, 0x00, 0x30, 0x78, 0xCC, 0x84,
    0x84, 0xCC, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x1F, 0x31, 0x20,
    0x20, 0x31, 0x1F, 0x0E, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //9
  {
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0x0C, 0x04,
    0x04, 0x0C, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x19, 0x33, 0x22,
    0x22, 0x33, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00
  }
  ,
  //:
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};

void setup() {
  //init display led
  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display
  DDRB |= 0x21;
  PORTB |= 0x21;
  //init display
  SeeedOled.init();                       //initialze SEEED OLED display
  SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
  SeeedOled.deactivateScroll();           // deactivete Scroll (might be activated by previous test case)
  SeeedOled.setNormalDisplay();           // Non-inverted Display
  //SeeedOled.setHorizontalMode();                // Page mode to start with

  //print title
  SeeedOled.setBitmapRect(0, 1, 0, 127);
  //p0
  for (int i = 0 ; i < 8; i++) {
    SeeedOled.drawBitmap(fontDatas[i], 16);
  }
  //p1
  for (int i = 0 ; i < 8; i++) {
    SeeedOled.drawBitmap(fontDatas[i] + 16, 16);
  }
  //wendu
  SeeedOled.setBitmapRect(3, 4, 16, 47);
  SeeedOled.drawBitmap(fontDatas[8], 16);
  SeeedOled.drawBitmap(fontDatas[10], 16);
  SeeedOled.drawBitmap(fontDatas[8] + 16, 16);
  SeeedOled.drawBitmap(fontDatas[10] + 16, 16);

  //shidu
  SeeedOled.setBitmapRect(6, 7, 16, 47);
  SeeedOled.drawBitmap(fontDatas[9], 16);
  SeeedOled.drawBitmap(fontDatas[10], 16);
  SeeedOled.drawBitmap(fontDatas[9] + 16, 16);
  SeeedOled.drawBitmap(fontDatas[10] + 16, 16);
  // put your setup code here, to run once:
  for (int i = 0 ; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
  }
  black();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int n = 0; n <= 10 ; n++) {
    showdig(n);
    delay(1000);
//    black();
//    delay(500);
  }
}

void showdig(int num) {
  if (num < 0 || num > 10) return;
  black();
  for (int i = 0; i < ndsize[num]; i++) {
    digitalWrite(nd[num][i], HIGH);
  }
}

void black() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pins[i], LOW);
  }
}