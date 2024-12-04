/*
 * CFile1.c
 *
 * Created: 01/12/2024 09:48:37 p. m.
 *  Author: emili
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "adc.h"

void ADC_Init(void) {
	// Configurar los pines analógicos como entradas
	DDRC &= ~((1 << DDC0) | (1 << DDC1)); // PC0 y PC1 como entradas
	
	// Referencia AVCC con capacitor externo en AREF
	ADMUX = (1 << REFS0);
	
	// Habilitar ADC, preescaler 128 (16MHz / 128 = 125kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
	// Limpiar bits de selección de canal anteriores
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	// Iniciar conversión
	ADCSRA |= (1 << ADSC);
	
	// Esperar a que complete la conversión
	while (ADCSRA & (1 << ADSC));
	
	// Leer valor
	return ADC;
}

void convertir_voltaje(uint16_t adc_value, char *buffer) {
	// Debug: Imprimir valor raw del ADC y voltaje calculado
	float voltaje = (adc_value * 5.0) / 1023.0;
	
	// Formatear como cadena con 2 decimales
	sprintf(buffer, "ADC:%u V:%.2f", adc_value, voltaje);
}
