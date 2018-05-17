/*
 * radio.h
 *
 * Created: 12-Apr-18 09:19:45
 *  Author: martin
 */ 


#ifndef SPI_H_
#define SPI_H_
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void spiMasterInit(void);
void spiSlaveInit(void);
//void spiSend(uint8_t);
//uint8_t spiRecieve(void);
uint8_t spiTransmit(uint8_t);




#endif /* RADIO_H_ */