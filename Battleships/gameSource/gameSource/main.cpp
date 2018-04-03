/*
 * gameSource.cpp
 *
 * Created: 22-Mar-18 09:14:08
 * Author : martin
 */ 

#define F_CPU 16000000
 
#include <avr/io.h>
#include <util/delay.h>
#include "game.h"


int main(void)
{
	DDRB |= 0xFF;
	PORTB = 0;
    cordinate cord1;
	cordinate cord2;

	cord1.xCord = 2;
	cord1.yCord = 4;

	cord2.xCord = 2;
	cord2.yCord = 7;

	ship hello(cord1,cord2);

	
	
	while(1)
	{
		
		if(hello.hit(cord1))
			PORTB = 0b10000000;
		else
			PORTB = 0b00000001;
		_delay_ms(500);
		if(cord1.yCord <= 10)
			cord1.yCord += 1;
		else
			cord1.yCord -= 1;
	}
	
}

