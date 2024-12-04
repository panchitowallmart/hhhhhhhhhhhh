/*
 * CFile1.c
 *
 * Created: 01/12/2024 09:46:21 p. m.
 *  Author: emili
 */ 

#include <avr/io.h>
#include "usart.h"

void USART_Init(unsigned int ubrr) {
	// Configuración de baudrate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	// Habilitar transmisor y receptor
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	
	// Configurar formato: 8 bits de datos, 1 bit de parada
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
	// Esperar a que el buffer de transmisión esté vacío
	while (!(UCSR0A & (1<<UDRE0)));
	
	// Colocar dato en buffer de transmisión
	UDR0 = data;
}

unsigned char USART_Receive(void) {
	// Esperar a recibir un dato
	while (!(UCSR0A & (1<<RXC0)));
	
	// Devolver dato recibido
	return UDR0;
}

void USART_SendString(char *str) {
	while (*str != 0x00) {
		USART_Transmit(*str);
		str++;
	}
}
