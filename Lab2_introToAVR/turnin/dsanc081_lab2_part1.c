/*	Author: dsanc081
 *  Partner(s) Name: 
 *	Lab Section: 028
 *	Assignment: Lab 2  Exercise 1
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
	DDRB = 0XFF; PORTB = 0X00;
	
	
	unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;


    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0x03;
	
	if(tmpA == 0x03){
		tmpB = (tmpB & 0xFE) | 0x01;
	}

	PORTB = tmpB;

    }
    return 0;
}
