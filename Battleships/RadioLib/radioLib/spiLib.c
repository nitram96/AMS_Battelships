/*
 * radio.c
 *
 * Created: 12-Apr-18 09:27:35
 *  Author: martin
 */ 

#include "spiLib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h> 

#define PORT_SPI  PORTB
#define PIN_SPI	PINB
#define DDR_SPI     DDRB
#define DD_MISO     DDB3
#define DD_MOSI     DDB2
#define DD_SS       DDB0
#define DD_SCK      DDB1
#define IRQ			2

//#define LOW_SCK()	PORT_RADIO &= ~(1<<DD_SCK)
//#define HI_SCK()	PORT_RADIO |= (1<<DD_SCK)
//#define HI_MOSI()	PORT_RADIO |= (1<<DD_MOSI)
//#define LOW_MOSI()	PORT_RADIO &= ~(1<<DD_MOSI)
//#define MISO_HI()	PIN_RADIO&(1<<DD_MISO)
//#define HI_SS()		PORT_RADIO |= (1<<DD_SS)
//#define LOW_SS()	PORT_RADIO &= ~(1<<DD_SS)



void spiMasterInit()
{		
	DDR_SPI = ((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));
	
	DDR_SPI &= ~(1<<DD_MISO);
	
	PORT_SPI |= (1<<DD_SS);
	
	SPCR = ((1<<SPE)|               // SPI Enable
	(0<<SPIE)|              // SPI Interupt Enable
	(1<<MSTR)|              // Master/Slave select
	(1<<SPR0));    // SPI Clock Rate
	
	SPSR &= ~(1<<SPI2X);
}

void spiSlaveInit()
{
	DDR_SPI &= ~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));
	DDR_SPI |= (1<<DD_MISO);
	
	SPCR = (1<<SPE);              // SPI Enable
}

//void radioSend(uint8_t aByte)
//{
	//SPDR = aByte;
	//while(!(SPSR & (1<<SPIF)));
//}
//
//uint8_t radioRecieve(void)
//{
	//
	//while(!(SPSR & (1<<SPIF)));
	//return(SPDR);
//}





uint8_t spiTransmit(uint8_t dataout)
{
	PORT_SPI |= (1<<6);
	PORT_SPI &= ~(1<<DD_SS);
	SPDR = dataout;
	while(!(SPSR & (1<<SPIF)));
	PORT_SPI |= (1<<DD_SS);
	PORT_SPI &= ~(1<<6);
	return SPDR;
	
}

