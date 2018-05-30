/* 
* ship.cpp
*
* Created: 30-May-18 14:44:31
* Author: martin
*/


#include "ship.h"


// default constructor
ship::ship(uint8_t len)
{
	length = len;
	for(int i = 0; i < length; i++)
	{
		coords[i] = makeCord(0,i);
	}
} //ship

// default destructor
ship::~ship()
{
} //~ship

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