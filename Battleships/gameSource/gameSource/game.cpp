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
//class ship
//{
	//
	//cordinate startCord, endCord;
	//bool sunk;
	//bool checkCord(cordinate);
	//direction dir;
	//public:
	//ship(cordinate,cordinate);
	//cordinate getStartCord();
	//cordinate getEndCord();
	//void changeCord(cordinate,cordinate);
	//bool hit(cordinate);
//
//};

ship::ship(cordinate _startCord, cordinate _endCord)
{
	startCord = _startCord;
	endCord = _endCord;
	sunk = false;
	if (startCord.xCord == endCord.xCord)
	{
		if(startCord.yCord >> endCord.yCord)
			dir = south;
		else
			dir = north; 
	}
	else
	{
		if(startCord.xCord >> endCord.xCord)
			dir = west;
		else
			dir = east;
	}
	
}
cordinate ship::getStartCord()
{
	return startCord;
}

cordinate ship::getEndCord()
{
	return endCord;
}

void ship::changeCord(cordinate _startCord,cordinate _endCord)
{
	startCord = _startCord;
	endCord = _endCord;
}

bool ship::hit(cordinate missilCord)
{
	if (checkCord(missilCord))
		return true;
	else
		return false;
}

bool ship::checkCord(cordinate _cords)
{
	uint8_t dxCurrent,dyCurrent,dx,dy, crossProd;
	dxCurrent = _cords.xCord - startCord.xCord;
	dyCurrent = _cords.yCord - startCord.yCord;
	
	dx = endCord.xCord - startCord.xCord;
	dy = endCord.yCord - startCord.yCord;
	
	crossProd = (dxCurrent*dy)-(dyCurrent*dx);
	
	if(crossProd != 0)
		return false;
	else
	{
	switch(dir)
	{
		case north:
			if(_cords.yCord >> startCord.yCord && _cords.yCord << endCord.yCord)
				return true;
			else
				return false;
		case south:
			if(_cords.yCord << startCord.yCord && _cords.yCord >> endCord.yCord)
				return true;
			else
				return false;
		case east:
			if(_cords.xCord >> startCord.xCord && _cords.xCord << endCord.xCord)
				return true;
			else
				return false;
		case west:
			if(_cords.xCord << startCord.xCord && _cords.xCord >> endCord.xCord)
				return true;
			else
				return false;
		default:
			return false;
	}
}		
}