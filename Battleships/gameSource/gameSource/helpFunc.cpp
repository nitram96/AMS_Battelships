/*
 * CPPFile1.cpp
 *
 * Created: 03-04-2018 23:51:50
 *  Author: Martin
 */ 

#include <avr/io.h>
#include "helpFunc.h"

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

int8_t compareXCord(uint8_t firstCord,uint8_t secondCord)
{
	uint8_t firstX = getXCord(firstCord);
	uint8_t secondX = getXCord(secondCord);
	
	if(firstX == secondX)
	return 0;
	else
	if(firstX > secondX)
	return 1;
	else
	if(firstX < secondX)
	return -1;
	else
	return -10;
}

int8_t compareYCord(uint8_t firstCord,uint8_t secondCord)
{
	uint8_t firstY = getYCord(firstCord);
	uint8_t secondY = getYCord(secondCord);
	
	if(firstY == secondY)
	return 0;
	else
	if(firstY > secondY)
	return 1;
	else
	if(firstY < secondY)
	return -1;
	else
	return -10;
	
}