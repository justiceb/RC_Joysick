/*

AuxSw thumb & trigger set

*/

char* AuxSwitchThumb[]=  {"        ", "Mode = 100%", "Mode = 50% ", "Mode = 0%  ", "Aux Pot1 Thumb  "};
char* AuxSwitchTrigger[]={"        ", "Mode = 100%", "Mode = 50% ", "Mode = 0%  ", "Aux Pot2 Trigger"};

// AuxSw Channels
void AuxSwitchThumbSet() {

	if (ModeDispSet == 7) {    // AuxSw1 Thumb, 1=100%, 2=50%, 3=0%
		 LCDgoTo(0);  // top line
         lcd.print(AuxSwitchThumb[4]);
		 LCDgoTo(16);  // bottom line
         lcd.print(AuxSwitchThumb[AuxSW1EEprom]);
		 
		 if (DI_Onup_c == 1) {    // down
		    DI_Onup_c = 0;                                                  
			AuxSwThumb--;
			if (AuxSwThumb < 1) { AuxSwThumb = 1; } 
			buzzeractivate = 1;                  // activate buzzer			
			AuxSW1EEprom = AuxSwThumb;    
			Epromvar = AuxSW1EEprom;
			Address = 48;
            EEpromwriteDirect();
		 }
		
		 if (DI_Onup_b == 1) {    // up
		    DI_Onup_b = 0;
			AuxSwThumb++;
			if (AuxSwThumb > 3) { AuxSwThumb = 3; }
			buzzeractivate = 1;                  // activate buzzer
			AuxSW1EEprom = AuxSwThumb;
			Epromvar = AuxSW1EEprom;
			Address = 48;
            EEpromwriteDirect();
		 }		 
	}

	if (ModeDispSet == 8) {    // AuxSw2 Trigger, 1=100%, 2=50%, 3=0%
		 LCDgoTo(0);  // top line
         lcd.print(AuxSwitchTrigger[4]);
		 LCDgoTo(16);  // bottom line
         lcd.print(AuxSwitchTrigger[AuxSW2EEprom]);

		 if (DI_Onup_c == 1) {    // down
		    DI_Onup_c = 0;
			AuxSwTrigger--;
			if (AuxSwTrigger < 1) { AuxSwTrigger = 1; }
			buzzeractivate = 1;                  // activate buzzer
			AuxSW2EEprom = AuxSwTrigger;
			Epromvar = AuxSW2EEprom;
			Address = 49;
            EEpromwriteDirect();
		 }
		
		 if (DI_Onup_b == 1) {    // up
		    DI_Onup_b = 0;
			AuxSwTrigger++;
			if (AuxSwTrigger > 3) { AuxSwTrigger = 3; }
			buzzeractivate = 1;                  // activate buzzer
			AuxSW2EEprom = AuxSwTrigger;
			Epromvar = AuxSW2EEprom;
			Address = 49;
            EEpromwriteDirect();
		 }
		 
	}	
	
}

// *********************** Setup **************************
void AuxSwitchesSetup() {

  // Pull AuxSw1 setting from EEprom
  Address = 48;
  EEpromreadDirect();
  AuxSW1EEprom = Epromvar;
  AuxSwThumb = AuxSW1EEprom;
  if (AuxSW1EEprom != 1 && AuxSW1EEprom != 2 && AuxSW1EEprom != 3) {  // Set to default if out of range
	 AuxSW1EEprom = 1;              // default set to 100%
	 AuxSwThumb = AuxSW1EEprom;
	 Epromvar = AuxSW1EEprom;
	 Address = 48;
     EEpromwriteDirect();
  }  

  // Pull AuxSw2 setting from EEprom
  Address = 49;
  EEpromreadDirect();
  AuxSW2EEprom = Epromvar;
  AuxSwTrigger = AuxSW2EEprom;
  if (AuxSW2EEprom != 1 && AuxSW2EEprom != 2 && AuxSW2EEprom != 3) {  // Set to default if out of range
	 AuxSW2EEprom = 1;              // default set to 100%
	 AuxSwTrigger = AuxSW2EEprom;
	 Epromvar = AuxSW2EEprom;
	 Address = 49;
     EEpromwriteDirect();
  }  

}  
