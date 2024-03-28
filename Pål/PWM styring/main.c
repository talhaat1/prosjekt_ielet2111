#define RTC_PERIOD (511)
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 4000000UL // Definerer systemets klokkehastighet til 4 MHz.
#define USART3_BAUD_RATE(BAUD_RATE) ((F_CPU*64) / (16*(float)BAUD_RATE)-1) // Makro for baudrate-beregning.
#define MAX_COMMAND_LEN 100 // Maksimal kommandolengde.
#include <stdio.h>
#include "UART.h" //Brukes kun for å lese av verdien til potensiometeret
#include "ADC.h"
#include "PWM_settings.h"


int main(void)
{
	TCA0_init();	ADC0_init();
	PORTA.DIR |= PIN2_bm;
	USART3_init(9600); // Initialiserer USART3 med 9600 baud.
	stdout = &USART_stream; // Omdirigerer stdout til USART-streamen.
	// Replace with your application code 
while (1) {
		
		unsigned short int adcVal100= 0;
		
		for (int i = 0; i < 100; i++) {
			adcVal = ADC0_read();
			adcVal100 += adcVal;
		}		uint8_t divisor = adcVal100/2000;		printf("adcVal: %d\r\n", (divisor));
		if (divisor <20) //Sørger for en dutycycle maks går til 100%
		{
			TCA0.SINGLE.CMP2BUF = DUTY_CYCLE_EXAMPLE_VALUE*divisor; //divisoren går fra 0-20 hvor hvert hetall representerer 5% 
		}
}
}