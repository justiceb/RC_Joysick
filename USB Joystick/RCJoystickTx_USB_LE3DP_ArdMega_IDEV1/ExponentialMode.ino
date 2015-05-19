/*

Exponential Mode

*/

char* ExponentialMode[]={"  ", "N", "Y", "Expo.", "AE", "EL", "RU"};
int ExpoSet = 1;

// Exponential Modes
void ExpoMode() {

	if (ModeDispSet == 5) {

	 ExpoSelectionDisplay();

	 if (DI_Onup_c == 1) {    // Advance cursor
	     DI_Onup_c = 0;
	     buzzeractivate = 1;                  // activate buzzer
	     ExpoSet = ExpoSet + 1;               // Flash selected channel
	     if (ExpoSet >= 4) { ExpoSet = 1; }
	 }

	 if (DI_Onup_b == 1) {    // update target EXPO channel
	     DI_Onup_b = 0;
	     buzzeractivate = 1;                  // activate buzzer
		 if (ExpoSet == 1) {
			ExpoModeAEL = !ExpoModeAEL;
			ExpoModeAELEEprom = ExpoModeAEL + 1;
		    Epromvar = ExpoModeAELEEprom;
		    Address = 22;
            EEpromwriteDirect();
		 }
		 if (ExpoSet == 2) {
			ExpoModeELE = !ExpoModeELE;
			ExpoModeELEEEprom = ExpoModeELE + 1;
		    Epromvar = ExpoModeELEEEprom;
		    Address = 23;
            EEpromwriteDirect();			
		 }
		 if (ExpoSet == 3) {
			ExpoModeRUD = !ExpoModeRUD;
			ExpoModeRUDEEprom = ExpoModeRUD + 1;
		    Epromvar = ExpoModeRUDEEprom;
		    Address = 24;
            EEpromwriteDirect();
		 }
	 }
	}

}

// ExponentialSelection Display
void ExpoSelectionDisplay() {

		LCDgoTo(0); lcd.print(ExponentialMode[3]);

		// Display Y or N
		if (ExpoModeAEL == 1) {
			LCDgoTo(22); lcd.print(ExponentialMode[2]);
		} else {
			LCDgoTo(22); lcd.print(ExponentialMode[1]);
		}
		if (ExpoModeELE == 1) {
			LCDgoTo(25); lcd.print(ExponentialMode[2]);
		} else {
			LCDgoTo(25); lcd.print(ExponentialMode[1]);
		}		
		if (ExpoModeRUD == 1) {
			LCDgoTo(28); lcd.print(ExponentialMode[2]);
		} else {
			LCDgoTo(28); lcd.print(ExponentialMode[1]);
		}		

		// Flash AE, EL, RU
		if (ExpoSet == 1) {
			if (slowflag == 1) { LCDgoTo(6); lcd.print(ExponentialMode[4]); }
			if (slowflag == 0) { LCDgoTo(6); lcd.print(ExponentialMode[0]); }
	    } else {
		LCDgoTo(6); lcd.print(ExponentialMode[4]);
		}
	    if (ExpoSet == 2) {
			if (slowflag == 1) { LCDgoTo(9); lcd.print(ExponentialMode[5]); }
			if (slowflag == 0) { LCDgoTo(9); lcd.print(ExponentialMode[0]); }
	    } else {
		LCDgoTo(9); lcd.print(ExponentialMode[5]);
		}
	    if (ExpoSet == 3) {
			if (slowflag == 1) { LCDgoTo(12); lcd.print(ExponentialMode[6]); }
			if (slowflag == 0) { LCDgoTo(12); lcd.print(ExponentialMode[0]); }
	    } else {
		LCDgoTo(12); lcd.print(ExponentialMode[6]);
		}
	 
}


// *********************** Setup **************************
void ExpoModeSetup () {
  Address = 22;
  EEpromreadDirect();
  ExpoModeAELEEprom = Epromvar; 
  if (ExpoModeAELEEprom != 1 && ExpoModeAELEEprom != 2) {  // Set to default if out of range
	 ExpoModeAELEEprom = 1;
	 Epromvar = ExpoModeAELEEprom;
	 Address = 22;
     EEpromwriteDirect();
  }
  if (ExpoModeAELEEprom == 2) { // Setup AEL Expo mode 
	 ExpoModeAEL = 1;
  } else {
     ExpoModeAEL = 0;
  }
  
  Address = 23;
  EEpromreadDirect();
  ExpoModeELEEEprom = Epromvar; 
  if (ExpoModeELEEEprom != 1 && ExpoModeELEEEprom != 2) {  // Set to default if out of range
	 ExpoModeELEEEprom = 1;
	 Epromvar = ExpoModeELEEEprom;
	 Address = 23;
     EEpromwriteDirect();
  }
  if (ExpoModeELEEEprom == 2) { // Setup ELE Expo mode 
	 ExpoModeELE = 1;
  } else {
     ExpoModeELE = 0;
  } 
  
  Address = 24;
  EEpromreadDirect();
  ExpoModeRUDEEprom = Epromvar; 
  if (ExpoModeRUDEEprom != 1 && ExpoModeRUDEEprom != 2) {  // Set to default if out of range
	 ExpoModeRUDEEprom = 1;
	 Epromvar = ExpoModeRUDEEprom;
	 Address = 24;
     EEpromwriteDirect();
  }
  if (ExpoModeRUDEEprom == 2) { // Setup RUD Expo mode 
	 ExpoModeRUD = 1;
  } else {
     ExpoModeRUD = 0;
  }     
}