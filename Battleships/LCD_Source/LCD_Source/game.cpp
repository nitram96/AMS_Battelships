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
	
	uint8_t temp[4];
	for (int j = 4; j > 1; j--)
	{
		initShip(temp,j);
		do 
		{
			for(int i = 0; i < 20; i++)
			{
				
				switch (rand()%5)
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
		if (playerField[getXCord(missileCord)][getYCord(missileCord)] == SHIP)
		{
			playerField[getXCord(missileCord)][getYCord(missileCord)] = HIT;
			return true;
		}
		else
		{
			playerField[getXCord(missileCord)][getYCord(missileCord)] = MISS;
			return false;
		}
	}
	else
	{
		if (cpuField[getXCord(missileCord)][getYCord(missileCord)] == SHIP)
		{
			cpuField[getXCord(missileCord)][getYCord(missileCord)] = HIT;
			return true;
		}
		else
		{
			cpuField[getXCord(missileCord)][getYCord(missileCord)] = MISS;
			return false;
		}
	}
}

