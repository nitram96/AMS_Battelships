/*
 * XPT2046TouchDriver.c
 *
 * Created: 10-05-2018 11:12:00
 *  Author: Rasmus BL
 */ 
#include <avr/io.h>
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "XPT2046TouchDriver.h"

long disp_x_size, disp_y_size, default_orientation, touch_x_left, touch_x_right, touch_y_top, touch_y_bottom;
unsigned char prec;

// Touch display initialization. Setup GPIO and set CS, CLK, DIN, DOUT ready for use in 
// other functions.
void touchInit()
{
	touch_x_left			= (CAL_X>>14) & 0x3FFF;
	touch_x_right			= CAL_X & 0x3FFF;
	touch_y_top				= (CAL_Y>>14) & 0x3FFF;
	touch_y_bottom			= CAL_Y & 0x3FFF;
	disp_x_size				= (CAL_S>>12) & 0x0FFF;
	disp_y_size				= CAL_S & 0x0FFF;
	prec					= 10;
	
	DDRE |= 0b00011000; // Sets IRQ and CS as output
	DDRE &= ~(0b00100000); // Sets DOUT as input
	DDRG |= 0b00100000; // Sets DIN as output
	DDRH |= 0b00001000; // Sets CLK as output
	
	// Set CS high (active-low) and all others low
	sbi(TOUCH_CS_PORT, TOUCH_CS_BIT);	
	//cbi(DOUT_PORT, DOUT_BIT);
	//cbi(DIN_PORT, DIN_BIT);
	//cbi(CLK_PORT, CLK_BIT);
	//cbi(TOUCH_IRQ_PORT, TOUCH_IRQ_BIT);
	
	
	// Testing stuff
	sbi(DIN_PORT, DIN_BIT);
	sbi(CLK_PORT, CLK_BIT);
	sbi(TOUCH_IRQ_PORT, TOUCH_IRQ_BIT);
}

int16_t xPos = 0, yPos = 0;

void touchMeassure()
{
	unsigned long x = 0, xTemp = 0, minx=99999, maxx=0;
	unsigned long y = 0, yTemp = 0, miny=99999, maxy=0;
	int8_t i;
	int touchCount = 0;
	

	// Clears interrupt and sets as input
	cbi(TOUCH_CS_PORT, TOUCH_CS_BIT);
	DDRE &= ~(0b00010000);
	
	for(i = 0; i < prec; i++)
	{
		// Get x-position
		if (!rbi(TOUCH_IRQ_PORT, TOUCH_IRQ_BIT))
		{
			touchWrite(0x90);
			
			// Pulse clock
			sbi(CLK_PORT, CLK_BIT);
			cbi(CLK_PORT, CLK_BIT);
			
			xTemp = touchRead();		
		
			// Get y-position
			if (!rbi(TOUCH_IRQ_PORT, TOUCH_IRQ_BIT))
			{
				touchWrite(0xD0);
				
				// Pulse clock
				sbi(CLK_PORT, CLK_BIT);
				cbi(CLK_PORT, CLK_BIT);
				
				yTemp = touchRead();
				
				// Assign xTemp and yTemp to global touch data variables
				if((xTemp > 0) && (xTemp < 4096) && (yTemp > 0) && (yTemp < 4096))
				{
					x += xTemp;
					y += yTemp;
					
					if (prec > 5)
					{
						if (xTemp < minx)
						minx = xTemp;
						if (xTemp > maxx)
						maxx = xTemp;
						if (yTemp<miny)
						miny = yTemp;
						if (yTemp > maxy)
						maxy = yTemp;
					}
					touchCount++;
				}
			}
		}
	}
	
	// Sets interrupt as output again
	DDRE |= 0b00010000;
	
	if (prec>5)
	{
		x = x-(minx+maxx);
		y = y-(miny+maxy);
		touchCount -= 2;
	}
	
	sbi(TOUCH_CS_PORT, TOUCH_CS_BIT);
	
	if((touchCount == (prec-2)) || (touchCount == 1))
	{
		xPos = y/touchCount;
		yPos = x/touchCount;
	}
	else
	{
		xPos = -1;
		yPos = -1;
	}
}

unsigned short int touchRead()
{
	unsigned short int touchData = 0;
	unsigned char count;
	
	for(count = 0; count < 12; count ++)
	{
		touchData <<= 1;
		sbi(CLK_PORT, CLK_BIT);
		cbi(CLK_PORT, CLK_BIT);
		if(rbi(DOUT_PORT, DOUT_BIT))
			touchData++;
	}
	return touchData;
}

void touchWrite(unsigned char command)
{
	unsigned char byte, count;
	
	byte = command;
	
	for(count = 0; count < 8; count++)
	{
		// If highest bit in byte isn't 0, set DIN high - else set low
		if(byte & 0x80)
			sbi(DIN_PORT, DIN_BIT);	
		else
			cbi(DIN_PORT, DIN_BIT);
	}
	byte = byte << 1;
	cbi(CLK_PORT, CLK_BIT);
	sbi(CLK_PORT, CLK_BIT);
}

int touchReady()
{
	int dataReady = 0;
	
	// Sets interrupt as input
	DDRE &= ~(0b00010000);
	
	// Checks whether data is ready on the touch IRQ port
	dataReady = !(rbi(TOUCH_IRQ_PORT, TOUCH_IRQ_BIT));
	
	// Sets interrupt as output again
	DDRE |= 0b00010000;
	
	return dataReady;
}

int16_t touchXPos()
{
	long x_;
	
	if((xPos == -1) || (yPos == -1))
		return -1;
		
	x_ = ((xPos - touch_x_left) * (disp_x_size)) / (touch_x_right - touch_x_left);
	
	if (x_<0)
		x_ = 0;
	if (x_ > disp_x_size)
		x_ = disp_x_size;
	
	return x_;
}

int16_t touchYPos()
{
	long y_;
	
	if((xPos == -1) || (yPos == -1))
		return -1;
	y_ = ((yPos - touch_y_top) * (disp_y_size)) / (touch_y_bottom - touch_y_top);
	
	if (y_ < 0)
		y_ = 0;
	
	if (y_ > disp_y_size)
		y_ = disp_y_size;
		
	return y_;
}


void testTouch()
{
	unsigned long tx=0;
	unsigned long ty=0;

	cbi(TOUCH_CS_PORT, TOUCH_CS_BIT);

	touchWrite(0x90);
	sbi(CLK_PORT, CLK_BIT);
	cbi(CLK_PORT, CLK_BIT);
	tx=touchRead();

	touchWrite(0xD0);
	sbi(CLK_PORT, CLK_BIT);
	cbi(CLK_PORT, CLK_BIT);
	ty=touchRead();

	sbi(TOUCH_CS_PORT, TOUCH_CS_BIT);

	xPos=ty;
	yPos=tx;
}