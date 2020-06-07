/*	Author: <your name>
 *	Lab Section:
 *  Exam #2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

/* SM state declarations --- fill in as needed */
typedef enum ping_states { PInit, POn, POff                                         } ping_states;
typedef enum detect_eq_states { DEQInit, DEQHigh, DEQLow, DEQEase                                    } detect_eq_states;
typedef enum detect_max_amp_states { DMAInit, DMARead, DMAIdle                              } detect_max_amp_states;
typedef enum detect_zc_states { DZCInit,                                    } detect_zc_states;
typedef enum transmit_states {TInit,                                        } transmit_states;

/* shared variables --- fill in as needed */

////////////input

unsigned char A0;
unsigned char A1;
unsigned char A2;
unsigned char A3;
unsigned char A4;
unsigned char A5;
unsigned char A6;
unsigned char A7;


unsigned char ping = 0; //helps to set B0

//detect_eq
unsigned char earthquakeEndCnt = 0;
unsigned char earthquakeDetected = 0;

//max amp
unsigned char maxAmp = 0;

/* state variables --- do not alter */
ping_states ping_state;
detect_eq_states detect_eq_state;
detect_max_amp_states detect_max_amp_state;
detect_zc_states detect_zc_state;
transmit_states transmit_state;

/* SM definitions --- complete each task as a SM in the appropriate file.
 * Alternatively, you can remove the #include statement and insert your
 *   SM implementation directly. 
 */
#include "ping.h"
#include "detect_eq.h"
#include "detect_max_amp.h"
#include "detect_zc.h"
#include "transmit.h"


/* main function --- do not alter */
int main(void) {
    /* DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    // Common period for all tasks set to 100ms
    TimerSet(100);
    TimerOn();

    // init state vars
    ping_state = PInit;
    detect_eq_state = DEQInit;
    detect_max_amp_state = DMAInit;
    detect_zc_state = DZCInit;
    transmit_state = TInit;

    while (1) {
	//motion direction
	A0 = ~PINA & 0x01;	
	A1 = ~PINA & 0x02;
	A2 = ~PINA & 0x04;

	//motion amplitude
	A3 = ~PINA & 0x08;
	A4 = ~PINA & 0x10;
	A5 = ~PINA & 0x20;
	A6 = ~PINA & 0x40;
	A7 = ~PINA & 0x80;

	PORTB = (ping) + (earthquakeDetected << 1) + (maxAmp << 3);

        Ping();
        Detect_EQ();
        Detect_Max_Amp();
        Detect_ZC();
        Transmit();
        while (!TimerFlag) { }
        TimerFlag = 0;
    }
    return 1;
}
