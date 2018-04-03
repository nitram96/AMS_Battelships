/*
 * ship.h
 *
 * Created: 25-Mar-18 16:23:23
 *  Author: martin
 */ 


#include <avr/io.h>

typedef enum{north,south,east,west} direction;

typedef struct
{
	uint8_t xCord;
	uint8_t yCord;
} cordinate;


typedef struct
{
	cordinate startCord, endCord;
	uint8_t sunk;
	direction dir;
} ship;

ship makeShip(cordinate,cordinate);
cordinate getStartCord(ship);
cordinate getEndCord(ship);
ship changeCord(ship,cordinate,cordinate);
uint8_t hit(ship,cordinate);

