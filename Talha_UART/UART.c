/*
 * UART.c
 *
 * Created: 07.02.2024 15:23:51
 *  Author: palhe
 */

#include "UART.h"
#include "PWM_settings.h"

// Array of commands for switch case
static char commands[NUMBER_OF_COMMANDS][MAX_COMMAND_LEN] = {
    "1",
    "2",
    "STOP"
};

// Init function
void USART3_init(void)
{
    PORTB.DIRSET = PIN0_bm; // Set TX pin to output
    PORTB.DIRCLR = PIN1_bm; // Set RX pin to input
    USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
}

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

// Function to execute command using switch case
void executeCommand(uint8_t command_number)
{
    _delay_ms(10);
    switch(command_number)
    {
        case 0:
        {
            printf("Manuell valgt \r\n");
            _delay_ms(10);
            printf("Velg hvor sterk viften skal være i prosent (0-100): ");
            
            char percentage_input[5]; // Array to store data from command panel
            int i = 0;
            
            // Read characters until a newline is received or max characters reached
            while (1) {
                char c = USART3_read();
                if (c == '\r' || c == '\n' || i >= 4) {
                    percentage_input[i] = '\0'; // Null-terminate the string
                    break;
                }
                percentage_input[i] = c;
                i++;
            }
            
            // Convert the array of characters to an integer
            int percentage = atoi(percentage_input);
            
            // Check if the percentage is within the valid range
            if (percentage >= 0 && percentage <= 100) {
                viftestyring(percentage);
                printf("Viftestyrke satt til %d%%\n", percentage);
            } else {
                printf("Invalid percentage input. Please enter a value between 0 and 100.\n");
            }

            _delay_ms(10);
            break;
        }
        // Case 1
        case 1:
            PORTD.OUTSET = PIN1_bm;
            printf("Autopilot valgt  \r\n");
            _delay_ms(10);
            break;
        case 2:
            PORTD.OUTSET = PIN1_bm;
            printf("Vifte stopper\r\n");
            _delay_ms(10);
            viftestyring(0);
            break;
        default:
            printf("Unknown command\r\n");
            _delay_ms(10);
            break;
    }
}

void viftestyring(int vifte_styrke_prosent)
{
    _delay_ms(500);
    int divisor = 20*vifte_styrke_prosent/100;
    TCA0.SINGLE.CMP2BUF = DUTY_CYCLE_EXAMPLE_VALUE * divisor; //divisor from 0-20 where each integer represents 5%
    printf("Viftestyrke satt til %d%%\n", vifte_styrke_prosent);
    _delay_ms(100);
}
