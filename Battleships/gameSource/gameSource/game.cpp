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
extern "C"{
#include "Drivers/uart.h"
#include "Drivers/spiLib.h"
};
#include <string.h>
#include <stdlib.h>


gameBoard::gameBoard(uint8_t _xSize, uint8_t _ySize)
{
	if (_xSize >> 15)
		xSize = 15;
	else
		xSize = _xSize;
	
	if (_ySize >> 15)
		ySize = 15;
	else
		ySize = _ySize;

		memset(cordMissile,0,256);
		memset(hitShips,0,17);
		memset(enemyShips,0,17);
		numberOfShips = 0;
		missileHits = 0;
		turn = 0;
	

	
	
	
}

void gameBoard::addShip(uint8_t _startCord, uint8_t  _endCord)
{
	ships[numberOfShips++] = ship(_startCord,_endCord) ;
}

bool gameBoard::hit(uint8_t missileCord)
{
	cordMissile[turn-1] = missileCord;
	for(int i = 0; i < numberOfShips; i++)
	{
		if(ships[i].hit(missileCord))
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

game::game(bool master,uint8_t x, uint8_t y)
{
	MOS = master;
	InitUART(9600,8);
	if(master)
	{
		//player = gameBoard(x,y);
		spiMasterInit();
		SendChar(READY);
		while(ReadChar() != ACK)
		{
			_delay_ms(10);
			SendChar(READY);
		}
		SendChar(x);
		while(ReadChar() != x)
		{
			_delay_ms(10);
			SendChar(x);
		}
		SendChar(y);
		while(ReadChar() != y)
		{
			_delay_ms(10);
			SendChar(y);
		}
		_delay_ms(10);
	}
	else
	{
		spiSlaveInit();
		while(ReadChar() != READY)
		{
			_delay_ms(10);
			SendChar(NACK);
		}
		SendChar(ACK);
		uint8_t xSize = ReadChar();
		SendChar(xSize);
		uint8_t ySize = ReadChar();
		SendChar(ySize);
		player = gameBoard(xSize,ySize);
		SendChar('D');
		
	}
	
}

int8_t game::ready()
{
	if(player.numberOfShips != 5)
	return -1;
	if(MOS)
	{
		
		while(spiTransmit(READY) != ACK)
		{
			_delay_ms(1000);
		}
		return 1;
	}
	else
	{
		while(spiReceive() != READY)
		{
			_delay_ms(1000);
		}
		spiSend(ACK);
		return 1;
		
	}
}

void game::shoot(uint8_t coord)
{
	if (MOS)
	{
		DDR_SPI &= ~(1<<DD_SS);
		while(spiTransmit(MISSILE) != ACK)
		{
			_delay_ms(1);
		}
		uint8_t hit = spiTransmit(coord);
		DDR_SPI |= (1<<DD_SS);
		if(hit == ACK)
		{
			player.cordMissile[player.turn++] = coord;
			player.enemyShips[player.missileHits++] = coord;
		}
		if(hit == NACK)
		player.cordMissile[player.turn++] = coord;
	}
	else
	{
		while(spiTransmit(MISSILE) != ACK)
		{
			_delay_ms(1);
		}
		uint8_t hit = spiTransmit(coord);
		while(hit != ACK && hit != NACK)
		{
			hit = spiTransmit(coord);
		}
		if(hit == ACK)
		{
			player.cordMissile[player.turn++] = coord;
			player.enemyShips[player.missileHits++] = coord;
		}
		if(hit == NACK)
		player.cordMissile[player.turn++] = coord;
	}
}

void game::waitForMissile()
{
	if (MOS)
	{
		DDR_SPI &= ~(1<<DD_SS);
		while(spiTransmit(ACK) != MISSILE)
		{
			_delay_ms(1);
		}
		if (player.hit(spiReceive()))
		{
			spiSend(ACK);
		}
		else
		{
			spiSend(NACK);
		}
		DDR_SPI |= (1<<DD_SS);
	}
	else
	{
		while(spiTransmit(ACK) != MISSILE)
		{
			_delay_ms(1);
		}
		if (player.hit(spiReceive()))
		{
			spiSend(ACK);
		}
		else
		{
			spiSend(NACK);
		}
		
	}
}