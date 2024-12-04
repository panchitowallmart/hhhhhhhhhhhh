/*
 * IncFile1.h
 *
 * Created: 01/12/2024 09:48:19 p. m.
 *  Author: emili
 */ 

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
void convertir_voltaje(uint16_t adc_value, char *buffer);

#endif
