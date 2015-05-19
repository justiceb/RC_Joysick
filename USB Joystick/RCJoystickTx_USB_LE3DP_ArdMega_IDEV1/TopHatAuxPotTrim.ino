/*

Top Hat control - AuxPot 1&2 / Trim Modes

*/

char* MenuPanTiltMode[]={"        ", "AuxPot 1&2", "   Trim   ", "Top Hat Mode"};
int TopHatModeEEprom = 1;    // 1=AuxPot 1&2, 2=Trim

// AuxPot 1&2 / Trim Mode
void AuxPotTrimMode() {

    // AuxPot 1&2 / Trim Mode
	if (ModeDispSet == 11) {
	     LCDgoTo(2);
         lcd.print(MenuPanTiltMode[3]);
		 
		 if (DI_Onup_c == 1) {    // Trim Mode
		    DI_Onup_c = 0;
			buzzeractivate = 1;                  // activate buzzer
			TopHatModeEEprom = 1;
			TopHatMode = 1;
			Epromvar = TopHatModeEEprom;
			Address = 50;
            EEpromwriteDirect();
		 }
		
		 if (DI_Onup_b == 1) {    // AuxPot 1&2 Mode
		    DI_Onup_b = 0;
			buzzeractivate = 1;                  // activate buzzer
			TopHatModeEEprom = 0;
			TopHatMode = 0;
			Epromvar = TopHatModeEEprom;
			Address = 50;
            EEpromwriteDirect();
		 }
		 LCDgoTo(19);
         if (TopHatMode == 0) { lcd.print(MenuPanTiltMode[1]); }
		 if (TopHatMode == 1) { lcd.print(MenuPanTiltMode[2]); }
	}
}

// *********************** Setup **************************
void AuxPotTrimModeSetup () {
  Address = 50;
  EEpromreadDirect();
  TopHatModeEEprom = Epromvar;
  TopHatMode = TopHatModeEEprom;
  if (TopHatModeEEprom != 0 && TopHatModeEEprom != 1) {  // Set to default if out of range
	 TopHatModeEEprom = 0;   // default AuxPot 1&2 Mode
	 TopHatMode = TopHatModeEEprom;
	 Epromvar = TopHatModeEEprom;
	 Address = 50;
     EEpromwriteDirect();
  }
  
}