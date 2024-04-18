/*
 * PWM_settings.h
 *
 * Created: 20.03.2024 14:18:26
 *  Author: palhe
 */ 
#include <avr/io.h>
#define F_CPU 4000000UL
#define PERIOD_EXAMPLE_VALUE (19) //25kHz
#define DUTY_CYCLE_EXAMPLE_VALUE (19) //DUTY_CYCLE - verdi mellom 0-20, hvor 1 tilsier 5% vifte hastighet
void TCA0_init(void);
void TCA0_init_split(void);
void TCA1_init_split(void);


//Det her må i main:

	TCA0_init_split(void);
	TCA1_init_split(void);

	PORTB.DIR |= PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm;/* set pin 0, 1, 2 of PORT B as output */
	
	PORTA.DIR |= PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm; /* set pin 3, 4, 5 of PORT A as output */

	
