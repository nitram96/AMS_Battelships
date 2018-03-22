/*
 * gameSource.cpp
 *
 * Created: 22-Mar-18 09:14:08
 * Author : martin
 */ 

#include <avr/io.h>
#include "game.h"


int main(void)
{
    cordinate cord1;
	cordinate cord2;
	bool test;

	cord1.xCord = 2;
	cord1.yCord = 4;

	cord2.xCord = 2;
	cord2.yCord = 7;

	ship hello(cord1,cord2);

	test = hello.hit(cord1);

	while(1)
	{

	}
	
}

