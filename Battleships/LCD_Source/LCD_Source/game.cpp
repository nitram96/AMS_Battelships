/*
 * game.cpp
 *
 * Created: 22-Mar-18 09:36:04
 *  Author: martin
 */

#define F_CPU 16000000
#include <util/delay.h>
#include "game.h"
#include <stdlib.h>
extern "C"{
#include "Drivers/uart.h"
#include "Drivers/TFTdriver.h"
#include "Drivers/XPT2046TouchDriver.h"
};
#include <string.h>
#include <stdlib.h>


void gameBoard::drawGameboard(uint8_t* ship, uint8_t length)
{
	uint8_t temp;
	FillRectangle(0, 0, MAX_WIDTH, MAX_HEIGHT, 0, 61, 31);
		
	for(uint8_t i = 1; i<=X_LINES; i++)
	drawGameboardYLines(i);
		
	for(uint8_t i = 1; i<=Y_LINES-1; i++)
	drawGameboardXLines(i);
	
	for(uint8_t j = 0; j < YSIZE; j++)
	{
		for(uint8_t i = 0; i < XSIZE; i++)
		{
			if(opponent)
				temp = cpuField[i][j];
			else
				temp = playerField[i][j];
			switch (temp)
			{
				case NO:
					break;
					
				case SHIP:
					drawBitmap(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, shipBMP, 24, 11);
					break;
					
				case MISS:
					FillRectangle(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, X_SQUARE, Y_SQUARE, 31, 63, 31);
					break;
					
				case HIT:
					FillRectangle(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, X_SQUARE, Y_SQUARE, 31, 0, 0);
					break;
				case SHIPANDMISS:
					FillRectangle(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, X_SQUARE, Y_SQUARE, 31, 63, 31);
					drawBitmap(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, shipBMP, 24, 11);
					break;
				case SHIPANDHIT:
					FillRectangle(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, X_SQUARE, Y_SQUARE, 31, 0, 0);
					drawBitmap(i*X_SQUARE, (YSIZE-j-1)*Y_SQUARE, shipBMP, 24, 11);
					break;
			}
		}
	}
	if(started)
	{
		drawBitmap(getXCord(ship[0])*X_SQUARE, (YSIZE-getYCord(ship[0])-1)*Y_SQUARE, cursorBMP, 33, 32);
	}
	else
	{
		for(uint8_t i = 0; i < length; i++)
		{
			drawBitmap(getXCord(ship[i])*X_SQUARE, (YSIZE-getYCord(ship[i])-1)*Y_SQUARE, shipBMP, 24, 11);
		}			
	}

	
	drawBitmap(0, 192, leftBMP, 66, 48);
	drawBitmap(67, 192, upBMP, 66, 48);
	drawBitmap(134, 192, downBMP, 66, 48);
	drawBitmap(201, 192, rightBMP, 66, 48);
	drawBitmap(267,0, hitBMP, 53, 53);
	if(!started)
		drawBitmap(267,53, rotateBMP, 53, 53);
}

void initShip(uint8_t* temp,uint8_t length)
{
	for(int i = 0; i < length; i++)
	{
		temp[i] = makeCord(0,i);
	}
}

bool up(uint8_t* coords, uint8_t length)
{
	uint8_t temp[4];
	for(int i = 0; i < length; i++)
	{
		temp[i] = addCord(coords[i],0,1);
		if (getYCord(temp[i]) >= YSIZE || getYCord(temp[i]) < 0)
		{
			return false;
		}
	}
	for (int i = 0; i < length; i++)
	{
		coords[i] = temp[i];
	}
	return true;
}

bool down(uint8_t* coords, uint8_t length)
{
	uint8_t temp[4];
	for(int i = 0; i < length; i++)
	{
		temp[i] = addCord(coords[i],1,1);
		if (getYCord(temp[i]) >= YSIZE || getYCord(temp[i]) < 0)
		{
			return false;
		}
	}
	for (int i = 0; i < length; i++)
	{
		coords[i] = temp[i];
	}
	return true;
	
}
bool left(uint8_t* coords, uint8_t length)
{
	uint8_t temp[4];
	for(int i = 0; i < length; i++)
	{
		temp[i] = addCord(coords[i],1,0);
		if (getXCord(temp[i]) >= XSIZE || getXCord(temp[i]) < 0)
		{
			return false;
		}
	}
	for (int i = 0; i < length; i++)
	{
		coords[i] = temp[i];
	}
	return true;
	
}
bool right(uint8_t* coords, uint8_t length)
{
	uint8_t temp[4];
	for(int i = 0; i < length; i++)
	{
		temp[i] = addCord(coords[i],0,0);
		if (getXCord(temp[i]) >= XSIZE || getXCord(temp[i]) < 0)
		{
			return false;
		}
	}
	for (int i = 0; i < length; i++)
	{
		coords[i] = temp[i];
	}
	return true;
	
}

