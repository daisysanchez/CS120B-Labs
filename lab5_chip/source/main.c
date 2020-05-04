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

enum states{start, release, press, hold} state;

unsigned char button0 = 0x00;

unsigned char cnt;

void Tick(){
	switch(state){
		case start:
			state = release;
			break;
		case release:
			if(button0){
				state = press;
			} else {
				state = release;
			}
			break;
		case press:
			if(button0){
				state = hold;
			} else {
				state = release;
			}
			break;
		case hold:
			if(button0){
				state = hold;
			} else {
				state = release;
			}
			break;
		default:
			break;
	}

	switch(state){
		case start:
			PORTB = 0x00;
			break;
		case release:
		
			break;
		case press:
			cnt++;	
			/*if(cnt == 0){
				PORTB = 0x08;
			} else if (cnt == 1){
				PORTB = 0x21;
			} else{// if (cnt %3 A== 2){
				//6, 1, 3
				PORTB = 0x65;
			}*/
			break;
		case hold:
			if(cnt == 1){
				PORTB = 0x08;
			
			} else if (cnt == 2){
				PORTB = 0x12;
			} else if(cnt == 3){ //if(cnt == 3){
				PORTB = 0x25;
			} else {
				cnt = 1;
			}
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //initialized as inputs
	DDRB = 0xFF; PORTB = 0x00; //initialized as outputs

	PORTB = 0x00;

	state = start;
	cnt = 0;

	while(1){
		button0 = ~PINA & 0X01;	
		Tick();
	//PORTB = 0XFF;
	}

}	
