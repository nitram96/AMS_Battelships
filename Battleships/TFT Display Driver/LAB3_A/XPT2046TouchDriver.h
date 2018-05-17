/*
 * XPT2046TouchDriver.h
 *
 * Created: 10-05-2018 11:11:06
 *  Author: Rasmus BL
 */ 


#ifndef XPT2046TOUCHDRIVER_H_
#define XPT2046TOUCHDRIVER_H_

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

// Calibration constants
#define CAL_X 0x00378F66UL
#define CAL_Y 0x03C34155UL
#define CAL_S 0x000EF13FUL


// Timing specification definitions (all in µs)
#define tACQ 1.5				// Acquisition time
#define tDS 0.1					// DIN valid prior to DCLK rising
#define tDH 0.05				// DIN hold after DCLK high
#define tDO 0.2					// DCLK falling to DOUT valid
#define tDV 0.2					// CS falling to DOUT enabled
#define tTR 0.2					// CS falling to DOUT disabled
#define tCSS 0.1				// CS falling to first DCLK rising
#define tCSH 0.01				// CS rising to DCLK ingored
#define tCH 0.2					// DCLK high
#define tCL 0.2					// DCLK low
#define tBD 0.2					// DCLK falling to busy rising/falling
#define tBDV 0.2				// CS falling to busy enabled
#define tBTR 0.2				// CS rising to busy disabled

// Should be defined for all drivers (common include file)
#define sbi(b,n) ((b) |= (1<<(n)))          // Set bit number n in byte b
#define cbi(b,n) ((b) &= (~(1<<(n))))       // Clear bit number n in byte b
#define fbi(b,n) ((b) ^= (1<<(n)))          // Flip bit number n in byte b
#define rbi(b,n) ((b) & (1<<(n)))           // Read bit number n in byte b

void touchInit();
void touchMeassure();
unsigned short int touchRead();
void touchWrite(unsigned char command);
int touchReady();
int16_t touchXPos();
int16_t touchYPos();


// Testing functions
void testTouch();

extern int touchDataReady;
extern int16_t xPos, yPos;



#endif /* XPT2046TOUCHDRIVER_H_ */