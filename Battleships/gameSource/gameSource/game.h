/*
 * game.h
 *
 * Created: 22-Mar-18 09:22:49
 *  Author: martin
 */ 
#include <avr/io.h>

#ifndef GAME_H_
#define GAME_H_

#define HIT 3
#define MISS 2
#define SHIP 1
#define NO 0
#define XSIZE 8
#define YSIZE 6
// enum to make it easier to read/work with the direction of the ship
enum direction{north,south,east,west};



class ship
{
	// coordinates expressed as a unsigned int 8 bit long, 4 MSB is y coordinate and 4 LSB is x coordinate
	uint8_t coords[4];
	//boolean that expresses whether or not the ship has been sunk
	bool sunk;
	bool checkCord(uint8_t);
	uint8_t length;
	uint8_t hitPoints;
	public:
	ship(uint8_t);
	bool up(void);
	bool down(void);
	bool right(void);
	bool left(void);
	bool rotate(void);
	bool hit(uint8_t);
};

class gameBoard
{
	
	public:
	uint8_t missileHits;
	uint8_t numberOfShips;
	uint8_t turn;
	gameBoard();
	void addShip(uint8_t,uint8_t,bool);
	bool hit(uint8_t);
	void startGame(void);
	private:
	uint8_t playerField[XSIZE][YSIZE];
	uint8_t cpuField[XSIZE][YSIZE];
	uint8_t xSize, ySize;
};
// class that we use as ships on the gameboard





#endif /* GAME_H_ */