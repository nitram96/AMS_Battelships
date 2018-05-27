/*
 * radioLib.c
 *
 * Created: 12-Apr-18 09:07:39
 * Author : martin
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "spiLib.h"

int main(void)
{
	
	uint8_t data = 0x50;
	spiMasterInit();
	_delay_ms(1000);
	
	while(1)
	{
	PORT_SPI &= ~(1<<DD_SS);
	data = spiTransmit(++data);
	PORT_SPI |= (1<<DD_SS);
	_delay_ms(1000);
	}
}

