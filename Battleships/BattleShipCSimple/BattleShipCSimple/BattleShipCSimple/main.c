/*
 * BattleShipCSimple.c
 *
 * Created: 27-Mar-18 16:29:04
 * Author : martin
 */ 

#include <avr/io.h>
#include "gameHelper.h"

int main(void)
{
	unsigned char cordinate;
	
	cordinate = makeCord(12,14);
	
	getXCord(cordinate);
    /* Replace with your application code */
    while (1) 
    {
    }
}

