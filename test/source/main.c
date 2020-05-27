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
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char switch0;
	unsigned char switch1;
	unsigned char switch2;
	unsigned char switch3;
	unsigned char switch4;
	unsigned char switch5;
	unsigned char switch6;
	unsigned char switch7;

    /* Insert your solution below */
    while (1) {

	    switch0 = ~PINA & 0x01;
	    switch1 = ~PINA & 0x02;
	    switch2 = ~PINA & 0x04;
	    switch3 = ~PINA & 0x08;
	    switch4 = ~PINA & 0x10;
	    switch5 = ~PINA & 0x20;
	    switch6 = ~PINA & 0x40;
	    switch7 = ~PINA & 0x80;

	    if(switch0){
		    PORTB = PORTB | 0x01;
		  //  	PORTB = 0xFF;
	    } else {
		    PORTB = PORTB & 0xFE;
		   // PORTB = 0x00;
	    }

	    if(switch1){
                    PORTB = PORTB | 0x02;
            } else {
                    PORTB = PORTB & 0xFD;
            }
	
	    if(switch2){
                    PORTB = PORTB | 0x04;
            } else {
                    PORTB = PORTB & 0xFB;
            }

	    if(switch3){
                    PORTB = PORTB | 0x08;
            } else {
                    PORTB = PORTB & 0xF7;
            }
	
	    if(switch4){
                    PORTB = PORTB | 0x10;
            } else {
                    PORTB = PORTB & 0xEF;
            }

	    if(switch5){
                    PORTB = PORTB | 0x20;
            } else {
                    PORTB = PORTB & 0xDF;
            }

	    if(switch6){
                    PORTB = PORTB | 0x40;
            } else {
                    PORTB = PORTB & 0xBF;
            }

	    if(switch7){
                    PORTB = PORTB | 0x80;
            } else {
                    PORTB = PORTB & 0x7F;
            }


    }
    return 1;
}
