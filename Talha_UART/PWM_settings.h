/*
 * PWM_settings.h
 *
 * Created: 20.03.2024 14:18:26
 *  Author: palhe
 */ 
#include <avr/io.h>
#define F_CPU 4000000UL
#define PERIOD_EXAMPLE_VALUE (20) //25kHz
#define DUTY_CYCLE_EXAMPLE_VALUE (1) //DUTY_CYCLE - verdi mellom 0-20, hvor 1 tilsier 5% vifte hastighet
void TCA0_init(void);
