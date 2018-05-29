/*
 * TFT.c
 *
 * Created: 24-02-2017 
 * Author : Henning Hargaard
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"

int main(void)
{
  DisplayInit();
  
  AllPixelsOff();
  _delay_ms(1000);
  AllPixelsOn();
  _delay_ms(1000);
  FillRectangle(0,0,320,240,31,63,31);
  FillRectangle(0,140,100,100,31,0,0);
  FillRectangle(0,0,100,100,31,0,0);
  FillRectangle(140,0,320-140,100,31,0,0);
  FillRectangle(140,140,320-140,100,31,0,0);      
  while(1)
  {
    DisplayOn();
    _delay_ms(1000);
    DisplayOff();
    _delay_ms(1000);		
  } 
}

