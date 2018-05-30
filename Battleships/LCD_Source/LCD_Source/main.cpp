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
extern "C"{
#include "Drivers/uart.h"
};


int main(void)
{
	//InitUART(9600, 8);
	
	// Initialize display and touchchip
	DisplayInit();
	touchInit();
	
	gameBoard xGame;
	uint8_t ship[4];
	uint8_t size = 4;
	initShip(ship,4);
	
	
	bool touchDataReady;
	unsigned char button;
	
	// Draw Gameboard and buttons
	xGame.drawGameboard(ship,4);
	//drawBitmap(201, 192, ship, 24, 11);
	
	
	//SendChar(12);
	//SendChar(7);
	
	while (1)
	{
		touchDataReady = touchReady();
		if(touchDataReady)
		{
			touchMeassure();
			button = buttonPressed(xPos, yPos);
			if(!xGame.started)
			{
				switch (button)
				{
					case 'L':
						left(ship,size);
						xGame.drawGameboard(ship, size);
						FillRectangle(267,192,53,53,31,0,0);
						break;
					
					case 'U':
						up(ship,size);
						xGame.drawGameboard(ship, size);
						FillRectangle(267,192,53,53,0,63,0);
						break;
					
					case 'D':
						down(ship,size);
						xGame.drawGameboard(ship, size);
						FillRectangle(267,192,53,53,0,0,31);
						break;
					
					case 'R':
						right(ship,size);
						xGame.drawGameboard(ship, size);
						FillRectangle(267,192,53,53,31,63,31);
						break;
					
					case 'H':
						if(!xGame.placeShip(ship, size, true))
							break;
						xGame.drawGameboard();
						size--;
						if(size < 2)
						{
							xGame.startGame();
							xGame.started = true;
						}
						break;
					
					case 'T':
						rotate(ship, size);
						xGame.drawGameboard(ship, size);
						FillRectangle(267,192,53,53,31,63,0);
						break;
					
					default:
						break;
				}
			
			}
			else
			{
				switch (button)
				{
					case 'L':
						left(ship,1);
						xGame.drawGameboard(ship, 1);
						FillRectangle(267,192,53,53,31,0,0);
						break;
					
					case 'U':
						up(ship,1);
						xGame.drawGameboard(ship, 1);
						FillRectangle(267,192,53,53,0,63,0);
						break;
					
					case 'D':
						down(ship,1);
						xGame.drawGameboard(ship, 1);
						FillRectangle(267,192,53,53,0,0,31);
						break;
					
					case 'R':
						right(ship,1);
						xGame.drawGameboard(ship, 1);
						FillRectangle(267,192,53,53,31,63,31);
						break;
					
					case 'H':
						xGame.hit(ship[0],true);
						xGame.hit(ship[0],false);
						xGame.drawGameboard();
						break;
					
					case 'T':
					FillRectangle(267,192,53,53,31,63,0);
						xGame.opponent = true;
						xGame.drawGameboard();
						xGame.opponent = false;
						break;
					
					default:
						break;
				}
			}
		}
	}
}






/*	while (1)
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
	}*/

