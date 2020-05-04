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

enum states{start, release,  press, hold, reset} state;

unsigned char button0 = 0x00;
unsigned char button1 = 0x00;

unsigned char cnt = 0;

void Tick(){

	switch(state){
		case start:
			state = release;
			break;
		case release:
			if(button0 ^ button1){
			       	state = press;
			} else if (button0 && button1){
				state = reset;
			} else {
				state = release;
			}	
			break;
		case press:
			if(button0 ^ button1){
				state = hold;
			} else if (button0 && button1) {
				state = reset;
			} else {
				state = release;
			}
			break;
		case hold:
			if(button0 ^ button1){
				state = hold;
			} else if (button0 && button1){
				state = reset;
			} else {
				state = release;
			}
			break;
		case reset:
			if(!button0 && !button1){
				state = release;
			} else {
				state = reset;
			}
			break;
		default:
			break;
	}

	switch (state) {
		case press:
			if(button0 && cnt<9){
				cnt ++;
				PORTC = cnt;
			} else if (button1 && cnt>0){
				cnt--;
				PORTC = cnt;
			} else {
			}

			break;
		case hold:
			break;
		case reset:
			cnt = 0;
			PORTC = 0;
			break;
		case release:
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
		button0 = ~PINA & 0x01; //pa0
		button1 = ~PINA & 0x02; //pa1
		Tick();
	}

}	
