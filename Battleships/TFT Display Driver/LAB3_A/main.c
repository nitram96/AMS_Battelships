/*
 * LAB3_A.c
 *
 * Created: 14-02-2018 21:31:04
 * Author : Rasmus BL
 */

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"


int main(void)
{
    DisplayInit();
	

    while (1) 
    {
		drawGameboard();
    }
}

/*
int main(void)
{
	// Initialize the display
	DisplayInit();
	// All pixels white (background)
	FillRectangle(0,0,320,240,31,63,31);
	// Draw red parts of danish flag
	FillRectangle(0,140,100,100,31,0,0);
	FillRectangle(0,0,100,100,31,0,0);
	FillRectangle(140,0,180,100,31,0,0);
	FillRectangle(140,140,180,100,31,0,0);
	
	while(1)
	{
		DisplayOn();
		_delay_ms(1000);
		DisplayOff();
		_delay_ms(1000);
	}
}*/

