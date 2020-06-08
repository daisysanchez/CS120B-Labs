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
//#include <../header/bit.h>
#include <../header/keypad.h>
#include <../header/timer.h>
#include <../header/scheduler.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum keypadStates{start} keypadState;

int keypadTick(int keypad_state){
	unsigned char x = GetKeypadKey();
	
	switch(keypadState){
		case start:
			keypadState = start;
			break;
		
		default:
			break;

	}

	switch(x){
		case '\0':PORTB = 0X1F; break;
		case '1': PORTB = 0x01; break;
		case '2': PORTB = 0x02; break;
		case '3': PORTB = 0x03; break;
		case '4': PORTB = 0x04; break;
		case '5': PORTB = 0x05; break;
		case '6': PORTB = 0x06; break;
		case '7': PORTB = 0x07; break;
		case '8': PORTB = 0x08; break;
		case '9': PORTB = 0X09; break;
		case 'A': PORTB = 0x0A; break;
		case 'B': PORTB = 0x0B; break;
		case 'C': PORTB = 0x0C; break;
		case 'D': PORTB = 0x0D; break;
		case '*': PORTB = 0x0E; break;
		case '#': PORTB = 0x0F; break;
		default: PORTB = 0x1B; break;

	}

	return keypad_state;

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
    /* Insert your solution below */

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = start;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &keypadTick;

	TimerSet(50);
	TimerOn();


    while (1) {

	    for(unsigned short i = 0; i<numTasks; i++){
		    if(tasks[i]->elapsedTime == tasks[i]-> period){
			    tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			    tasks[i]->elapsedTime = 0;
		    }

		    tasks[i]->elapsedTime += 50;
	    }

	    keypadTick(start);
	    while(!TimerFlag);
	    TimerFlag = 0;

    }

    return 1;
}
