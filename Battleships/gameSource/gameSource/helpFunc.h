/*
 * helpFunc.h
 *
 * Created: 03-04-2018 23:52:41
 *  Author: Martin
 */ 


#ifndef HELPFUNC_H_
#define HELPFUNC_H_

#include <avr/io.h>

//makes a cordinate contained in a uint8, the first 4 LSB is the x cordinate and the 4 MSB is the y cordinate
uint8_t makeCord(uint8_t,uint8_t);

//returns the 4 LSB
uint8_t getXCord(uint8_t);

//returns the 4 MSB
uint8_t getYCord(uint8_t);

//compares the 4 LSB of the first cordinate with the 4 LSB of the second cordinate and returns >0 if the first is biggest <0 if the first is smallest and 0 if they are the same
int8_t compareXCord(uint8_t,uint8_t);

//compares the 4 MSB of the first cordinate with the 4 MSB of the second cordinate and returns >0 if the first is biggest <0 if the first is smallest and 0 if they are the same
int8_t compareYCord(uint8_t,uint8_t);

#endif /* HELPFUNC_H_ */