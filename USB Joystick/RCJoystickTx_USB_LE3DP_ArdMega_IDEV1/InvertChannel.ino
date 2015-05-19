/*

Invert Channels

*/

char* InvertMode[]={"  ", "N", "Y", "Inv.", "AE", "EL", "RU", "TH"};
int Reverse = 1;

// Invert Channel Selection
void InvertChannel() {

	if (ModeDispSet == 6) {

	 InvertSelectionDisplay();

	 if (DI_Onup_c == 1) {    // Advance cursor
	     DI_Onup_c = 0;
	     buzzeractivate = 1;                  // activate buzzer
	     Reverse = Reverse + 1;               // Flash selected channel
	     if (Reverse >= 5) { Reverse = 1; }
	 }

	 if (DI_Onup_b == 1) {    // update target INV channel
	     DI_Onup_b = 0;
	     buzzeractivate = 1;                  // activate buzzer
		 if (Reverse == 1) {
			ReverseAeleron = !ReverseAeleron;
			InvModeAELEEprom = ReverseAeleron + 1;
		    Epromvar = InvModeAELEEprom;
		    Address = 32;
            EEpromwriteDirect();
		 }
		 if (Reverse == 2) {
			ReverseElevator = !ReverseElevator;
			InvModeELEEEprom = ReverseElevator + 1;
		    Epromvar = InvModeELEEEprom;
		    Address = 33;
            EEpromwriteDirect();			
		 }
		 if (Reverse == 3) {
			ReverseRudder = !ReverseRudder;
			InvModeRUDEEprom = ReverseRudder + 1;
		    Epromvar = InvModeRUDEEprom;
		    Address = 34;
            EEpromwriteDirect();
		 }
		 if (Reverse == 4) {
			ReverseThrottle = !ReverseThrottle;
			InvModeTHREEprom = ReverseThrottle + 1;
		    Epromvar = InvModeTHREEprom;
		    Address = 35;
            EEpromwriteDirect();			
		 }
	 }
	}
}

void InvertSelectionDisplay() {

		LCDgoTo(0); lcd.print(InvertMode[3]);

		// Display Y or N
		if (ReverseAeleron == 1) {
			LCDgoTo(21); lcd.print(InvertMode[2]);
		} else {
			LCDgoTo(21); lcd.print(InvertMode[1]);
		}
		if (ReverseElevator == 1) {
			LCDgoTo(24); lcd.print(InvertMode[2]);
		} else {
			LCDgoTo(24); lcd.print(InvertMode[1]);
		}		
		if (ReverseRudder == 1) {
			LCDgoTo(27); lcd.print(InvertMode[2]);
		} else {
			LCDgoTo(27); lcd.print(InvertMode[1]);
		}		
		if (ReverseThrottle == 1) {
			LCDgoTo(30); lcd.print(InvertMode[2]);
		} else {
			LCDgoTo(30); lcd.print(InvertMode[1]);
		}		

		// Flash AE, EL, RU, TH
		if (Reverse == 1) {
			if (slowflag == 1) { LCDgoTo(5); lcd.print(InvertMode[4]); }
			if (slowflag == 0) { LCDgoTo(5); lcd.print(InvertMode[0]); }
	    } else {
		LCDgoTo(5); lcd.print(InvertMode[4]);
		}
	    if (Reverse == 2) {
			if (slowflag == 1) { LCDgoTo(8); lcd.print(InvertMode[5]); }
			if (slowflag == 0) { LCDgoTo(8); lcd.print(InvertMode[0]); }
	    } else {
		LCDgoTo(8); lcd.print(InvertMode[5]);
		}
	    if (Reverse == 3) {
			if (slowflag == 1) { LCDgoTo(11); lcd.print(InvertMode[6]); }
			if (slowflag == 0) { LCDgoTo(11); lcd.print(InvertMode[0]); }
	    } else {
		LCDgoTo(11); lcd.print(InvertMode[6]);
		}
	    if (Reverse == 4) {
			if (slowflag == 1) { LCDgoTo(14); lcd.print(InvertMode[7]); }
			if (slowflag == 0) { LCDgoTo(14); lcd.print(InvertMode[0]); }
	    } else {
		LCDgoTo(14); lcd.print(InvertMode[7]);
		}		 
}


// *********************** Setup **************************
void InvertChannelsSetup() {

  // Pull AEL Invert Mode from EEprom
  Address = 32;
  EEpromreadDirect();
  InvModeAELEEprom = Epromvar; 
  if (InvModeAELEEprom != 1 && InvModeAELEEprom != 2) {  // Set to default if out of range
	 InvModeAELEEprom = 1;
	 Epromvar = InvModeAELEEprom;
	 Address = 32;
     EEpromwriteDirect();
  }  
  if (InvModeAELEEprom == 2) {  // Setup AEL Invert mode
	 ReverseAeleron = 1;
  } else {
     ReverseAeleron = 0;
  }

  // Pull ELE Invert Mode from EEprom
  Address = 33;
  EEpromreadDirect();
  InvModeELEEEprom = Epromvar; 
  if (InvModeELEEEprom != 1 && InvModeELEEEprom != 2) {  // Set to default if out of range
	 InvModeELEEEprom = 1;
	 Epromvar = InvModeELEEEprom;
	 Address = 33;
     EEpromwriteDirect();
  }  
  if (InvModeELEEEprom == 2) {  // Setup ELE Invert mode
	 ReverseElevator = 1;
  } else {
     ReverseElevator = 0;
  }  

  // Pull RUD Invert Mode from EEprom
  Address = 34;
  EEpromreadDirect();
  InvModeRUDEEprom = Epromvar; 
  if (InvModeRUDEEprom != 1 && InvModeRUDEEprom != 2) {  // Set to default if out of range
	 InvModeRUDEEprom = 1;
	 Epromvar = InvModeRUDEEprom;
	 Address = 34;
     EEpromwriteDirect();
  }  
  if (InvModeRUDEEprom == 2) {  // Setup ELE Invert mode
	 ReverseRudder = 1;
  } else {
     ReverseRudder = 0;
  }  
  
  // Pull THR Invert Mode from EEprom
  Address = 35;
  EEpromreadDirect();
  InvModeTHREEprom = Epromvar; 
  if (InvModeTHREEprom != 1 && InvModeTHREEprom != 2) {  // Set to default if out of range
	 InvModeTHREEprom = 1;
	 Epromvar = InvModeTHREEprom;
	 Address = 35;
     EEpromwriteDirect();
  }  
  if (InvModeTHREEprom == 2) {  // Setup ELE Invert mode
	 ReverseThrottle = 1;
  } else {
     ReverseThrottle = 0;
  }  
}  
