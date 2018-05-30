/************************************************************
  File name: "TFTdriver.c"

  Driver for "ITDB02 320 x 240 TFT display module, Version 2"
  mounted at "ITDB02 Arduino Mega2560 Shield".
  Display controller = ILI 9341.
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connections:
  DB15-DB8:   PORT A
  DB7-DB0:    PORT C

  RESETx:     PORT G, bit 0
  CSx:        PORT G, bit 1
  WRx:        PORT G, bit 2
  RS (=D/Cx): PORT D, bit 7

  Henning Hargaard, February 14, 2018
************************************************************/  
#include <avr/pgmspace.h>
#include "bitmaps.h"

#define ALL_PIXELS_OFF_CMD		0x22
#define ALL_PIXELS_ON_CMD		0x23
#define DISPLAY_OFF_CMD			0x28
#define DISPLAY_ON_CMD			0x29
#define SLEEP_OUT_CMD			0x11
#define MEMORY_WRITE_CMD		0x2C
#define MEMORY_ACCESS_CMD		0x36
#define PIXEl_FORMAT_CMD		0x3A
#define COLUMN_ADDRESS_CMD		0x2A
#define PAGE_ADDRESS_CMD		0x2B

#define MAX_HEIGHT				240
#define MAX_WIDTH				320

#define X_SQUARE				33
#define Y_SQUARE				32
#define X_GAMEBOARD				267
#define Y_GAMEBOARD				192
#define X_LINES					8
#define Y_LINES					6

/* TFT Display Driver Methods */
void DisplayInit();
void AllPixelsOff();
void AllPixelsOn();
void DisplayOff();
void DisplayOn();
void SleepOut();
void MemoryAccessControl(unsigned char parameter);
void InterfacePixelFormat(unsigned char parameter);
void WritePixel(unsigned char Red, unsigned char Blue, unsigned char Green);
void writeColor(uint16_t color);
void SetColumnAddress(unsigned int Start, unsigned int End);
void SetPageAddress(unsigned int Start, unsigned int End);
void MemoryWrite();
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, 
                   unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue);
void drawBitmap(int x, int y, const uint16_t bitmap[], int16_t w, int16_t h);
void writeBitmap(unsigned int x, unsigned int y, uint16_t color);

void drawLine(unsigned int StartX, unsigned int StartY, unsigned int EndX, 
			  unsigned int EndY, unsigned char Red, unsigned char Green, unsigned char Blue);



/* Battleships Game Methods */
//void drawGameboard();
void drawGameboardYLines(unsigned int i);
void drawGameboardXLines(unsigned int i);
// More?


