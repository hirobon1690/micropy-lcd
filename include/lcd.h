#pragma once
#include <arduino.h>

class LCD{
  public:
    void print(char *,int line=1);
    void clr();
    void init(int num=0,int cont=38);
    void write(byte,byte);
};