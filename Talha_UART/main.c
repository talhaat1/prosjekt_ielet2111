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


static FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	// flytte disse til egen funksjon
	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600); // Set Baud rate 9600
	char command[MAX_COMMAND_LEN];
	uint8_t index = 0;
	char c;
	

	//***********************************************
	
	TCA0_init();	ADC0_init();
	PORTA.DIR |= PIN2_bm;
	USART3_init(); // Initialiserer USART3 med 9600 baud.
	stdout =& USART_stream; // Omdirigerer stdout til USART-streamen.
	// Replace with your application code
	
	printf("Velkommen til meny\r\n For manuel tast inn 1\r\n For auto tast 2\r\n");

	while (1)
	{

		c = USART3_read();
		if(c != LF && c != CR){ // If received \r or \n
			command[index++] = c;
			if(index > MAX_COMMAND_LEN)
			{
				printf("\r\n");
				index = 0;
			}
		}
		if(c == CR){ // if recived \r
			command[index] = 0;
			index = 0;
			printf("Received command: ");
			executeCommand(compareCommands(command));
		}
	}
}