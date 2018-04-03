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

//class game
//{
	//gameBoard player, opponent;
	//
	//public:
	//void startGame();
	//
//};
//
//class gameBoard
//{
	//uint8_t xSize, ySize;
	//cordinate cordShips[17];
	//cordinate hitShips[17];
	//cordinate cordMissil[256];
	//ship ships[5];
	//public:
	//void addShip();
	//bool hit(cordinate);
	//
//};

// class that we use as ships on the gameboard
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
	uint8_t getStartCord();
	uint8_t getEndCord();
	void changeCord(uint8_t,uint8_t);
	bool hit(uint8_t);

};




#endif /* GAME_H_ */