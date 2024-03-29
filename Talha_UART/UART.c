/*
* UART.c
*
* Created: 07.02.2024 15:23:51
*  Author: palhe
*/
//Brukes kun for å lese av verdien til potensiometeret

#include "UART.h"
// Initialiserer USART3 for seriell kommunikasjon med spesifisert baudrate.
#include "PWM_settings.h"


// Setting up FDEV_SETUP_STREAM to use USART3_printChar
// Array of commands to compare to
static char commands[NUMBER_OF_COMMANDS][MAX_COMMAND_LEN] = {
	"1",
	"2",
	"STOP"
};

/*
static char vifte_styrke[NUMBER_OF_COMMANDS][MAX_COMMAND_LEN] = {
	"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"
};
*/
// Init function
void USART3_init(void)
{
	
	PORTB.DIRSET = PIN0_bm; // Set TX pin to output
	PORTB.DIRCLR = PIN1_bm; // Set RX pin to input
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
}

char command[MAX_COMMAND_LEN];


// Function to send char
void USART3_sendChar(char c)
{
	while (!(USART3.STATUS & USART_DREIF_bm)) //while data register not empty
	{
		;
	}
	USART3.TXDATAL = c;
}
// Wrapping USART3_sendChar in a function computable with FDEV_SETUP_STREAM
int USART3_printChar(char c, FILE *stream)
{
	USART3_sendChar(c);
	return 0;
}
// Function to send string
void USART3_sendString(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		USART3_sendChar(str[i]);
	}
}
// Function to read received char
uint8_t USART3_read()
{
	while (!(USART3.STATUS & USART_RXCIF_bm))
	{
		;
	}
	uint8_t src = USART3.RXDATAL;
	USART3_sendChar(src);
	return src;
}
uint8_t compareCommands(char* src)
{
	// Return index of command received or 255 if none
	for(uint8_t i = 0; i < NUMBER_OF_COMMANDS; i++){
		if(strcmp(src, commands[i]) == 0){
			return i;
		}
	}
	return 255;
}
// Function to exicute command using switc case
void executeCommand(uint8_t command_number)
{
	_delay_ms(10);
	switch(command_number)
	{
		case 0:
		PORTD.OUTSET = PIN0_bm;
		printf("Manuell valgt \r\n");
		viftestyring(10);
		_delay_ms(10);
		break;
		case 1:
		PORTD.OUTSET = PIN1_bm;
		printf("Autopilot valgt  \r\n");
		_delay_ms(10);
		break;
		case 2:
		PORTD.OUTSET = PIN1_bm;
		printf("Vifte stopper\r\n");
		viftestyring(0);
		_delay_ms(10);
		break;
		default:
		printf("unknown command\r\n");
		_delay_ms(10);
	}
}

void viftestyring(int vifte_styrke_prosent)
{
	printf("Velkommen til manuell styring/n`r");
	printf("Velg hvor sterk viften skal være i prosent\n\r");
	int divisor = (20/100)*vifte_styrke_prosent;
	TCA0.SINGLE.CMP2BUF = DUTY_CYCLE_EXAMPLE_VALUE*divisor; //divisoren går fra 0-20 hvor hvert hetall representerer 5%
	printf(TCA0.SINGLE.CMP2BUF);
	_delay_ms(100);
}