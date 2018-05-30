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
#include <avr/io.h>
#include <avr/cpufunc.h>
#define  F_CPU 16000000
#include <math.h>
#include <util/delay.h>
#include "TFTdriver.h"

// TFT Display data port definitions
#define DATA_PORT_HIGH PORTA
#define DATA_PORT_LOW  PORTC

// TFT Display control port definitions
#define WR_PORT PORTG
#define WR_BIT 2
#define DC_PORT PORTD
#define DC_BIT  7				// "DC" signal is at the shield called RS
#define CS_PORT PORTG
#define CS_BIT  1
#define RST_PORT PORTG
#define RST_BIT 0


// Define read byte and word for PROGMEM
#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif


// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

// ILI 9341 data sheet, page 238
void WriteCommand(unsigned int command)
{
	DATA_PORT_LOW = command;
	
	DC_PORT &= ~(1<<DC_BIT);
	CS_PORT &= ~(1<<CS_BIT);
	WR_PORT &= ~(1<<WR_BIT);
	
	_NOP();
	WR_PORT |= (1<<WR_BIT);
	CS_PORT |= (1<<CS_BIT);
	WR_PORT &= ~(1<<WR_BIT);
	_NOP();
}

// ILI 9341 data sheet, page 238
void WriteData(unsigned int data)
{		
	DATA_PORT_HIGH = data >> 8;
	DATA_PORT_LOW = data & 0xFF;
	
	DC_PORT |= (1<<DC_BIT);
	CS_PORT &= ~(1<<CS_BIT);
	WR_PORT &= ~(1<<WR_BIT);
	
	_NOP();
	WR_PORT |= (1<<WR_BIT);
	CS_PORT |= (1<<CS_BIT);
	WR_PORT &= ~(1<<WR_BIT);
	_NOP();
		
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRG |= 0b00000111;
	DDRD |= 0b10000000;
	
	_delay_ms(1);
	
	// Performs HW reset
	RST_PORT |= (1<<RST_BIT);
	_delay_ms(300);
	RST_PORT &= ~(1<<RST_BIT);
	_delay_ms(500);
	RST_PORT |= (1<<RST_BIT);
	_delay_ms(120);


	InterfacePixelFormat(0x55);
	MemoryAccessControl(0x08);
	
	_delay_ms(10);
	
	SleepOut();
	
	_delay_ms(100);
	
	DisplayOn();
	
}

void AllPixelsOff()
{
	WriteCommand(ALL_PIXELS_OFF_CMD);
}

void AllPixelsOn()
{
	WriteCommand(ALL_PIXELS_ON_CMD);
}

void DisplayOff()
{
	WriteCommand(DISPLAY_OFF_CMD);
}

void DisplayOn()
{
	WriteCommand(DISPLAY_ON_CMD);
}

void SleepOut()
{
	WriteCommand(SLEEP_OUT_CMD);
}

void MemoryAccessControl(unsigned char parameter)
{
	WriteCommand(MEMORY_ACCESS_CMD);
	WriteData(parameter);
}

void InterfacePixelFormat(unsigned char parameter)
{
	WriteCommand(PIXEl_FORMAT_CMD);
	WriteData(parameter);
}

void MemoryWrite()
{
	WriteCommand(MEMORY_WRITE_CMD);
}

// Red 0-31, Green 0-63, Blue 0-31
void WritePixel(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	uint16_t frame = 0;
	
	frame |= (Red & 0x1F)<<11;
	frame |= (Green & 0x3F)<<5;
	frame |= (Blue & 0x1F);
			
	WriteData(frame);
}

void writeColor(uint16_t color)
{
	uint16_t frame = 0;
	
	frame |= (color & 0xF800);
	frame |= (color & 0x7E0);
	frame |= (color & 0x1F);
	
	WriteData(frame);
}

// Set Column Address (0-239), Start > End
void SetColumnAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(COLUMN_ADDRESS_CMD);
	
	WriteData(Start >> 8);
	WriteData(Start & 0xFF);
	
	WriteData(End >> 8);
	WriteData(End & 0xFF);
}

