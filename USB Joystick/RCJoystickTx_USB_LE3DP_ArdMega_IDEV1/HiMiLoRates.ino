/*

HI/LO/MID Rates

*/

char* MenuRatesHIMIDLO[]={"        ", "LOW ", "MID ", "HIGH"};

// Switch Rates
void HiMiLoRates() {

    if (DI_Onup_c == 1 && ModeDispSet == 0) {      // LO/MI/HI selection & save
	    DI_Onup_c = 0;  // reset onup
		buzzeractivate = 1;         // activate buzzer
		RatesHIMIDLOEEprom = RatesHIMIDLOEEprom + 1;
		ChangeModeHIMIDLO = 1;
		if (RatesHIMIDLOEEprom >= 4) {
		   RatesHIMIDLOEEprom = 1;
		}
		Epromvar = RatesHIMIDLOEEprom;
		Address = 0;
        EEpromwriteDirect();
    }

    if (DI_Onup_b == 1 && ModeDispSet == 0) {      // LO/MI/HI selection & save
	    DI_Onup_b = 0;  // reset onup
		buzzeractivate = 1;         // activate buzzer
		RatesHIMIDLOEEprom = RatesHIMIDLOEEprom - 1;
		ChangeModeHIMIDLO = 1;
		if (RatesHIMIDLOEEprom <= 0) {
		   RatesHIMIDLOEEprom = 3;
		}
		Epromvar = RatesHIMIDLOEEprom;
		Address = 0;
        EEpromwriteDirect();
    }	
	
	if (ModeDispSet == 0) {     // LO/MI/HI Rates var set
        if (RatesHIMIDLOEEprom == 1) {  // LO rate
	     EpromPointer = 0;
	     LCDgoTo(16);
         lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]);
        }
        if (RatesHIMIDLOEEprom == 2) {  // MID rate
	    EpromPointer = 3; 
	    LCDgoTo(16);
        lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]); 
        }
        if (RatesHIMIDLOEEprom == 3) {  // HI rate
	    EpromPointer = 6; 
	    LCDgoTo(16);
        lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]);
        }	
	}	
	
    if (RatesHIMIDLOEEprom == 3 && ModeDispSet == 0 && ChangeModeHIMIDLO == 1) {      // HI rate
	    ChangeModeHIMIDLO = 0;
		LCDgoTo(16);
        lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]); 
	    EpromPointer = 6;  // Set pointer for EEprom trim settings storage
		
		Epromvar = TrAelEEprom;
        Offset = 0;
        EEpromread();
        TrAelEEprom = Epromvar;
		Epromvar = TrEleEEprom;
        Offset = 3;
        EEpromread();
        TrEleEEprom = Epromvar;
        Epromvar = TrRudEEprom;
        Offset = 6;
        EEpromread();
        TrRudEEprom = Epromvar; 
		
		RateMult = RateMultHI;
	}
	
    if (RatesHIMIDLOEEprom == 2 && ModeDispSet == 0 && ChangeModeHIMIDLO == 1) {      // MID rate
	    ChangeModeHIMIDLO = 0;
		LCDgoTo(16);
        lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]); 
	    EpromPointer = 3;  // Set pointer for EEprom trim settings storage
		
	    Epromvar = TrAelEEprom;
        Offset = 0;
        EEpromread();
        TrAelEEprom = Epromvar;
		Epromvar = TrEleEEprom;
        Offset = 3;
        EEpromread();
        TrEleEEprom = Epromvar;
        Epromvar = TrRudEEprom;
        Offset = 6;
        EEpromread();
        TrRudEEprom = Epromvar; 

		RateMult = RateMultMI;
    }
	
    if (RatesHIMIDLOEEprom == 1 && ModeDispSet == 0 && ChangeModeHIMIDLO == 1) {      // LO rate
	    ChangeModeHIMIDLO = 0;
		LCDgoTo(16);
		lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]); 
	    EpromPointer = 0;  // Set pointer for EEprom trim settings storage
		
		Epromvar = TrAelEEprom;
        Offset = 0;
        EEpromread();
        TrAelEEprom = Epromvar;
		Epromvar = TrEleEEprom;
        Offset = 3;
        EEpromread();
        TrEleEEprom = Epromvar;
        Epromvar = TrRudEEprom;
        Offset = 6;
        EEpromread();
        TrRudEEprom = Epromvar; 

		RateMult = RateMultLO;
    }
}

// *********************** Setup **************************
void HiMiLoRatesSetup() {

  // Set LO rate default if out of range
  Address = 0;
  EEpromreadDirect();
  RatesHIMIDLOEEprom = Epromvar; 

  if (RatesHIMIDLOEEprom <= 0 || RatesHIMIDLOEEprom >= 4) {  
	 RatesHIMIDLOEEprom = 1;
	 EpromPointer = 0;
  } 
   
  if (RatesHIMIDLOEEprom == 1) {  // LO rate
	 EpromPointer = 0;
	 LCDgoTo(16);
     lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]);
	 RateMult = RateMultLO;
  }
  if (RatesHIMIDLOEEprom == 2) {  // MID rate
	 EpromPointer = 3; 
	 LCDgoTo(16);
     lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]);	
     RateMult = RateMultMI;	 
  }
  if (RatesHIMIDLOEEprom == 3) {  // HI rate
	 EpromPointer = 6; 
	 LCDgoTo(16);
     lcd.print(MenuRatesHIMIDLO[RatesHIMIDLOEEprom]); 
	 RateMult = RateMultHI;
  }
  
  Epromvar = TrAelEEprom;
  Offset = 0;
  EEpromread();
  TrAelEEprom = Epromvar;
  Epromvar = TrEleEEprom;
  Offset = 3;
  EEpromread();
  TrEleEEprom = Epromvar;
  Epromvar = TrRudEEprom;
  Offset = 6;
  EEpromread();
  TrRudEEprom = Epromvar;  
}  
  