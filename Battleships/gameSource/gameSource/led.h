/*
 * led.h
 *
 * Created: 25-Mar-18 15:24:04
 *  Author: martin
 */ 


#ifndef LED_H_
#define LED_H_

void init_LEDport();
void writeAllLEDs(unsigned char pattern);
void turnOnLED(unsigned char led_nr);
void turnOffLED(unsigned char led_nr);
void toggleLED(unsigned char led_nr);

#endif /* LED_H_ */