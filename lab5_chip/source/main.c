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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
//	DDRB = 0xFF; PORTB = 0X00; //configures port b as outputs
	DDRC = 0xFF; PORTC = 0x00;
	

	unsigned char sensor = 0x00;
	unsigned char indicator = 0x00;

    /* Insert your solution below */
    while (1) {	

	sensor = PINA;

	if((~sensor & 0x01) == 0x01 || (~sensor & 0x00) == 0x00){
		indicator = 0x60;
	} 
       	if ((~sensor & 0x03) == 0x03 || (~sensor & 0x04) == 0x04){
		indicator = 0x70;
	} 
       	if ( (~sensor & 0x05) == 0x05 || (~sensor & 0x06) == 0x06){
		indicator = 0x38;
	}
       	if ((~sensor & 0x07) == 0x07 || (~sensor & 0x08) == 0x08 || (~sensor & 0x09) == 0x09){
		indicator  = 0x03C;
	}
       	if ((~sensor & 0x0A) == 0x0A || (~sensor & 0x0B) == 0x0B || (~sensor & 0X0c) == 0x0c){
		indicator = 0x3e;
	} 
       if((~sensor & 0x0D) == 0x0D || (~sensor & 0x0E) == 0x0E || (~sensor & 0x0F) == 0x0F){
		indicator = 0x3f;
	}	
	
	PORTC = indicator;

	

    }
    return 1;
}
