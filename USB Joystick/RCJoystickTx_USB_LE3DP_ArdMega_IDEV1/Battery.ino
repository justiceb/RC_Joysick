/*

Battery Monitor

*/

int DI_Onup_e_int;
int DI_Onup_f_int;
int AI_Batte_percent = 0;
int AI_Battefloat = 0;
float AI_Batte;
float LipoMin = 14.8;       // Minimum battery voltage (alarm)
float BatteryMult = 5;  // Scale the analogue input down to battery voltage. Value depends on voltage divider resistors used.
						    // 5.6k & 1k resistors should give 2.2v at the input for 12.6v battery voltage.

void batterymonitor_auxpot() {

    AI_Batte = AI_Val[5] * BatteryMult * 5/1024;

	if (AI_Batte > LipoMin) {            // Compare battery with Lipo alarm setting
        digitalWrite(outPinBuzz, LOW);   // Turn off buzzer
    }
    if (AI_Batte < LipoMin && slooowflag == 1) {
	    digitalWrite(outPinBuzz, HIGH);  // Turn on buzzer
    } else {
	    digitalWrite(outPinBuzz, LOW);   // Turn off buzzer
	}
	
	AI_Battefloat = AI_Batte * 100;      // map doesn't work with float, so mult x100 gains 2 dp's to get around this
	AI_Batte_percent = map(AI_Battefloat, 1480, 1680, 0, 100) + 0;  // map battery voltage to percentage 14.8v to 16.8v
	if (AI_Batte_percent < 0) { AI_Batte_percent = 0; }
	if (AI_Batte_percent > 100) { AI_Batte_percent = 100; }

    if (ModeDispSet == 0) {
      
	LCDgoTo(0); lcd.print(AI_Batte_percent); lcd.print("%    ");
        lcd.print(AI_Batte); lcd.print("v ");
      /*
		if (slooowflag == 1) {
			LCDgoTo(0); lcd.print(AI_Batte_percent); lcd.print("%    ");
			} else {
			LCDgoTo(0); lcd.print(AI_Batte); lcd.print("v ");
		}
		
		DI_Onup_e_int = DI_Onup_e;
		DI_Onup_f_int = DI_Onup_f;
		LCDgoTo(15); lcd.print(DI_Onup_e_int);
		LCDgoTo(31); lcd.print(DI_Onup_f_int);
		AuxPot1 = map(AI_Val[4], 0, 1023, 0, 100) + 0;
		
		if (AuxPot1 > 100) { AuxPot1 = 100; };
		if (AuxPot1 < 0) { AuxPot1 = 0; };
		
		LCDgoTo(21); lcd.print("MDL"); lcd.print(Model);
		LCDgoTo(10); lcd.print(AuxPot1); lcd.print("% ");
		AuxPot2 = map(AI_Val[6], 0, 1023, 0, 100) + 0;
		
		if (AuxPot2 > 100) { AuxPot2 = 100; };
		if (AuxPot2 < 0) { AuxPot2 = 0; };	
		
		LCDgoTo(26); lcd.print(AuxPot2); lcd.print("% ");
      */
	}

}

