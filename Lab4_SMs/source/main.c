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
			if(PA0){
				state = onPress;
			} else {
				state = offRelease;
	`		}
			break;
		case onPress:
			if(PA0){
				state = onPress;
			} else {
				state = onRelease;
			}
			break;
		case onRelease:
			if(PA0){
				state = offPress;
			} else {
				state = onPress;
			} 
			break;
		case offPress:
			if(PA0){
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
			PB0 = 1;
			PB1 = 0;
			break;
		case onPress:
			PB0 = 0;
			PB1 = 1;
			break;
		case onRelease:
			PB0 = 0;
			PB1 = 1;
			break;
		case offPress;
			PB0 = 1;
			PB1 = 0;
			break;
		default:
			printf("error in switch2");
			break;	
	}	
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //initialized as inputs
	DDRB = 0xFF; PORTB = 0x00; //initialized as outputs

	state = start;


    /* Insert your solution below */
    while (1) {	
	
	Tick();

    }
    return 1;
}
