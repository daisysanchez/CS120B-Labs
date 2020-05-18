/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
* video demo: https://www.youtube.com/watch?v=HlhHHft4zoo
 */
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


void set_PWM(double frequency){
	static double current_frequency;

	if(frequency != current_frequency){
		if(!frequency){
			TCCR3B &= 0x08;
		} else {
			TCCR3B |= 0x03;
		}

		if(frequency < .954){
			OCR3A = 0xFFFF;
		} else if (frequency > 31250){
			OCR3A = 0x0000;
		} else {
			OCR3A = (short)(8000000 / (128 * frequency)) -1;
		}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);

	TCCR3B = (1<<WGM32) | (1 << CS31) | (1 << CS30);

	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
enum States{start, off, play, hold} state;

double frequencies[9] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
double mii[7] = {369.99, 440.0, 554.37, 293.66, 659.25, 622.25, 587.33};

unsigned char frequency = 0;
unsigned char done;

unsigned char button0;

void Play(){
	set_PWM(mii[0]);
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;


    set_PWM(mii[1]);
	    while(!TimerFlag);
		TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;


	set_PWM(mii[2]);
		while(!TimerFlag);
		TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;


	set_PWM(mii[1]);
		while(!TimerFlag);
		TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;


	set_PWM(mii[0]);
		while(!TimerFlag);
		TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;

    set_PWM(mii[3]);
		while(!TimerFlag);
		TimerFlag = 0;

	set_PWM(0);
        while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(mii[3]);
		while(!TimerFlag);
		TimerFlag = 0;

	set_PWM(0);
        while(!TimerFlag);
        TimerFlag = 0;

		
	set_PWM(mii[3]);
		while(!TimerFlag);
		TimerFlag = 0;

	set_PWM(0);
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(mii[0]);
        while(!TimerFlag);
        TimerFlag = 0;
	while(!TimerFlag);
	TimerFlag = 0;

    set_PWM(mii[1]);
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(mii[2]);
            while(!TimerFlag);
            TimerFlag = 0;
            while(!TimerFlag);
            TimerFlag = 0;
            while(!TimerFlag);
            TimerFlag = 0;

	set_PWM(mii[1]);
            while(!TimerFlag);
            TimerFlag = 0;
	        while(!TimerFlag);
            TimerFlag = 0;
            while(!TimerFlag);
            TimerFlag = 0;

    set_PWM(mii[0]);
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(mii[4]);
        while(!TimerFlag);
        TimerFlag = 0;
		while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(mii[5]);
        while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(mii[6]);
        while(!TimerFlag);
        TimerFlag = 0;
        while(!TimerFlag);
        TimerFlag = 0;
		while(!TimerFlag);
        TimerFlag = 0;
	    while(!TimerFlag);
        TimerFlag = 0;

	set_PWM(0);
}

void Tick(){

	switch(state){
		case start:
			state = off;
			break;
		case off:
			if(button0){
				state = play;
			} else {
				state = off;
			}
			break;
		case play:
			if(button0){
				state = hold;
			} else {
				state = off;
			}
			break;
		case hold:
			if(button0){
				state = hold;
			} else {
				state = off;
			}
		default:
			break;
	}

	switch(state){
		case start:
			done = 0;
			break;
		case off:
			PORTC = 0x01;
			done = 0;
			break;
		case play:
			PORTC = 0X02;
			Play();

			break;
		case hold:
			PORTC = 0x03;
			break;
		default:
			break;
	}


}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */

	PWM_on();
	TimerSet(150);
	TimerOn();

	state = start;

    while (1) {
	    button0 = ~PINA & 0x01;
//	    button1 = ~PINA & 0x02;
//	    button2 = ~PINA & 0x04;

	   Tick();
        while(!TimerFlag);
      TimerFlag = 0;


    }
    return 1;
}
