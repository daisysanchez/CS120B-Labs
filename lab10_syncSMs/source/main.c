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


//cycles through pb0...pb2
void threeLEDsSM(){
	switch(stateOne){
		case startOne:
			stateOne = led0;
			break;
		case led0:
			stateOne = led1;
			break;
		case led1:
			stateOne = led2;
			break;
		case led2:
			stateOne = led0;
			break;
		default:
			break;
	}

	switch(stateOne){
		case startOne:
			break;
		case led0:
			threeLEDs = 0x01;
			break;
		case led1:
			threeLEDs = 0x02;
			break;
		case led2:
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
			stateTwo = blinkOff;
			break;
		case blinkOff:
			stateTwo = blinkOn;
			break;
		default:
			break;	
	}

	switch(stateTwo){
		case startTwo:
			break;
		case blinkOn:
			blinkingLED = 0x01;
			break;
		case blinkOff:
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
	TimerSet(1000);

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
