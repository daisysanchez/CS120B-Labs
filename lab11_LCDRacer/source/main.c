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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*unsigned char GetKeypadKey() {
	//checks keys in col 1
	PORTC = 0xEF; //enable col 4 width 0, disable others with 1's
	asm("nop"); //add a delay to allow PORTC to stablizie before checking
	if(GetBit(~PINC, 0) == 0) {return('1');}
	if(GetBit(~PINC, 1) == 0) {return('4');}
	if(GetBit(~PINC, 2) == 0) {return('7');}
	if(GetBit(~PINC, 3) == 0) {return('*');}

	//check keys in col 2
	PORTC = 0xDF; //enable col 5 with 0, disable others with 1's
	asm("nop"); //add a delay to allow PORTC to stabilize before checking
	if(GetBit(PINC, 0) == 0) {return('2');}	
	if(GetBit(PINC, 1) == 0) {return('5');}
	if(GetBit(PINC, 3) == 0) {return('8');}
	if(GetBit(PINC, 4) == 0) {return('0');}
	
	//checks keys in col 3
	PORTC = 0xBF; //enable col 6 with 0, disables other's with 1's
	asm("nop");
	if(GetBit(PINC, 0) == 0) {return('3');}
	if(GetBit(PINC, 1) == 0) {return('6');}
	if(GetBit(PINC, 2) == 0) {return('9');}
	if(GetBit(PINC, 3) == 0) {return('#');}
	
	//checks keys in col 4
	PORTC = 0x8F;
	asm("nop");
	if(GetBit(PINC, 0) == 0) {return('A');}
	if(GetBit(PINC, 1) == 0) {return('B');}
	if(GetBit(PINC, 2) == 0) {return('C');}
	if(GetBit(PINC, 3) == 0) {return('D');}

	return('\0'); //default value

}*/


int main(void) {
	unsigned char x;

    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
    /* Insert your solution below */
    while (1) {
	x = GetKeypadKey();

	switch(x){
		case '\0': PORTB = 0x1F; break; //all 5 leds on
		case '1': PORTB = 0x01; break; //hex equivalent
		case '2': PORTB = 0x02; break;
		case '3': PORTB = 0x03; break;
		case '4': PORTB = 0x04; break;
		case '5': PORTB = 0x05; break;
		case '6': PORTB = 0x06; break;
		case '7': PORTB = 0x07; break;
		case '8': PORTB = 0x08; break;
		case '9': PORTB = 0x09; break;
		case '0': PORTB = 0x00; break;
		case 'A': PORTB = 0x0A; break;
		case 'B': PORTB = 0x0B; break;
		case 'C': PORTB = 0x0C; break;
		case 'D': PORTB = 0x0D; break;
		case '*': PORTB = 0x0E; break;
		case '#': PORTB = 0x0F; break;
		default: PORTB = 0x1B; break; //should nevewr occur, middle led off
	}
    }
    return 1;
}
