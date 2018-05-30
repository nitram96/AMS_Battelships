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
#include "Drivers/spiLib.h"
};
#include <string.h>
#include <stdlib.h>


gameBoard::gameBoard()
{
		xSize = SIZE;
	
		ySize = SIZE;

		memset(playerField,0,SIZE*SIZE);
		memset(cpuField,0,SIZE*SIZE);
		numberOfShips = 0;
		missileHits = 0;
		turn = 0;
	
}

void gameBoard::addShip(uint8_t _startCord, uint8_t  _endCord, bool player)
{
	ships[numberOfShips] = ship(_startCord,_endCord);
	
	switch (ships[numberOfShips].dir)
	{
	case : north
		for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
		{
			if(player)
				playerField[getXCord(_startCord)+i][getYCord(_startCord)] = SHIP;
			else
				cpuField[getXCord(_startCord)+i][getYCord(_startCord)] = SHIP;
		}
		break;
	case : south
		for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
		{
			if(player)
				playerField[getXCord(_startCord)-i][getYCord(_startCord)] = SHIP;
			else
				cpuField[getXCord(_startCord)-i][getYCord(_startCord)] = SHIP;
		}
		break;
	case : east
		for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
		{
			if(player)
				playerField[getXCord(_startCord)][getYCord(_startCord)+i] = SHIP;
			else
				cpuField[getXCord(_startCord)][getYCord(_startCord)+i] = SHIP;
		}
		break;
	case : west
		for (int i = 0; i < ships[numberOfShips].HitPoints; i++)
		{
			if(player)
				playerField[getXCord(_startCord)][getYCord(_startCord)-i] = SHIP;
			else
				cpuField[getXCord(_startCord)][getYCord(_startCord)-i] = SHIP;
		}
		break;
	}
	numberOfShips++;
}

bool gameBoard::hit(uint8_t missileCord)
{
	
	for(int i = 0; i < numberOfShips; i++)
	{
		if(ships[i].hit(missileCord))
		{
			playerField[getXCord(missileCord)][getYCord(missileCord)] = HIT;
			missileHits++;
			turn++;	
			return true;
		}
	}
	turn++;
	return false;
}

void gameBoard::startGame()
{
	uint8_t rng = (uint8_t) rand()%(ySize*xSize);
	
	for (uint8_t i = 0; i < gameBoard.xSize; i++)
	{
		for (uint8_t j = 0; j < gameBoard.ySize; j++)
		{
			for (uint8_t h = 0; h <= numberOfShips; h++)
			{
				if(playerField[i][j] != SHIP)
					playerField[i][j] = ships[h].checkCord(makeCord(i,j)) ? SHIP : NO;
			}
		}
	}
}


ship::ship(uint8_t _startCord, uint8_t _endCord)
{
	startCord = _startCord;
	endCord = _endCord;
	sunk = false;
	if (compareXCord(startCord,endCord) == 0)
	{
		if(compareYCord(startCord,endCord) == 1){
			dir = south;
			HitPoints = getYCord(startCord)-getYCord(endCord)+1;
		}
		else{
			dir = north;
			HitPoints = getYCord(endCord)-getYCord(startCord)+1;
		}
	}
	else
	{
		if(compareXCord(startCord,endCord) == 1){
			dir = west;
			HitPoints = getXCord(startCord)-getXCord(endCord)+1;
		}
		else{
			dir = east;
			HitPoints = getXCord(endCord)-getXCord(startCord)+1;
		}
	}
	
	
	
}
uint8_t ship::getStartCord()
{
	return startCord;
}

uint8_t ship::getEndCord()
{
	return endCord;
}

void ship::changeCord(uint8_t _startCord,uint8_t _endCord)
{
	startCord = _startCord;
	endCord = _endCord;
}

bool ship::hit(uint8_t missilCord)
{
	if (checkCord(missilCord)){
		HitPoints -= 1;
		if(HitPoints == 0)
			sunk = true;
		return true;
	}
	else
		return false;
}

bool ship::checkCord(uint8_t _cord)
{
	switch(dir)
	{
		case north:
			if(compareXCord(startCord,_cord) == 0)
			{
				if(compareYCord(_cord,startCord) == -1)
					return false;
				else
				if(compareYCord(_cord,endCord) == 1)
					return false;
				else
					return true;
			}
			else
				return false;
		
		case south:
			if(compareXCord(startCord,_cord) == 0)
			{
				if(compareYCord(_cord,startCord) == 1)
					return false;
				else
				if(compareYCord(_cord,endCord) == -1)
					return false;
				else
					return true;
			}
			else
				return false;
		case east:
			if(compareYCord(startCord,_cord) == 0)
			{
				if(compareXCord(_cord,startCord) == -1)
					return false;
				else
				if(compareXCord(_cord,endCord) == 1)
					return false;
				else
					return true;
			}
			else
				return false;
		case west:
			if(compareYCord(startCord,_cord) == 0)
			{
				if(compareXCord(_cord,startCord) == 1)
					return false;
				else
				if(compareXCord(_cord,endCord) == -1)
					return false;
				else
					return true;
			}
			else
				return false;
		default:
			return false;
	}
	
}	