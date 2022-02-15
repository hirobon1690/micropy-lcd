#pragma once
#include <arduino.h>

class LCD{
  public:
    void print(const char *,int line=1);
    void clr();
    void init(int num=0,int contrast=12);
    void write(byte,byte);
    void printf(int, const char*, ...);
    LCD();
};