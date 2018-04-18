/*
 * radio.h
 *
 * Created: 12-Apr-18 09:19:45
 *  Author: martin
 */ 


#ifndef RADIO_H_
#define RADIO_H_
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void radioInit();
uint16_t radioCmd(uint16_t);
void radioSend(uint8_t);
void radioTransmit(uint8_t*, uint8_t*,uint8_t);




#endif /* RADIO_H_ */