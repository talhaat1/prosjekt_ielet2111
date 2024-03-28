/*
 * ADC.h
 *
 * Created: 21.03.2024 09:15:07
 *  Author: palhe
 */ 

#define RTC_PERIOD (511)
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 4000000UL // Definerer systemets klokkehastighet til 4 MHz.
#define MAX_COMMAND_LEN 100 // Maksimal kommandolengde.
#include <stdio.h>
uint16_t adcVal;
void ADC0_init(void);
uint16_t ADC0_read(void);
// Prototyper for USART-funksjoner
