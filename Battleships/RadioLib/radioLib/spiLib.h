/*
 * radio.h
 *
 * Created: 12-Apr-18 09:19:45
 *  Author: martin
 */ 



#ifndef SPI_H_
#define SPI_H_

#define ACK 0x7F
#define NACK 0x8F

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>


#define PORT_SPI  PORTB
#define PIN_SPI	PINB
#define MEGA

#ifdef UNO
#define DDR_SPI     DDRB
#define DD_MISO     DDB4
#define DD_MOSI     DDB3
#define DD_SS       DDB2
#define DD_SCK      DDB5
#endif

#ifdef MEGA
#define DDR_SPI     DDRB
#define DD_MISO     DDB3
#define DD_MOSI     DDB2
#define DD_SS       DDB0
#define DD_SCK      DDB1
#endif


void spiMasterInit(void);
void spiSlaveInit(void);
uint8_t spiTransmit(uint8_t);
uint8_t spiReceive(void);
void spiSend(uint8_t);





#endif /* RADIO_H_ */