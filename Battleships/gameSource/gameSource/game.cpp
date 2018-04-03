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
#include "helpFunc.h"




//class game
//{
	//gameBoard player, opponent;
	//
	//public:
	//void startGame();
	//
//};
//
//class gameBoard
//{
	//uint8_t xSize, ySize;
	//cordinate cordShips[17];
	//cordinate hitShips[17];
	//cordinate cordMissil[256];
	//ship ships[5];
	//public:
	//void addShip();
	//bool hit(cordinate);
	//
//};


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
	