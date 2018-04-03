/*
 * gameHelper.c
 *
 * Created: 27-Mar-18 16:33:27
 *  Author: martin
 */ 

#include "gameHelper.h"


uint8_t makeCord(uint8_t xCord,uint8_t yCord)
{
	uint8_t temp = 0xFF;
	
	temp = (xCord & 0x0F);
	temp |= (yCord << 4);
	
	return temp;
}

uint8_t getXCord(uint8_t cord)
{
	return (cord & 0x0F);
}

uint8_t getYCord(uint8_t cord)
{
	return (cord >> 4);
}