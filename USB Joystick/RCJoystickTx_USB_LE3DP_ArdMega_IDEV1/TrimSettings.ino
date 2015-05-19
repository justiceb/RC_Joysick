/*

AEL/ELE/RUD Trim

*/

char* MenuHIMIDLO[]={"  ", "LOW ", "MID ", "HIGH", "Trim", "AE", "EL", "RU"};
int TrEprom;

// Trim Settings
void TrimSettings() {

    if (ModeDispSet == 1 || ModeDispSet == 2 || ModeDispSet == 3) {    // AEL,ELE,RUD Trim setting
	    if (ModeDispSet == 1) {
		    TrEprom = TrAelEEprom;
		    Offset = 0;
		}
		if (ModeDispSet == 2) {
		    TrEprom = TrEleEEprom;
            Offset = 3;
		}
		if (ModeDispSet == 3) {
		    TrEprom = TrRudEEprom;
            Offset = 6;
		}
	
	    // Write AEL, ELE or RUD to LCD
		LCDgoTo(16);
        lcd.print(MenuHIMIDLO[4]);
		LCDgoTo(0);
        lcd.print(MenuHIMIDLO[RatesHIMIDLOEEprom]);  // LO, MI or HI

		// Flash AE, EL, RU
		if (ModeDispSet == 1) {  // AE
			if (slowflag == 1) { LCDgoTo(5); lcd.print(MenuHIMIDLO[5]); }
			if (slowflag == 0) { LCDgoTo(5); lcd.print(MenuHIMIDLO[0]); }
	    } else {
		LCDgoTo(5); lcd.print(MenuHIMIDLO[5]);
		}
		if (ModeDispSet == 2) {  // EL
			if (slowflag == 1) { LCDgoTo(9); lcd.print(MenuHIMIDLO[6]); }
			if (slowflag == 0) { LCDgoTo(9); lcd.print(MenuHIMIDLO[0]); }
	    } else {
		LCDgoTo(9); lcd.print(MenuHIMIDLO[6]);
		}
		if (ModeDispSet == 3) {  // RU
			if (slowflag == 1) { LCDgoTo(13); lcd.print(MenuHIMIDLO[7]); }
			if (slowflag == 0) { LCDgoTo(13); lcd.print(MenuHIMIDLO[0]); }
	    } else {
		LCDgoTo(13); lcd.print(MenuHIMIDLO[7]);
		}		

		LCDgoTo(21); lcd.print(TrAelEEprom); lcd.print(" ");
		LCDgoTo(25); lcd.print(TrEleEEprom); lcd.print(" ");
		LCDgoTo(29); lcd.print(TrRudEEprom); lcd.print(" ");

		// Stick Trim
		if (TrEprom > trimMax) {   // If more than trimMax (i.e. brand new install or corrupt) then reset to zero
		    TrEprom = 0;
			Epromvar = TrEprom;
            EEpromwrite();
		}
		
		if (TrEprom < trimMin) {   // If lower than trimMin (i.e. brand new install or corrupt) then reset to zero
		    TrEprom = 0;
			Epromvar = TrEprom;
            EEpromwrite();
		}
		
		if (DI_Onup_c == 1 && TrEprom < trimMax) {    // panel button trim adj up
		    DI_Onup_c = 0;
		    buzzeractivate = 1;                  // activate buzzer
			TrEprom++;
			if (TrEprom > trimMax) { TrEprom = trimMax; }
			Epromvar = TrEprom;
            EEpromwrite();
		}
		
		if (DI_Onup_b == 1 && TrEprom > trimMin) {    // panel button trim adj down
		    DI_Onup_b = 0;
		    buzzeractivate = 1;                  // activate buzzer
			TrEprom--;
			if (TrEprom < trimMin) { TrEprom = trimMin; }
			Epromvar = TrEprom;
            EEpromwrite();
		}

		// Reload vars
        if (ModeDispSet == 1) {TrAelEEprom = TrEprom; }
		if (ModeDispSet == 2) {TrEleEEprom = TrEprom; }
		if (ModeDispSet == 3) {TrRudEEprom = TrEprom; }
    }
	
    // Thumb stick trim
	if (TopHatMode == 1) {
		if (DI_Val[5] == 0 && TrAelEEprom < trimMax) {     // Ael trim up via thumb stick
				buzzeractivate = 2;         // activate buzzer
				TrAelEEprom++;
				if (TrAelEEprom > trimMax) { TrAelEEprom = trimMax; }
				Epromvar = TrAelEEprom;
				Offset = 0;
				EEpromwrite();
		}
		if (DI_Val[4] == 0 && TrAelEEprom > trimMin) {     // Ael trim down via thumb stick
				buzzeractivate = 2;         // activate buzzer
				TrAelEEprom--;
				if (TrAelEEprom < trimMin) { TrAelEEprom = trimMin; }
				Epromvar = TrAelEEprom;
				Offset = 0;
				EEpromwrite();
		}	
		if (DI_Val[6] == 0 && TrEleEEprom < trimMax) {     // Ele trim up via thumb stick
				buzzeractivate = 2;         // activate buzzer
				TrEleEEprom++;
				if (TrEleEEprom > trimMax) { TrEleEEprom = trimMax; }
				Epromvar = TrEleEEprom;
				Offset = 3;
				EEpromwrite();
		}
		if (DI_Val[7] == 0 && TrEleEEprom > trimMin) {     // Ele trim down via thumb stick
				buzzeractivate = 2;         // activate buzzer
				TrEleEEprom--;
				if (TrEleEEprom < trimMin) { TrEleEEprom = trimMin; }
				Epromvar = TrEleEEprom;
				Offset = 3;
				EEpromwrite();
		}
    }	
	
}


