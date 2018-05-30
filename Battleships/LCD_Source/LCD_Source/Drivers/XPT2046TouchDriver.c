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


unsigned short int xPos = 0, yPos = 0;

// Touch display initialization. Setup GPIO and set CS, CLK, DIN, DOUT ready for use in 
// other functions.
void touchInit()
{
	DDRE |= 0b00011000; // Sets IRQ and CS as output, DOUT as input
	DDRG |= 0b00100000; // Sets DIN as output
	DDRH |= 0b00001000; // Sets CLK as output
}


void touchMeassure()
{
	cbi(TOUCH_CS_PORT, TOUCH_CS_BIT);
		
	touchWrite(X_CMD);
	sbi(CLK_PORT, CLK_BIT);
	cbi(CLK_PORT, CLK_BIT);
	xPos = touchRead();
	
	touchWrite(Y_CMD);
	sbi(CLK_PORT, CLK_BIT);
	cbi(CLK_PORT, CLK_BIT);
	yPos = touchRead();
		
	xPos = xPos/20;
	yPos = yPos/20;
		
	sbi(TOUCH_CS_PORT, TOUCH_CS_BIT);
}

unsigned short int touchRead()
{
	unsigned short int touchData = 0, doutPin = 0;
	unsigned char count;
	
	for(count = 0; count < 12; count ++)
	{
		touchData <<= 1;
		sbi(CLK_PORT, CLK_BIT);
		cbi(CLK_PORT, CLK_BIT);
		doutPin = rbi(PINE, DOUT_BIT);
		if(doutPin != 0)
			touchData++;
	}
	return touchData;
}

// Input 0x90 for x position, 0xD0 for y position
void touchWrite(unsigned char command)
{
	unsigned char cmd, count;
	
	cmd = command;
	cbi(CLK_PORT, CLK_BIT);
	
	for(count = 0; count < 8; count++)
	{
		// If highest bit in byte isn't 0, set DIN high - else set low
		if(cmd & 0x80)
			sbi(DIN_PORT, DIN_BIT);	
		else
			cbi(DIN_PORT, DIN_BIT);
		
		_NOP();
		_NOP();
		cmd = cmd << 1;
		cbi(CLK_PORT, CLK_BIT);
		sbi(CLK_PORT, CLK_BIT);
	}
}


bool touchReady()
{
	bool dataReady;
	
	// Sets interrupt as input
	TOUCH_IRQ_PORT &= ~(TOUCH_IRQ_BIT);
	
	// Checks whether data is ready on the touch IRQ port
	dataReady = !(rbi(PINE, TOUCH_IRQ_BIT));
	
	// Sets interrupt as output again
	TOUCH_IRQ_PORT |= TOUCH_IRQ_BIT;
	
	return dataReady;
}


unsigned char buttonPressed(unsigned short int x, unsigned short int y)
{
	unsigned char button = 0;
	switch(yPos)
	{
		case Y_RANGE_MIN ... Y_RANGE_MAX:
			switch(xPos)
			{
				case LEFT_RANGE_MIN ... LEFT_RANGE_MAX:
					button = 'L';
					return button;

				case UP_RANGE_MIN ... UP_RANGE_MAX:
					button = 'U';
					return button;
							
				case DOWN_RANGE_MIN ... DOWN_RANGE_MAX:
					button = 'D';
					return button;

				case RIGHT_RANGE_MIN ... RIGHT_RANGE_MAX:
					button = 'R';
					return button;
			}
		default:
			break;	
	}
	
	switch(xPos)
	{
		case X_RANGE_MIN ... X_RANGE_MAX:
			switch(yPos)
			{
				case HIT_RANGE_MIN ... HIT_RANGE_MAX:
					button = 'H';
					return button;
				
				case ROTATE_RANGE_MIN ... ROTATE_RANGE_MAX:
					button = 'T';
					return button;
			}
		default:
			return button;
	}
}
