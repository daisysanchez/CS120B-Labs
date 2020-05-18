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
enum States{start, release, press, hold} state;

double frequencies[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

unsigned char frequency = 0;
unsigned char on;

unsigned char button0;
unsigned char button1;
unsigned char button2;

void Tick(){
	switch(state){
		case start:
			state = release;
			break;
		case release:
		//	if( (button0 && !button1 && !button2) || (!button0 && button1 && !button2) || (!button0 && !button1 && button2)){
			if(button0 || button1 || button2){
				state = press;
			} else {
				state = release;
			}
			break;

		case press:
	//		if((button0 && !button1 && !button2) || (!button0 && button1 && !button2) || (!button0 && !button1 && !button2)){
	
			if(button0 || button1 || button2){	
				state = hold;
			} else {
				state = release;
			}
			break;
		case hold:
			
	//		if((button0 && !button1 && !button2) || (!button0 && button1 && !button2) || (!button0 && !button1 && !button2)){
			if(button0 || button1 || button2){	
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
			break;
		case release:
			break;
		case press:
			if(button0){ //toggle on off
				if(on == 0){
					set_PWM(frequencies[frequency]);
					on = 1;
				} else {
					set_PWM(0.0);
					on = 0;
				}

			} else if(button1) { //raise freq
				if(frequency < 7){
					frequency++;
					if(on){
						set_PWM(frequencies[frequency]);
					}
				}
			} else if(button2) {
				if(frequency > 0){
					frequency--;
					if(on){
						set_PWM(frequencies[frequency]);
					}
				}
			}
			break;
		case hold:
			break;
		default:
			break;
	}


				

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */

	frequency = 0;
	on = 0;

	PWM_on();

    while (1) {
	    button0 = ~PINA & 0x01;
	    button1 = ~PINA & 0x02;
	    button2 = ~PINA & 0x04;

	    set_PWM(261.63);
	    set_PWM(440.0);

	   // Tick();


    }
    return 1;
}
