/*
 * game.cpp
 *
 * Created: 22-Mar-18 09:36:04
 *  Author: martin
 */ 

/*
 * game.h
 *
 * Created: 22-Mar-18 09:22:49
 *  Author: martin
 */ 
#include "game.h"
#include "spiLib.h"
#include "helpFunc.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdlib.h>


void* operator new(size_t objsize) {
	return malloc(objsize);
}

void operator delete(void* obj) {
	free(obj);
}

void* operator new[](unsigned int x);
void operator delete[](void *);


game::startGame(bool master,uint8_t x, uint8_t y)
{
	
	if(master)
	{
		player.gameBoard(x,y,true);
		opponent.gameBoard(x,y,false);
		spiMasterInit();
		DDR_SPI &= ~(1<<DD_SS);
		while(spiTransmit(READY) != ACK)
		{
			_delay_ms(1000);	
		}
		while(spiTransmit(x) != ACK)
		{
			_delay_ms(1);
		}
		while(spiTransmit(y) != ACK)
		{
			_delay_ms(1);
		}
		
		DDR_SPI &= ~(1<<DD_SS);
		player.addShip();
		
		DDR_SPI &= ~(1<<DD_SS);
		while(spiTransmit(READY) != ACK)
		{
			_delay_ms(1000);
		}
		DDR_SPI &= ~(1<<DD_SS);
		
		
		opponent.hit(cord);
		hit = spiTransmit(cord);
		if(hit == ACK)
		
			
		
	}
	else
	{
		spiSlaveInit();
		while(spiReceive() != READY)
		{
			_delay_ms(1000);
		}
		spiSend(ACK);
		uint8_t xSize = spiTransmit(ACK);
		uint8_t ySize = spiTransmit(ACK);
		player.gameBoard(xSize,ySize,true);
		opponent.gameBoard(xSize,ySize,false);
		player.addShip();
		while(spiReceive() != READY)
		{
			_delay_ms(1000);
		}
		spiSend(ACK);
		
		
	}
	
	if(player.numberOfShips == 5)
	{
		if(opponent.numberOfShips == 5)
		{
			
		}
	}
}



gameBoard::gameBoard(uint8_t _xSize, uint8_t _ySize, bool master)
{
	if (_xSize >> 15)
		xSize = 15;
	else
		xSize = _xSize;
	
	if (_ySize >> 15)
		ySize = 15;
	else
		ySize = _ySize;

	MOS = master
	if (master)
	{
		memset(cordMissile,0,256);
		memset(hitShips,0,17);
		numberOfShips = 0;
		missileHits = 0;
		turn = 1;
	}
	else
	{
		memset(cordMissile,0,256);
		memset(hitShips,0,17);
		missileHits = 0;
		turn = 1;
	}
	

	
	
	
}

void gameBoard::addShip(uint8_t _startCord, uint8_t  _endCord)
{
	ships[numberOfShips++] = new ship(_startCord,_endCord) ;
}

bool gameBoard::hit(uint8_t missileCord)
{
	cordMissile[turn-1] = missileCord;
	for(int i = 0; i < numberOfShips; i++)
	{
		if(ships[i]->hit(missileCord))
		{
			hitShips[missileHits] = missileCord;
			missileHits++;
			turn++;	
			return true;
		}
	}
	turn++;
	return false;
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
	