/*
 * gameSource.cpp
 *
 * Created: 22-Mar-18 09:14:08
 * Author : martin
 */ 

#define F_CPU 16000000
 
#include <avr/io.h>
#include "game.h"
extern "C"{
#include "Drivers/uart.h"
#include "Drivers/TFTdriver.h"
#include "Drivers/XPT2046TouchDriver.h"
};


int main(void)
{
	gameBoard xGame;
	
	bool touchDataReady;
	unsigned char button;
	
	InitUART(9600, 8);
	
	// Initialize display and touchchip
	DisplayInit();
	touchInit();
	
	// Draw Gameboard and buttons
	drawGameboard();
	drawBitmap(0, 192, leftBMP, 66, 48);
	drawBitmap(67, 192, upBMP, 66, 48);
	drawBitmap(134, 192, downBMP, 66, 48);
	drawBitmap(201, 192, rightBMP, 66, 48);
	drawBitmap(267,0, hitBMP, 53, 53);
	drawBitmap(267,53, rotateBMP, 53, 53);
	//drawBitmap(201, 192, ship, 24, 11);
	
	SendChar(12);
	SendChar(7);
	
	while (1)
	{
		touchDataReady = touchReady();
		if(touchDataReady)
		{
			touchMeassure();
			
			SendString("xPos: ");
			SendInteger(xPos);
			SendString(" yPos: ");
			SendInteger(yPos);
			SendString("; ");
			SendString("\n");
			SendString("\r");
			SendString("\n");
			SendString("\r");
			
			button = buttonPressed(xPos, yPos);
			SendChar(button);
			SendString("\n");
			SendString("\r");
		}
	}
}

