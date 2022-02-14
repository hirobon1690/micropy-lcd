#include "lcd.h"

#include <Wire.h>
#include <arduino.h>

#define LCD_ADRS 0x7c
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


void LCD::write(byte command, byte t_data) {
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(command);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(10);
}


void LCD::print(char *c, int line) {
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

void LCD::init(int num, int cont) {
  delay(20);
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
  delay(20);
  if (num == 1) {
    this->write(CMD, 0b00111101);
  } else {
    this->write(CMD, 0b00111001);  // Function Set
  }
  delay(20);
  this->write(CMD, 0x14);  // Internal OSC Freq
  delay(20);
  this->write(CMD, 0b01110000 | (cont & 0b001111));  // Contrast Set
  delay(20);
  this->write(CMD, 0b01010100 | (cont >> 4));  // P/I/C Control
  delay(20);
  this->write(CMD, 0x6C);  // Follower Control
  delay(20);
  if (num == 1) {
    this->write(CMD, 0b00111100);
  } else {
    this->write(CMD, 0b00111000);  // Function Set
  }
  delay(20);
  this->write(CMD, 0x01);  // Clear Display
  delay(20);
  this->write(CMD, 0x0C);  // On/Off Control
  delay(20);
  this->write(CMD, 0x40);  // Set CGRAM
  delay(20);
  int i;
  for (i = 0; i <= 64; i++) {
    this->write(DATA, Custom_Char5x8[i]);  // Set CGRAM
    delay(20);
  }
  delay(20);
}