/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//video demo: https://www.youtube.com/watch?v=Xm-nrdfcAlw
//#include "../header/timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
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

enum States{start, B0, B1, B2} state;
unsigned char tmpB = 0x00;

void Tick(){

	switch(state){
		case start:
			state = B0;
		case B0:
			state = B1;	
			break;
		case B1:
			state = B2;	
			break;

		case B2:
			state = B0;	
			break;

		default:
			break;
	}

	switch(state){
		case start:
			break;
		case B0:
			tmpB = 0x01;
			PORTB = tmpB;
			break;
		case B1:
			tmpB = 0x02;
			PORTB = tmpB;
			break;
		case B2:
			tmpB = 0x04;
			PORTB = tmpB;
		break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; //sets portb to output
	TimerSet(1000);
	TimerOn();

	//unsigned char tmpB = 0x00;

	 state = start;

    /* Insert your solution below */
    while (1){

	Tick();
	while(!TimerFlag);
	TimerFlag = 0;

    }
    return 1;
}