bool rotate(uint8_t* coords, uint8_t length)
{
	
	uint8_t temp[4];
	for(int i = 0; i < length; i++)
	{
		temp[i] = makeCord(getYCord(coords[i]),getXCord(coords[i]));
		if (getXCord(temp[i]) >= XSIZE || getXCord(temp[i]) < 0 || getYCord(temp[i]) >= YSIZE || getYCord(temp[i]) < 0)
		{
			return false;
		}
	}
	for (int i = 0; i < length; i++)
	{
		coords[i] = temp[i];
	}
	return true;
}

gameBoard::gameBoard()
{
	
	xSize = XSIZE;
	
	ySize = YSIZE;

	memset(playerField,0,XSIZE*YSIZE);
	memset(cpuField,0,XSIZE*YSIZE);
	numberOfShips = 0;
	missileHits = 0;
	turn = 0;
	
}

void gameBoard::startGame()
{
	uint8_t rng;
	uint8_t temp[4];
	for (int j = 4; j > 1; j--)
	{
		initShip(temp,j);
		do 
		{
			for(int i = 0; i < 20; i++)
			{
				rng = (uint8_t) rand()%5;
				switch (rng)
				{
					case 0:
						right(temp,j);
						break;
					case 1:
						down(temp,j);
						break;
					case 2:
						rotate(temp,j);
						break;
					case 3:
						up(temp,j);
						break;
					case 4:
						left(temp,j);
						break;
				}
			}
		
		}
		while(!placeShip(temp,j,false));
	}
}

bool gameBoard::placeShip(uint8_t *coords,uint8_t length,bool player)
{
	for (int i = 0; i < length; i++)
	{
		if (player)
		{
			if (playerField[getXCord(coords[i])][getYCord(coords[i])] == SHIP)
			{
				return false;
			}
		}
		else
		{
			if (cpuField[getXCord(coords[i])][getYCord(coords[i])] == SHIP)
			{
				return false;
			}
		}		
	}
	for (int i = 0; i < length; i++)
	{
		if (player)
		{
			playerField[getXCord(coords[i])][getYCord(coords[i])] = SHIP;
		}
		else
		{
			cpuField[getXCord(coords[i])][getYCord(coords[i])] = SHIP;
		}
	}
	return true;
}

bool gameBoard::hit(uint8_t missileCord,bool player)
{
	turn++;
	if (player)
	{
		if (cpuField[getXCord(missileCord)][getYCord(missileCord)] == SHIP || cpuField[getXCord(missileCord)][getYCord(missileCord)] == SHIPANDHIT ||cpuField[getXCord(missileCord)][getYCord(missileCord)] == SHIPANDMISS )
		{
			if(playerField[getXCord(missileCord)][getYCord(missileCord)] == SHIP)
				playerField[getXCord(missileCord)][getYCord(missileCord)] = SHIPANDHIT;
			else
				playerField[getXCord(missileCord)][getYCord(missileCord)] = HIT;
				
			missileHits++;
			if (missileHits >= 9)
				won(player);
			
			return true;
		}
		else
		{
			if(playerField[getXCord(missileCord)][getYCord(missileCord)] == SHIP)
				playerField[getXCord(missileCord)][getYCord(missileCord)] = SHIPANDMISS;
			else
				playerField[getXCord(missileCord)][getYCord(missileCord)] = MISS;
			return false;
		}
	}
	else
	{
		uint8_t xRand = (uint8_t) rand()%XSIZE;
		uint8_t yRand = (uint8_t) rand()%YSIZE;
		while(cpuField[xRand][yRand] != NO && cpuField[xRand][yRand] != SHIP)
		{
			xRand = (uint8_t) rand()%XSIZE;
			yRand = (uint8_t) rand()%YSIZE;
		}
		if (playerField[xRand][yRand] == SHIP || playerField[xRand][yRand] == SHIPANDHIT || playerField[xRand][yRand] == SHIPANDMISS)
		{
			if(cpuField[xRand][yRand] == SHIP)
				cpuField[xRand][yRand] = SHIPANDHIT;
			else
				cpuField[xRand][yRand] = HIT;
				
			cpuMissiles++;
			if (cpuMissiles >= 9)
				won(player);
			return true;
		}
		else
		{
			if(cpuField[xRand][yRand] == SHIP)
				cpuField[xRand][yRand] = SHIPANDMISS;
			else
				cpuField[xRand][yRand] = MISS;
			return false;
		}
	}
}

void gameBoard::won(bool player)
{
	if(player)
	{
		FillRectangle(0, 0, MAX_WIDTH, MAX_HEIGHT, 0, 63, 0);
		drawBitmap(100, 110, winBMP, 100, 30);
	}
	else
	{
		FillRectangle(0, 0, MAX_WIDTH, MAX_HEIGHT, 31, 0, 0);
		drawBitmap(100, 110, lossBMP, 100, 30);
	}
	while(1);
}