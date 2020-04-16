/*	Author: dsanc081
 *  Partner(s) Name: 
 *	Lab Section: 028
 *	Assignment: Lab 2  Exercise 3
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

	//DDRB = 0XFF;
	//PORTB = 0x00;
	
	DDRA = 0X00; PORTA = 0XFF;
//	DDRB = 0XFF; PORTB = 0X00;
	DDRC = 0xFF; PORTC = 0x00;
	
	
//	unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char spaceA0;
	unsigned char spaceA1;
	unsigned char spaceA2;
	unsigned char spaceA3;

	unsigned char cntavail;


    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0x0F; //taked in a3 - a0
	
	spaceA0 = tmpA & 0x01;

	spaceA1 = tmpA & 0x02;
	spaceA1 = spaceA1 >> 1;

	spaceA2 = tmpA & 0x04;
	spaceA2 = spaceA2 >> 2;

	spaceA3 = tmpA & 0x08;
	spaceA3 = spaceA3 >> 3;

	cntavail = spaceA0 + spaceA1 + spaceA2 + spaceA3;

	PORTC = 0x04 - cntavail;
	
	if(cntavail == 0x04){
		PORTC = PORTC | 0x80;
	}

    }
    return 0;
}
