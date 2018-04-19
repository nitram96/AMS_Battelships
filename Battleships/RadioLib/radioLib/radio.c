/*
 * radio.c
 *
 * Created: 12-Apr-18 09:27:35
 *  Author: martin
 */ 

#include "radio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define PORT_RADIO  PORTB
#define PIN_RADIO	PINB
#define DDR_SPI     DDRB
#define DD_MISO     DDB4
#define DD_MOSI     DDB3
#define DD_SS       DDB2
#define DD_SCK      DDB5
#define IRQ			2

#define LOW_SCK()	PORT_RADIO &= ~(1<<DD_SCK)
#define HI_SCK()	PORT_RADIO |= (1<<DD_SCK)
#define HI_MOSI()	PORT_RADIO |= (1<<DD_MOSI)
#define LOW_MOSI()	PORT_RADIO &= ~(1<<DD_MOSI)
#define MISO_HI()	PIN_RADIO&(1<<DD_MISO)
#define HI_SS()		PORT_RADIO |= (1<<DD_SS)
#define LOW_SS()	PORT_RADIO &= ~(1<<DD_SS)

void radioInit()
{		
	DDR_SPI &= ~((1<<DD_MOSI)|(1<<DD_MISO)|(1<<DD_SS)|(1<<DD_SCK));
	
	DDR_SPI |= ((1<<DD_MOSI)|(1<<DD_SS)|(1<<DD_SCK));
	
	HI_SS();
	HI_MOSI();
	LOW_SCK();
	
	radioCmd(0x80D7);
	radioCmd(0x8239);
	radioCmd(0xA640);
	radioCmd(0xC647);
	radioCmd(0x94A0);
	radioCmd(0xC2AC);
	radioCmd(0xCA81);
	radioCmd(0xCED4);
	radioCmd(0xC483);
	radioCmd(0x9850);
	radioCmd(0xCC67);
	radioCmd(0xE000);
	radioCmd(0xC800);
	radioCmd(0xC400);
}

void radioSend(uint8_t aByte)
{
	while(PIND&(1<<IRQ));
	radioCmd(0xB800+aByte);
}

uint8_t radioRecieve(void)
{
	uint16_t fifoData;
	while(PIND&(1<<IRQ));
	radioCmd(0x0000);
	fifoData=radioCmd(0xB000);
	return (fifoData&0x00FF);
}





void radioTransmit(uint8_t* dataout, uint8_t* datain, uint8_t len)
{
	uint8_t i;
	for (i = 0; i<len; i++)
	{
		SPDR = dataout[i];
		while((SPSR &(1<<SPIF))==0);
		datain[i] = SPDR;
	}
}

uint16_t radioCmd(uint16_t aCmd)
{
	uint8_t i;
	uint16_t temp = 0;
	LOW_SCK();
	LOW_SS();
	for(i = 0; i<16;i++)
	{
		temp <<=1;
		if(MISO_HI())
		{
			temp |=0x0001;	
		}
		LOW_SCK();
		if (aCmd&0x8000)
		{
			HI_MOSI();
		}else{
			LOW_MOSI();
		}
		HI_SCK();
		aCmd<<=1;
	};
	LOW_SCK();
	HI_SS();
	return (temp);
}
