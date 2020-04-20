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

enum states{start, offRelease, onPress, onRelease, offPress} state;

void Tick(){
	switch(state){
		case start:
			state = offRelease;
			break;
		case offRelease:
			if(PINA == 0x01){
				state = onPress;
			} else {
				state = offRelease;
			}
			break;
		case onPress:
			if(PINA == 0x01 ){
				state = onPress;
			} else {
				state = onRelease;
			}
			break;
		case onRelease:
			if(PA0 == 0x01){
				state = offPress;
			} else {
				state = onPress;
			} 
			break;
		case offPress:
			if(PA0 == 0x01){
				state = offPress;
			} else {
				state = offRelease;
			} 
			break;
		default:
			printf("error in switch1");
			break;
	}

	switch(state){
		case start:
			break;
		case offRelease:	
			PORTB = 0x01;
			break;
		case onPress:	
			PORTB = 0x02;
			break;
		case onRelease:	
			PORTB = 0x02;
			break;
		case offPress:	
			PORTB = 0x01;
			break;
		default:
			printf("error in switch2");
			break;	
	}	
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //initialized as inputs
	DDRB = 0xFF; PORTB = 0x00;

	state = start;

	while(1){

		Tick();
	}

}	
