/*
 * game.h
 *
 * Created: 22-Mar-18 09:22:49
 *  Author: martin
 */ 
#include <avr/io.h>

#ifndef GAME_H_
#define GAME_H_

enum direction{north,south,east,west};

struct cordinate
{
	uint8_t xCord;
	uint8_t yCord;
};

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

class ship
{
	cordinate startCord, endCord;
	bool sunk;
	bool checkCord(cordinate);
	direction dir;
	public:
	ship(cordinate,cordinate);
	cordinate getStartCord();
	cordinate getEndCord();
	void changeCord(cordinate,cordinate);
	bool hit(cordinate);

};




#endif /* GAME_H_ */