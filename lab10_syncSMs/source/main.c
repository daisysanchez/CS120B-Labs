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
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum StatesOne{startOne, led0, led1, led2} stateOne;
enum StatesTwo{startTwo, blinkOn, blinkOff} stateTwo;
//enum StatesComb{
unsigned char threeLEDs;
unsigned char blinkingLED;

unsigned short timerOne = 0;
unsigned short timerTwo = 0;


//cycles through pb0...pb2
void threeLEDsSM(){
	switch(stateOne){
		case startOne:
			stateOne = led0;
			break;
		case led0:
			if(timerOne == 300){
				stateOne = led1;
				timerOne = 0;
			} else {
				stateOne = led0;
			}
			break;
		case led1:
			if(timerOne == 300){
				stateOne = led2;
				timerOne = 0;
			} else {
				stateOne = led1;
			}
			break;
		case led2:
			if(timerOne == 300){
				stateOne = led0;
				timerOne = 0;
			} else {
				stateOne = led2;
			}
			break;
		default:
			break;
	}

	switch(stateOne){
		case startOne:
			break;
		case led0:
			timerOne++;
			threeLEDs = 0x01;
			break;
		case led1:
			timerOne++;
			threeLEDs = 0x02;
			break;
		case led2:
			timerOne++;
			threeLEDs = 0x04;
			break;
		default:
			break;
	}
}

void blinkingLEDsSM(){

	switch(stateTwo){
		case startTwo:
			stateTwo = blinkOn;
			break;
		case blinkOn:
			if(timerTwo == 1000){
				stateTwo = blinkOff;
				timerTwo = 0;
			} else {
				stateTwo = blinkOn;
			}
			break;
		case blinkOff:
			if(timerTwo == 1000){
				stateTwo = blinkOn;
				timerTwo = 0;
			} else {
				stateTwo = blinkOff;
			}
			break;
		default:
			break;	
	}

	switch(stateTwo){
		case startTwo:
			break;
		case blinkOn:
			timerTwo++;
			blinkingLED = 0x01;
			break;
		case blinkOff:
			timerTwo++;
			blinkingLED = 0x00;
			break;
		default:
			break;
	}

}

void combinedLEDsSM(){

	PORTB = ((blinkingLED << 3) + threeLEDs);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char button0;

	TimerOn();
	TimerSet(1);

    /* Insert your solution below */
    while (1) {
	threeLEDsSM();
	blinkingLEDsSM();
	combinedLEDsSM();

	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
