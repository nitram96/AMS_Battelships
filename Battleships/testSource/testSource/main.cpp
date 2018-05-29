/*
 * testSource.cpp
 *
 * Created: 29-05-2018 16:58:34
 * Author : Martin
 */ 
#define F_CPU 16000000
#include "Drivers/uart.h"
#include <util/delay.h>
#include <avr/io.h>



int main(void)
{
	InitUART(9600,8);
    /* Replace with your application code */
    while (1) 
    {
		SendChar(0x40);
		_delay_ms(1000);
    }
}

