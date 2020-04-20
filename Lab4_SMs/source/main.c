/*	Author: dsanc081
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{start, max, min} state;

void Tick(){
	
	switch(state){
		case start:
			state = main;
			break;
		case main:
			if(PINA == 0x01){
				PORTC = PORTC + 0x01;
				if(PORTC == 0x09){
					state = max;
				} else {
					state = main;
				}
			} else if (PINA == 0x02){
				PORTC = PORTC - 0x01;
				if(PORTC == 0x00){
					state = min;
				} else {
					state = main;
				}
			} else if (PINA == 0x03){
				PORTC = 0x00;
				state = min;
			}
			break;
		case max:
			if(PINA == 0x02){
				PORTC = PORTC - 0x01;
				state = main;
			} else {
				state = max;
			}
			break;
		case min:
			if(PINA == 0x01){
				PORTC = PORTC + 0x01;
				state = main;
			} else {
				state = min;
			}
			break;
		default:
			printf("error in switch1")
	}

	
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //initialized as inputs
	DDRC = 0xFF; PORTC = 0x00; //initialized as outputs

	state = start;

	PORTC = 0x07;

	while(1){

		Tick();
	}

}	
