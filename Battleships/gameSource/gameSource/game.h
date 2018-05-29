/*
 * game.h
 *
 * Created: 22-Mar-18 09:22:49
 *  Author: martin
 */ 
#include <avr/io.h>

#ifndef GAME_H_
#define GAME_H_

// enum to make it easier to read/work with the direction of the ship
enum direction{north,south,east,west};



class ship
{
	// coordinates expressed as a unsigned int 8 bit long, 4 MSB is y coordinate and 4 LSB is x coordinate
	uint8_t startCord, endCord;
	//boolean that expresses whether or not the ship has been sunk
	bool sunk;
	bool checkCord(uint8_t);
	direction dir;
	uint8_t HitPoints;
	public:
	ship(uint8_t,uint8_t);
	ship() : startCord(), endCord(){};
	uint8_t getStartCord();
	uint8_t getEndCord();
	void changeCord(uint8_t,uint8_t);
	bool hit(uint8_t);
};

class gameBoard
{
	
	public:
	uint8_t xSize, ySize;
	uint8_t hitShips[17];
	uint8_t enemyShips[17];
	uint8_t missileHits;
	uint8_t cordMissile[256];
	uint8_t numberOfShips;
	ship ships[5];
	uint8_t turn;
	gameBoard(uint8_t x = 10, uint8_t y = 10);
	void addShip(uint8_t,uint8_t);
	bool hit(uint8_t);
};

class game
{
	
	public:
	game(bool, uint8_t x = 10, uint8_t y = 10);
	int8_t ready(void);
	void shoot(uint8_t coord);
	void waitForMissile(void);
	gameBoard player;
	private:
	bool MOS;
};
// class that we use as ships on the gameboard





#endif /* GAME_H_ */