/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTD = 0x00;

    /* Insert your solution below */

	ADC_init();

	unsigned short x = ADC;




	
	
    while (1) {
	
	    if(ADC < 112){
		    PORTB = 0x01;
	    } else if(ADC >= 112 && ADC < 224) {
		    PORTB = 0x02;
	    } else if(ADC >= 224 && ADC < 336)  {
		    PORTB = 0x04;
	    } else if (ADC >= 336 && ADC < 448){
		    PORTB = 0x08;
	    } else if(ADC >= 448 && ADC < 560){
		    PORTB = 0x10;
	    } else if(ADC >= 560 && ADC < 672) {
		    PORTB = 0x20;
	    } else if(ADC >= 672 && ADC < 784){
		    PORTB = 0x40;
	    } else{
		    PORTB = 0x80;
	    }
    }
    return 1;
}
