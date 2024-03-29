/*
* UART.h
*
* Created: 07.02.2024 15:20:03
*  Author: palhe
*/

#ifndef UART_H_
#define UART_H_
#define F_CPU 4000000UL // Definerer systemets klokkehastighet til 4 MHz.
#define MAX_COMMAND_LEN 100 // Maksimal kommandolengde.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>





// UART Function Prototypes
void USART3_init(void);
void USART3_sendChar(char c);
int USART3_printChar(char c, FILE *stream);
void USART3_sendString(char *str);
uint8_t USART3_read(void);
uint8_t compareCommands(char* src);
char c;
char command[MAX_COMMAND_LEN];

void viftestyring(int viftestyrke);





// Globale variabler
#define NUMBER_OF_COMMANDS 4
#define CR 0x0D // '\r'
#define LF 0x0A // '\n'
#define LED1_PIN_bm PIN0_bm
#define LED2_PIN_bm PIN1_bm

#endif /* UART_H_ */