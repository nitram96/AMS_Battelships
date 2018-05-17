/*
 * radioLib.c
 *
 * Created: 12-Apr-18 09:07:39
 * Author : martin
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include "spiLib.h"

int main(void)
{
	spiMasterInit();
	
	while(1)
	{
	spiTransmit(0x40);
	_delay_ms(1000);
	}
}

