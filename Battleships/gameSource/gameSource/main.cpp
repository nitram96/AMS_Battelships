/*
 * gameSource.cpp
 *
 * Created: 22-Mar-18 09:14:08
 * Author : martin
 */ 

#define F_CPU 16000000
 
#include <avr/io.h>
#include "game.h"


int main(void)
{
	gameBoard player(10,10);

	player.addShip(0x25,0x28);
	player.hit(0x26);	
		
}

