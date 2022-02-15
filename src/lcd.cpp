#include "lcd.h"

#include <Wire.h>
#include <arduino.h>

#define LCD_ADRS 0x3E
#define ONELINE 1
#define TWOLINES 0
#define DATA 0x40
#define CMD 0x00

const int Custom_Char5x8[] = {
    // 0x00, 通常は使わない
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x01
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x02
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x03
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x04
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x05
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x06
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x07
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000

};

LCD::LCD() {}

void LCD::write(byte command, byte t_data) {
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(command);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
}

void LCD::print(const char* c, int line) {
  this->write(CMD, 0x02);
  if (line == 2) {
    this->write(CMD, 0x40 + 0x80);
  }
  unsigned char i, str;
  for (i = 0; i < strlen(c); i++) {
    str = c[i];
    this->write(DATA, str);
  }
}

void LCD::clr() {
  this->write(CMD, 0x01);
  delay(2);
  this->write(CMD, 0x02);
  delay(2);
}

void LCD::init(int num, int contrast) {
  delay(1);
  if (num == 1) {
    this->write(CMD, 0b00111100);
  } else {
    this->write(CMD, 0b00111000);  // Function Set
  }
  if (num == 1) {
    this->write(CMD, 0b00111101);
  } else {
    this->write(CMD, 0b00111001);  // Function Set
  }
  delay(1);
  if (num == 1) {
    this->write(CMD, 0b00111101);
  } else {
    this->write(CMD, 0b00111001);  // Function Set
  }
  delay(1);
  this->write(CMD, 0x14);  // Internal OSC Freq
  delay(1);
  this->write(CMD, 0b01110000 | (contrast & 0b001111));  // Contrast Set
  delay(1);
  this->write(CMD, 0b01010100 | (contrast >> 4));  // P/I/C Control
  delay(1);
  this->write(CMD, 0x6C);  // Follower Control
  delay(1);
  if (num == 1) {
    this->write(CMD, 0b00111100);
  } else {
    this->write(CMD, 0b00111000);  // Function Set
  }
  delay(1);
  this->write(CMD, 0x01);  // Clear Display
  delay(1);
  this->write(CMD, 0x0C);  // On/Off Control
  delay(1);
  this->write(CMD, 0x40);  // Set CGRAM
  delay(1);
  int i;
  for (i = 0; i < 64; i++) {
    this->write(DATA, Custom_Char5x8[i]);  // Set CGRAM
    delay(1);
  }
  delay(1);
}

void LCD::printf(int line, const char* format, ...) {
  char buf[32];
  va_list ap;
  va_start(ap, format);
  vsprintf(buf, format, ap);
  va_end(ap);
  this->print(buf, line);
}