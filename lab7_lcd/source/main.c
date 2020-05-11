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
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

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

enum States{start, release, press, hold, reset} state;

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
			} else if(button0 && button1){
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
			if(button0 && !button1){
				state = release;
			} else {
				state = reset;
			} 
			break;
		default:
			break;
	}

	switch(state){
		case press:
			if(button0 && cnt<9){
				cnt++;
				LCD_ClearScreen();
				LCD_WriteData (cnt + '0');
			} else if(button1 && cnt > 0){
				cnt --;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
			} else {
			}
			break;
		case hold:
			break;
		case reset:
			cnt = 0;
			LCD_ClearScreen();
			LCD_WriteData('0');
			break;
		case release:
			break;
		default:
			break;
	}
}
	

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	state = start;

	TimerSet(1000);
	TimerOn();

	LCD_init();

//	LCD_DisplayString(1, "Hello World");

    /* Insert your solution below */
    while (1) {
//	    LCD_DisplayString(1, "Hello World");
	    button0 = ~PINA & 0x01;
	    button1 = ~PINA & 0x02;
	    Tick();
	    while(!TimerFlag);
	    TimerFlag=0;
	    continue;

    }
    return 1;
}
