/**************************************
* "uart.h":                           *
* Header file for Mega32 UART driver. *
* Henning Hargaard, 1/11 2011         *
***************************************/
#ifndef UART
#define UART

#if defined(__cplusplus)
extern "C" {                 // Make sure we have C-declarations in C++ programs
#endif

void InitUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char CharReady();
char ReadChar();
void SendChar(char Ch);
void SendString(char* String);
void SendInteger(int Number);
/**************************************/

#if defined(__cplusplus)
}
#endif
#endif