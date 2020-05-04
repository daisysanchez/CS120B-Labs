/*	Author: dsanc081
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{start, read, inc, dec, reset} state;

void Tick(){
	
	switch(state){
		case start:
			state = read;
			break;
		case read:
			if(~PINA == 0x01){
				if(PORTC != 0X09){
					PORTC = PORTC + 0X01;
				} 
				state = inc;
			} else if (~PINA == 0X02){
				if(PORTC != 0X00){
					PORTC = PORTC - 0X01;
				} 
				state = dec;
			} else if (~PINA == 0X03){
				state = reset;
			} else {
				state = read;
			}
			break;
		
		case inc:
			if(~PINA == 0X00){
				state = read;
			} else if (~PINA == 0X03) {
				state = reset;
			} else {
				state = inc;
			}
			break;
		case dec:
			if(~PINA == 0X00){
				state = read;
			} else if (~PINA == 0X03){
				state = reset;
			} else {
				state = dec;
			}
			break;
		case reset:
			if(~PINA == 0X00){
				state = read;
			} else {
				state = reset;
			}
			break;
		default:
		//	printf("error in switch1");
			break;
	}

	switch(state){
		case reset:
			PORTC = 0X00;
			break;
		default:
			break;
	}

	
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //initialized as inputs
	DDRC = 0xFF; PORTC = 0x00; //initialized as outputs

	state = start;

	PORTC = 0x00;

	while(1){

		Tick();
	}

}	
