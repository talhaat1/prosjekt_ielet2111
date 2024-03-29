/*
 * PWM_settings.c
 *
 * Created: 20.03.2024 14:18:12
 *  Author: palhe
 */ 
#include "PWM_settings.h"
void TCA0_init(void) {	// set waveform output on PORT A
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTA_gc;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm // enable compare channel 0
	| TCA_SINGLE_WGMODE_DSBOTTOM_gc; // set dual-slope PWM mode
	TCA0.SINGLE.CMP2BUF = DUTY_CYCLE_EXAMPLE_VALUE; //duty cycle
	TCA0.SINGLE.PERBUF = PERIOD_EXAMPLE_VALUE;	//Setter Hz
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc // set clock source (sys_clk/4)  //TCAprescaler
	| TCA_SINGLE_ENABLE_bm; // start timer
}