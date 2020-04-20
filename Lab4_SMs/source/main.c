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

enum states{start, hashPress, hashRelease, yPress, init} state;

void Tick(){
	
	switch(state){
		case start:
			state = init;
			break;
		case init:
			if(PINA == 0X01){
				state = hashPress;
			} else {
				state = init;
			}
			break;
		case hashPress: 
			if(PINA & 0x80) state = init;
			if(PINA == 0x00){
				state = hashRelease;
			} else if (PINA == 0X01){
				state = hashPress;
			} else {
				state = init;
			}
			break;
		case hashRelease:
			if(PINA & 0X80) state = init;
			if(PINA == 0x02){
				state = yPress;
			} else if (PINA == 0x00){
				state = hashRelease;
			} else {
				state = init;
			} 
			break;
		case yPress :
			state = init;
			break;

		default:
		//	printf("error in switch1");
			break;
	}

	switch(state){
		case init:
			PORTB = 0X00;
			break;
		case yPress:
			PORTB = 0X01;
			break;
		default:
			break;
	}

	
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //initialized as inputs
	DDRB = 0xFF; PORTB = 0x00; //initialized as outputs

	state = start;

	while(1){
		Tick();
	}	

}
