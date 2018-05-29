/*
 * XPT2046TouchDriver.h
 *
 * Created: 10-05-2018 11:11:06
 *  Author: Rasmus BL
 */ 


#ifndef XPT2046TOUCHDRIVER_H_
#define XPT2046TOUCHDRIVER_H_
#include "TFTdriver.h"
#include <stdbool.h>

// Touch screen control port definitions
#define CLK_PORT PORTH
#define CLK_BIT 3
#define TOUCH_CS_PORT PORTE
#define TOUCH_CS_BIT 3
#define DIN_PORT PORTG
#define DIN_BIT 5
#define DOUT_PORT PORTE
#define DOUT_BIT 5
#define TOUCH_IRQ_PORT PORTE
#define TOUCH_IRQ_BIT 4			// (=INT4)

// X and Y commands
#define X_CMD 0x90
#define Y_CMD 0xD0

// Buttons
#define Y_RANGE_MIN				0
#define Y_RANGE_MAX				27
#define LEFT_RANGE_MIN			81
#define LEFT_RANGE_MAX			100
#define UP_RANGE_MIN			62
#define UP_RANGE_MAX			80
#define DOWN_RANGE_MIN			43
#define DOWN_RANGE_MAX			61
#define RIGHT_RANGE_MIN			24
#define RIGHT_RANGE_MAX			42

// Should be defined for all drivers (common include file)
#define sbi(b,n) ((b) |= (1<<(n)))          // Set bit number n in byte b
#define cbi(b,n) ((b) &= (~(1<<(n))))       // Clear bit number n in byte b
#define fbi(b,n) ((b) ^= (1<<(n)))          // Flip bit number n in byte b
#define rbi(b,n) ((b) & (1<<(n)))           // Read bit number n in byte b

void touchInit();
void touchMeassure();
unsigned short int touchRead();
void touchWrite(unsigned char command);
bool touchReady();
unsigned char buttonPressed(unsigned short int x, unsigned short int y);

extern bool touchDataReady;
extern unsigned short int xPos, yPos;


#endif /* XPT2046TOUCHDRIVER_H_ */