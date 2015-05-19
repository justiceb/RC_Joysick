/*

Timer Display

*/

char* MenuTimerMode[]={"        ", "Timer   "};
int DI_Onup_c_latch = 0;
unsigned char DItemp_c_latch = 0;

// Timer Mode
void TimerDisplay() {

    if (ModeDispSet == 13) {

		LCDgoTo(3); lcd.print(MenuTimerMode[1]); 

		if (minflag < 10) {
		    LCDgoTo(19); lcd.print("0");
		    LCDgoTo(20); lcd.print(minflag);
		}
		if (minflag >= 10) {
		    LCDgoTo(19); lcd.print(minflag);
		}		

		LCDgoTo(21); lcd.print(":");

		if (secflag < 10) {
		    LCDgoTo(22); lcd.print("0");
		    LCDgoTo(23); lcd.print(secflag);
		}
		if (secflag >= 10) {
		    LCDgoTo(22); lcd.print(secflag);
		}	
	
        if (DI_Onup_c == 1) {           // Throttle inhibit/pause timer
            DI_Onup_c = 0;		
			DI_Onup_c_latch = !DI_Onup_c_latch;
			if (DI_Onup_c_latch == 1) {
               TimerInhibit = 1;
			} else {
			   TimerInhibit = 0;
			   LCDgoTo(24); lcd.print(" ");
			}
		}
		if (ReverseThrottle == 0) {
			if (TimerInhibit == 1) {
				LCDgoTo(10); lcd.print("Inh");
				LCDgoTo(26); lcd.print("On ");
				if (AI_Throt < (pulseMin + 10)) { LCDgoTo(24); lcd.print("*"); }
				if (AI_Throt >= (pulseMin + 11)) { LCDgoTo(24); lcd.print(" "); }			
				} else {
				LCDgoTo(10); lcd.print("Inh");
				LCDgoTo(26); lcd.print("Off");
			}
		}
		if (ReverseThrottle == 1) {
			if (TimerInhibit == 1) {
				LCDgoTo(10); lcd.print("Inh");
				LCDgoTo(26); lcd.print("On ");
				if (AI_Throt > (pulseMax - 10)) { LCDgoTo(24); lcd.print("*"); }
				if (AI_Throt <= (pulseMax - 11)) { LCDgoTo(24); lcd.print(" "); }			
				} else {
				LCDgoTo(10); lcd.print("Inh");
				LCDgoTo(26); lcd.print("Off");
			}
		}		
		
        if (DI_Onup_b == 1) {           // start/stop timer
		    DI_Onup_b = 0;
		    buzzeractivate = 1;         // activate buzzer
		    if (TimerStart == 0) {      // start timer
			   TimerStart = 1;
		       } else {                 // stop timer
		       secflag = 0;
			   minflag = 0;
			   TimerStart = 0;
			   LCDgoTo(19); lcd.print("0");
			   LCDgoTo(20); lcd.print("0");
			   LCDgoTo(22); lcd.print("0");
			   LCDgoTo(23); lcd.print("0");
		    }
        }			
	}	
}
