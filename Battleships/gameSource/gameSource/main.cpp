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

	gameBoard xGame;
	ship tempShip(3);
	tempShip.up();
	tempShip.up();
	tempShip.right();
	tempShip.right();
	tempShip.right();
	tempShip.rotate();
		
}

