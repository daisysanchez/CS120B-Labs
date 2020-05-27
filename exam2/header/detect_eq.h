//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here
	    detect_eq_state = DEQLow;
            break;

	case DEQLow:
	    if(A7 | A6 | A5 | A4 | A3){ //if motion is detected
		    detect_eq_state = DEQHigh;
	    } else {
		    detect_eq_state = DEQLow;
	    }

	    break;
	
	case DEQHigh:
	    if(!A7 & !A6 & !A5 & !A4 & !A3){ //if no motion detected
		    earthquakeEndCnt = 0;
		    detect_eq_state = DEQEase;
	    } else {
		    detect_eq_state = DEQHigh;
	    }

	    break;

	case DEQEase:
	    if(earthquakeEndCnt == 10){ //if gone still for one second, go back to low
		    earthquakeEndCnt = 0; //reset counter
		    detect_eq_state = DEQLow;
	    } else if(A7 | A6 | A5 | A3 | A2 | A1){ //if motion is once again detected, go back to high
		    earthquakeEndCnt = 0;
		    detect_eq_state = DEQHigh;
	    } else {
		    detect_eq_state = DEQEase;
           }

	    break;

        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case DEQLow:
	  //  PORTB = PORTB & 0xFD; //sets B1 to 0
            earthquakeDetected = 0;
	    break;
	case DEQHigh:
	    earthquakeDetected = 1;
	  //  PORTB = PORTB | 0x02; //sets B1 to 1
	    break;
	case DEQEase:
	    earthquakeDetected = 1;
	    earthquakeEndCnt++;
	    break;
        default:
            break;
    }
}
