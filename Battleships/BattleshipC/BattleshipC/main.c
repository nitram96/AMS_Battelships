/*
 * BattleshipC.c
 *
 * Created: 25-Mar-18 16:22:47
 * Author : martin
 */ 

#include "ship.h"
#include <avr/io.h>

int main(void)
{
	cordinate hej;
	hej.xCord = 2;
	hej.yCord = 4;
	cordinate hej2;
	hej2.xCord = 2;
	hej2.yCord = 7;
	ship ship1;
	ship1 = makeShip(hej,hej2);
    while (1) 
    {
    }
}

