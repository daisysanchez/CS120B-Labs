/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//video demo: https://www.youtube.com/watch?v=wDiPH8Y3Tu8

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;

	OCR1A = 125;

	TIMSK1 = 0x02;

	TCNT1 = 0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;

}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
		_avr_timer_cntcurr--;
		if(_avr_timer_cntcurr == 0){
			TimerISR();
			_avr_timer_cntcurr = _avr_timer_M;
		}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States{start, B0, B1, B2, press, release} state, prev_state, next_state;

unsigned char button0;

void Tick(){

	switch(state){
		case start:
			state = B0;
			break;
		case B0:
			if(button0){
				state = press;
			} else {
				state = B1;	
				
			}
			next_state = B1;
			prev_state = B0;	
			break;
		case B1:
			if(button0){
				state = press;
				if(prev_state == B0){
					next_state = B2;
				} else {
					next_state = B0;
				}
			} else {
				if(prev_state == B0){
					state = B2;
				} 
				else {
					state = B0;
				}
			}
			prev_state = B1;
			break;

		case B2:
			if(button0){
				state = press;
				next_state = B1;
			} else {
				state = B1;		
			}
			prev_state = B2;
			break;
		case press:
			if(button0){
				state = press;
			} else {
				state = release;
			}
			break;
		case release:	
		//	if(prev_state == B0) state = B0;
		//	if(prev_state == B1) state = B1;
		//	if(prev_state == B2) state = B2;
			state = next_state;
			break;
			

		default:
			break;
	}

	switch(state){
		case start:
			break;
		case B0:	
			PORTB = 0x01;
			break;
		case B1:
	
			PORTB = 0x02;
			break;
		case B2:	

			PORTB = 0x04;
			break;
		default:
			break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; //sets portb to output
	TimerSet(300);
	TimerOn();

	//unsigned char tmpB = 0x00;

	 state = start;
	 prev_state = start;	

    /* Insert your solution below */
    while (1){
	    button0 = ~PINA & 0x01;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;

    }
    return 1;
}
