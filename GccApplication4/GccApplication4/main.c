/*
 * GccApplication4.c
 *
 * Created: 01/12/2024 09:45:31 p. m.
 * Author : emili
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "usart.h"
#include "adc.h"

#define POT1 0 // Canal ADC 0 (PC0)
#define POT2 1 // Canal ADC 1 (PC1)

char buffer[50]; // Buffer global para mayor claridad

void ConfigureBluetooth(void);

int main(void) {
	uint16_t adc_value;
	char rx_char;
	uint8_t current_pot = POT1; // Inicialmente POT1

	// Inicializar módulos
	USART_Init(103);  // Inicialización USART (9600 baudios)
	ADC_Init();       // Inicialización del ADC
	
	_delay_ms(500);   // Retardo de estabilización

	// Configurar Bluetooth
	ConfigureBluetooth();

	// Mensaje de bienvenida
	USART_SendString("Sistema de Monitoreo de Potenciómetros\r\n");
	USART_SendString("Comandos: \r\n");
	USART_SendString("'1' - Mostrar voltaje POT1\r\n");
	USART_SendString("'2' - Mostrar voltaje POT2\r\n");

	while (1) {
		// Verificar si hay un comando recibido
		if (UCSR0A & (1 << RXC0)) {
			rx_char = USART_Receive();
			
			// Seleccionar potenciómetro
			if (rx_char == '1') {
				current_pot = POT1;
				USART_SendString("Seleccionado POT1\r\n");
			}
			else if (rx_char == '2') {
				current_pot = POT2;
				USART_SendString("Seleccionado POT2\r\n");
			}
		}
		
		// Leer valor del potenciómetro seleccionado
		adc_value = ADC_Read(current_pot);
		
		// Convertir valor ADC a voltaje
		convertir_voltaje(adc_value, buffer);
		
		// Enviar valor de voltaje
		USART_SendString("Voltaje POT");
		USART_Transmit(current_pot == POT1 ? '1' : '2');
		USART_SendString(": ");
		USART_SendString(buffer);
		USART_SendString("\r\n");
		
		_delay_ms(1000); // Retardo entre lecturas
	}
	return 0;
}

// Función de configuración de Bluetooth
void ConfigureBluetooth(void) {
	_delay_ms(100);
	
	// Comandos AT para configuración
	USART_SendString("AT\r\n");
	_delay_ms(100);
	
	USART_SendString("AT+RENEW\r\n");  // Restaurar configuración de fábrica
	_delay_ms(100);
	
	USART_SendString("AT+RESET\r\n");  // Reiniciar módulo
	_delay_ms(100);
	
	USART_SendString("AT+ROLE0\r\n");  // Modo esclavo
	_delay_ms(100);
	
	USART_SendString("AT+BAUD0\r\n");  // Baudrate 9600
	_delay_ms(100);
	
	USART_SendString("AT+NAMEProyectoPOTS\r\n");  // Nombre del dispositivo
	_delay_ms(100);
}
