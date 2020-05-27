
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
//
 static unsigned char currAmp = 0;

/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
	    detect_max_amp_state = DMAIdle;
            break;
        
	case DMAIdle:
            if(A7 | A6 | A5 | A4 | A3){ //if motion is detected, start recording
		    detect_max_amp_state = DMARead;
	    } else {
		    detect_max_amp_state = DMAIdle;
	    }
	    break;

	case DMARead:
	    if(!A7 & !A6 & !A5 & !A4 & !A3){
		    detect_max_amp_state = DMAIdle;
	    } else {
		    detect_max_amp_state = DMARead;
	    }
	    break;

        default:
            break;
    }

    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;

	case DMAIdle:
	   currAmp = 0;
	   maxAmp = 0;
	  break;
	case DMARead:
	  currAmp = (A7 << 4) + (A6 << 3) + (A5 << 2) + (A4 << 1) + A3;
	  if(currAmp > maxAmp){
		  maxAmp = currAmp;
	  }
	  break;
	   
        default:
            break;
    }
}
