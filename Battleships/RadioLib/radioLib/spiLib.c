/*
 * radio.c
 *
 * Created: 12-Apr-18 09:27:35
 *  Author: martin
 */ 

#include "spiLib.h"


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
	SPDR = dataout;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

uint8_t spiReceive(void)
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void spiSend(uint8_t dataout)
{
	SPDR = dataout;
	while(!(SPSR & (1<<SPIF)));
}