// Set Page Address (0-339), Start > End
void SetPageAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(PAGE_ADDRESS_CMD);
	
	WriteData(Start >> 8);
	WriteData(Start & 0xFF);
		
	WriteData(End >> 8);
	WriteData(End & 0xFF);
}

// Fills rectangle with specified colour
// (0,0) = Upper left corner. X horizontal (0-239) , Y vertical (0-339).
// Height (1-240) vertical. Width (1-320) horizontal.
// R-G-B = 5-6-5 bits.
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue)
{
	if(StartX < 0 && StartX > 240 && StartY < 0 && StartY > 320)
		return;
		
	SetPageAddress(StartX,StartX+Width);
	SetColumnAddress(StartY,StartY+Height);

	uint16_t w = MAX_WIDTH-StartX, h = MAX_HEIGHT-StartY;
	
	MemoryWrite();
		
	for(StartY = h; StartY>0; StartY--)
	{
 		for(StartX = w; StartX>0; StartX--)
		{
			WritePixel(Red,Green,Blue);
		}
	}
}

void drawLine(unsigned int StartX, unsigned int StartY, unsigned int EndX, unsigned int EndY, unsigned char Red, unsigned char Green, unsigned char Blue)
{
	int x = EndX-StartX;
	int y = EndY-StartY;
	int dx = abs(x), sx = StartX<EndX ? 1 : -1;
	int dy = -abs(y), sy = StartY<EndY ? 1 : -1;
	int err = dx+dy, e2;			// error value e_xy
	for (;;)
	{
		SetPageAddress(StartX,StartX);
		SetColumnAddress(StartY,StartY);
		MemoryWrite();
		WritePixel(Red, Green, Blue);
		e2 = 2*err;
		if (e2 >= dy)			// e_xy+e_x > 0
		{
			if (StartX == EndX)
			break;
			err += dy;
			StartX += sx;
		}
		if (e2 <= dx)	 		// e_xy+e_y < 0
		{
			if (StartY == EndY) break;
			err += dx;
			StartY += sy;
		}
	}
}


// Draws a 16-bit bitmap saved in PROGMEM using pgm_read_word and writeBitmap()
void drawBitmap(int x, int y, const uint16_t bitmap[], int16_t w, int16_t h)
{
	uint16_t word = 0;

	for(int16_t j=0; j<h; j++, y++)
	{
		for(int16_t i=0; i<w; i++)
		{
			word   = pgm_read_word(&bitmap[j * w + i]);
			if(word != 0xFFFF) writeBitmap(x+i, y, word);
		}
	}
}


// Sets location of the bitmap in PROGMEM and writes each pixel with their respective 16-bit color
void writeBitmap(unsigned int x, unsigned int y, uint16_t color)
{
	if((x < 0) || (x >= MAX_WIDTH) || (y < 0) || (y >= MAX_HEIGHT)) return;
	SetPageAddress(x,x+1);
	SetColumnAddress(y,y+1);
	MemoryWrite();
	writeColor(color);
}



/* BATTLESHIPS Methods */

/*void drawGameboard()
{
	unsigned int i;
	FillRectangle(0, 0, MAX_WIDTH, MAX_HEIGHT, 0, 61, 31);
	
	for(i = 1; i<=X_LINES; i++)
		drawGameboardYLines(i);
		
	for(i = 1; i<=Y_LINES-1; i++)
		drawGameboardXLines(i);
}*/

void drawGameboardYLines(unsigned int i)
{
	SetPageAddress(X_SQUARE*i,X_GAMEBOARD);
	SetColumnAddress(0,Y_GAMEBOARD);
	MemoryWrite();		
	for(i = 0; i <= Y_GAMEBOARD; i++)
		WritePixel(31, 63, 31);
}


void drawGameboardXLines(unsigned int i)
{
	SetPageAddress(0,X_GAMEBOARD);
	SetColumnAddress(Y_SQUARE*i,Y_SQUARE*i);
	MemoryWrite();		
	for(i = 0; i <= X_GAMEBOARD; i++)
		WritePixel(31, 63, 31);
}

void updateScreen()
{
	
}

void drawStats()
{
	
}

void drawShip()
{
	
}

void drawMissiles()
{
	
}


