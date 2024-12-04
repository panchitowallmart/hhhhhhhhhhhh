/*
 * IncFile1.h
 *
 * Created: 01/12/2024 09:48:00 p. m.
 *  Author: emili
 */ 

#ifndef USART_H
#define USART_H

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_SendString(char *str);

#endif
