/*
 * gameSource.cpp
 *
 * Created: 22-Mar-18 09:14:08
 * Author : martin
 */ 

#define F_CPU 16000000
 
#include <avr/io.h>
#include "game.h"
extern "C"{
#include "Drivers/uart.h"
};


int main(void)
{
	
	game xGame(false,10,10);
	
	char string[] = {"Connected"};
	SendString(string);

	xGame.player.addShip(0x25,0x28);
	xGame.player.addShip(0x25,0x28);
	xGame.player.addShip(0x25,0x28);
	xGame.player.addShip(0x25,0x28);
	xGame.player.addShip(0x25,0x28);
	
	xGame.ready();
	xGame.waitForMissile();
	xGame.shoot(0x0F);
		
}

