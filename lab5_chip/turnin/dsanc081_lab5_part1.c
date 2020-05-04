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
	
	unsigned char indicator = 0x00;

	unsigned char button0 = 0x00;
	unsigned char button1 = 0x00;
	unsigned char button2 = 0x00;
	unsigned char button3 = 0x00;
//
    /* Insert your solution below */
    while (1) {	

	button0 = ~PINA & 0x01; //sets to pa0
	button1 = ~PINA & 0x02; //sets to pa1
	button2 = ~PINA & 0x04; //sets to pa2
	button3 = ~PINA & 0x08; //sets to pa3

	if((button0 && !button1 && !button2 && !button3) || (!button0 && button1 &&  !button2 && !button3)){ //1, 2
		//light c5, 6
		indicator = 0x60;
	} else if((button0 && button1 && !button2 && !button3) || (!button0 && !button1 && button2 && !button3)){ //3,4
		//lights c5,4 and 6
		indicator = 0x70;
	} else if((button0 && !button1 && button2 && !button3) || (!button0 && button1 && button2 && !button3)){ //5,6
		//lights c5, 4, 3
		indicator = 0x38;
	} else if((button0 && button1 && button2 && !button3) || (!button0 && !button1 &&  !button2 && button3) || (button0 && !button1 && !button2 && button3)){ //7,8,9
		indicator = 0x3C; 
	} else if((!button0 && button1 && !button2 && button3) || (button0 && button1 && !button2 && button3) || (!button0 && !button1 && button2 && button3)){ //10,11,12
		indicator = 0x3E;
	} else if((button0 && !button1 && button2 && button3) || (!button0 && button1 && button2 && button3) || (button0 && button1 && button2 && button3)){ //13,14,15
		indicator = 0x3F;
	} else { //0
		indicator = 0x0;
	}

	PORTC = indicator;
    }
    return 1;
}
