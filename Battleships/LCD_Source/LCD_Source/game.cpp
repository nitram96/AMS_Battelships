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
	
	//sunk = false;
	//if (compareXCord(startCord,endCord) == 0)
	//{
		//if(compareYCord(startCord,endCord) == 1){
			//dir = south;
			//HitPoints = getYCord(startCord)-getYCord(endCord)+1;
		//}
		//else{
			//dir = north;
			//HitPoints = getYCord(endCord)-getYCord(startCord)+1;
		//}
	//}
	//else
	//{
		//if(compareXCord(startCord,endCord) == 1){
			//dir = west;
			//HitPoints = getXCord(startCord)-getXCord(endCord)+1;
		//}
		//else{
			//dir = east;
			//HitPoints = getXCord(endCord)-getXCord(startCord)+1;
		//}
	//}
	
	
	
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
	return true;
}


bool ship::hit(uint8_t missilCord)
{
	if (checkCord(missilCord)){
		hitPoints -= 1;
		if(hitPoints == 0)
			sunk = true;
		return true;
	}
	else
		return false;
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

void gameBoard::addShip(uint8_t _startCord, uint8_t  _endCord, bool player)
{
	//ships[numberOfShips] = ship(_startCord);
	//
	//switch (ships[numberOfShips].dir)
	//{
	//case north:
	//for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
	//{
	//if(player)
	//playerField[getXCord(_startCord)+i][getYCord(_startCord)] = SHIP;
	//else
	//cpuField[getXCord(_startCord)+i][getYCord(_startCord)] = SHIP;
	//}
	//break;
	//case south:
	//for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
	//{
	//if(player)
	//playerField[getXCord(_startCord)-i][getYCord(_startCord)] = SHIP;
	//else
	//cpuField[getXCord(_startCord)-i][getYCord(_startCord)] = SHIP;
	//}
	//break;
	//case east:
	//for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
	//{
	//if(player)
	//playerField[getXCord(_startCord)][getYCord(_startCord)+i] = SHIP;
	//else
	//cpuField[getXCord(_startCord)][getYCord(_startCord)+i] = SHIP;
	//}
	//break;
	//case west:
	//for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
	//{
	//if(player)
	//playerField[getXCord(_startCord)][getYCord(_startCord)-i] = SHIP;
	//else
	//cpuField[getXCord(_startCord)][getYCord(_startCord)-i] = SHIP;
	//}
	//break;
	//case default:
	//break;
	//}
	//numberOfShips++;
}

bool gameBoard::hit(uint8_t missileCord)
{
	
	turn++;
	return false;
}

void gameBoard::startGame()
{
	uint8_t rng = (uint8_t) rand()%(ySize*xSize);
	
	
}