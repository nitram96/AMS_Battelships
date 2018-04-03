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
	bool temp;
	char hej[4];
	ship ship1(0x25,0x28);
	
	temp = ship1.hit(0x26);
	
	if(temp){
		hej[0] = 'Y';
		hej[1] = 'E';
		hej[2] = 'S';
	}
	else{
		hej[0] = 'N';
		hej[1] = 'O';
	}
	while(1)
	{
		
	}		
		
}

