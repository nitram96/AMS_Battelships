/* 
* ship.h
*
* Created: 30-May-18 14:44:31
* Author: martin
*/


#ifndef __SHIP_H__
#define __SHIP_H__

#include "avr/io.h"
#include "helpFunc.h"

#define HIT 3
#define MISS 2
#define SHIP 1
#define NO 0
#define XSIZE 8
#define YSIZE 6


class ship
{
//variables
public:
protected:
	uint8_t coords[4];
	uint8_t length;
private:

//functions
public:
	ship(uint8_t);
	~ship();
	bool up(void);
	bool down(void);
	bool right(void);
	bool left(void);
	bool rotate(void);
protected:
private:
	ship( const ship &c );
	ship& operator=( const ship &c );

}; //ship

#endif //__SHIP_H__
