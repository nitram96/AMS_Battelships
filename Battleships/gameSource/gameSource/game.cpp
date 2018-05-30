/*
 * game.cpp
 *
 * Created: 22-Mar-18 09:36:04
 *  Author: martin
 */

#define F_CPU 16000000
#include <util/delay.h>
#include "game.h"
#include "helpFunc.h"
#include <stdlib.h>
extern "C"{
#include "Drivers/uart.h"
#include "Drivers/TFTdriver.h"
#include "Drivers/XPT2046TouchDriver.h"
};
#include <string.h>
#include <stdlib.h>





ship::ship(uint8_t len)
{
	length = len;
	for(int i = 0; i < len; i++)
	{
		coords[i] = makeCord(0,i);	
	}
	hitPoints = len;	
	
}

bool ship::up()
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

bool ship::down()
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
bool ship::left()
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
bool ship::right()
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

bool ship::rotate()
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


bool ship::checkCord(uint8_t _cord)
{
	for(int i = 0; i < length; i++)
	{
		if (_cord == coords[i])
		{
			return true;
		}
	}
	return false;
	
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

bool gameBoard::placeShip(ship _ship,bool player)
{
	for (int i = 0; i < _ship.length; i++)
	{
		if (player)
		{
			if (playerField[getXCord(_ship.coords[i])][getYCord(_ship.coords[i])] == SHIP)
			{
				return false;
			}
		}
		else
		{
			if (cpuField[getXCord(_ship.coords[i])][getYCord(_ship.coords[i])] == SHIP)
			{
				return false;
			}
		}		
	}
	for (int i = 0; i < _ship.length; i++)
	{
		if (player)
		{
			playerField[getXCord(_ship.coords[i])][getYCord(_ship.coords[i])] = SHIP;
		}
		else
		{
			cpuField[getXCord(_ship.coords[i])][getYCord(_ship.coords[i])] = SHIP;
		}
	}
	
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

void gameBoard::startGame()
{
	uint8_t rng = (uint8_t) rand()%(YSIZE*XSIZE);
	
	ship Tempship(4);
	for (int j = 4; j > 1; j--)
	{
		Tempship = ship(j);
		for(int i = 0; i < 20; i++)
		{
			
			switch (rand()%5)
			{
				case 0:
				Tempship.right();
				break;
				case 1:
				Tempship.down();
				break;
				case 2:
				Tempship.rotate();
				break;
				case 3:
				Tempship.up();
				break;
				case 4:
				Tempship.left();
				break;
			}
		}
		placeShip(Tempship,false);
	}
}