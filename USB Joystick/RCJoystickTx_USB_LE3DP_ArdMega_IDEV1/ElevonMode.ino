/*

Elevon Mode

*/

char* MenuWingMode[]={"        ", "Off", "On ", "Mode = "};
int ElevonModeEEprom = 1, ExpoModeAELEEprom = 1, ExpoModeELEEEprom = 1, ExpoModeRUDEEprom = 1, InvModeAELEEprom = 1, InvModeELEEEprom = 1, InvModeRUDEEprom = 1, InvModeTHREEprom = 1;

// Elevon Mode
void ElevonModeSet() {

    // Elevon Mode setting, 1=OFF, 2=ON
	if (ModeDispSet == 4) {
	     LCDgoTo(16);
         lcd.print(MenuWingMode[3]);
		 LCDgoTo(23);
         lcd.print(MenuWingMode[ElevonModeEEprom]);
		 LCDgoTo(0);
         lcd.print(MenuDisplay[4]);
		 
		 if (DI_Onup_c == 1) {    // Elevon Mode Set ON
		    DI_Onup_c = 0;
			ElevonMode = 1;
			buzzeractivate = 1;                  // activate buzzer
			MenuDisplay[1] = "AE1 Trim";
	        MenuDisplay[2] = "AE2 Trim";
			ElevonModeEEprom = 2;
			Epromvar = ElevonModeEEprom;
			Address = 20;
            EEpromwriteDirect();
		 }
		
		 if (DI_Onup_b == 1) {    // Elevon Mode Set OFF
		    DI_Onup_b = 0;
			ElevonMode = 0;
			buzzeractivate = 1;                  // activate buzzer
			MenuDisplay[1] = "AEL Trim";
	        MenuDisplay[2] = "ELE Trim";
			ElevonModeEEprom = 1;
			Epromvar = ElevonModeEEprom;
			Address = 20;
            EEpromwriteDirect();
		 }
	}
	
}

// *********************** Setup **************************
void ElevonModeSetup () {
 Address = 20;
 EEpromreadDirect();
 ElevonModeEEprom = Epromvar; 
 if (ElevonModeEEprom != 1 && ElevonModeEEprom != 2) {  // Set to default if out of range
	 ElevonModeEEprom = 1;
	 Epromvar = ElevonModeEEprom;
	 Address = 20;
     EEpromwriteDirect();
  }
  if (ElevonModeEEprom == 2) {  // Setup Elevon mode
     MenuDisplay[1] = "AE1 Trim";
	 MenuDisplay[2] = "AE2 Trim";
	 ElevonMode = 1;
  }
}
