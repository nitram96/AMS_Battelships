/*
 * ship.c
 *
 * Created: 25-Mar-18 16:23:39
 *  Author: martin
 */ 

#include "ship.h"

 ship makeShip(cordinate _startCord,cordinate _endCord)
{
	ship Ship;
	Ship.startCord = _startCord;
	Ship.endCord = _endCord;
	if (_startCord.xCord == _endCord.xCord)
	{
		if(_startCord.yCord >> _endCord.yCord)
		Ship.dir = south;
		else
		Ship.dir = north;
	}
	else
	{
		if(_startCord.xCord >> _endCord.xCord)
		Ship.dir = west;
		else
		Ship.dir = east;
	}
	Ship.sunk = 0;

	return Ship;
}

