/*
 * game.h
 *
 * Created: 22-Mar-18 09:22:49
 *  Author: martin
 */ 


#ifndef GAME_H_
#define GAME_H_
#include <avr/io.h>
#include "helpFunc.h"
extern "C"{
#include "Drivers/TFTdriver.h"
#include "Drivers/XPT2046TouchDriver.h"
};
#define SHIPANDHIT 5
#define SHIPANDMISS 4
#define HIT 3
#define MISS 2
#define SHIP 1
#define NO 0
#define XSIZE 8
#define YSIZE 6

// enum to make it easier to read/work with the direction of the ship

//void startGame(void);

class gameBoard
{
	public:
	uint8_t missileHits;
	uint8_t cpuMissiles;
	uint8_t numberOfShips;
	uint8_t turn;
	bool started = false;
	bool opponent = false;
	gameBoard();
	void startGame(void);
	bool placeShip(uint8_t*, uint8_t, bool);
	bool hit(uint8_t,bool);
	void drawGameboard(uint8_t* = 0, uint8_t length = 0);
	private:
	void won(bool player);
	uint8_t playerField[XSIZE][YSIZE];
	uint8_t cpuField[XSIZE][YSIZE];
	uint8_t xSize, ySize;
	
};
void initShip(uint8_t* temp,uint8_t length);
bool up(uint8_t*, uint8_t len);
bool down(uint8_t*, uint8_t len);
bool right(uint8_t*, uint8_t len);
bool left(uint8_t*, uint8_t len);
bool rotate(uint8_t*, uint8_t len);
// class that we use as ships on the gameboard





#endif /* GAME_H_ */