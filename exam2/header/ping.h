
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit:
		ping_state = POn;
            break;

	case POn:
	    ping_state = POff;
	    break;

	case POff:
	    ping_state = POn;
	    break;

        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;
	case POn:
	    ping = 1;
	  //  PORTB = PORTB | 0x01; //sets B0 to on
	    break;
	case POff:
	    ping = 0;
	  //  PORTB = PORTB & 0xFE;
	    break;
        default:
            break;
    }
}
