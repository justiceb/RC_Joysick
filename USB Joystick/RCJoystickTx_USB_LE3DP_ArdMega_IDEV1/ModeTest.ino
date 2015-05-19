/*

Mode Test

A rough and ready way of diagnosing the analogue inputs and PPM output channels.
Press buttons DI_Val[3] or DI_Val[4] to cycle round the RAW analogue
input or ppm output channels. Press button DI_Val[2] or DI_Val[5] to exit this mode.

*/

int pointraw = 0;
int pointppm = 0;
int RawPPMOut = 0;
int prevmode = 0;

void ModeTesting() {
    
	// Mode Test RAW & PPM
	if (ModeDispSet == 10) {
        // clearLCD();
	//	 LCDgoTo(0);
         //lcd.print(MenuDisplay[7]);
	//	 LCDgoTo(16);
        // lcd.print(MenuDisplay[8]);
		 
		 if (DI_Onup_c == 1) {    // Enter Test Mode
		     DI_Onup_c = 0;
		 	 ModeTest = 1;
			 buzzeractivate = 1;                  // activate buzzer
		 }
		 
		 if (DI_Onup_b == 1) {    // Enter Test Mode
		     DI_Onup_b = 0;
			 ModeTest = 1;
			 buzzeractivate = 1;                  // activate buzzer
		 }		 
		
	}

    if (ModeTest == 1) {

	    if (DI_Onup_a == 1 || DI_Onup_d == 1) {   // Exit Mode Test
		     clearLCD();
		     DI_Onup_a = 0;
		     DI_Onup_d = 0;
	         buzzeractivate = 1;
	         ModeTest = 0;
		     pointppm = 0;
		     pointraw = 0;
        }

	    if (DI_Onup_b == 1 || DI_Onup_c == 1) {   // Enter Mode Test
		     DI_Onup_b = 0;
		     RawPPMOut = 0;
			 clearLCD();
		}
		
		// Raw input display mode (all the analogue inputs)
		// PPM input display mode (for the 8 channels)
		if (RawPPMOut == 0) {
		     clearLCD();  // Clear chars off the screen - cheat!
		
		     if (DI_Val[1] == 0) {
		     DI_Onup_b = 0;
		     buzzeractivate = 1;
		     if (prevmode == 0) { pointraw++; }
		     prevmode = 0;
             if (pointraw == 7) { pointraw = 0; }  
		     }
		
		     if (pointraw <= 6) {
		         LCDgoTo(0);
                 lcd.print("RAW A   ");
		         LCDgoTo(5);
                 lcd.print(pointraw);
		         LCDgoTo(16);
                 lcd.print(AI_Val[pointraw]);
             }
		   
		     if (DI_Val[2] == 0) {
		         DI_Onup_c = 0;
		         buzzeractivate = 1;
		         if (prevmode == 1) { pointppm++; }
		         prevmode = 1;
                 if (pointppm == 8) { pointppm = 0; }  
		     }
		
		     LCDgoTo(10);
             lcd.print("PPM     ");
		     LCDgoTo(14);
             lcd.print(pointppm + 1);
		     LCDgoTo(26);
		   
             if (pointppm == 0) { lcd.print(AI_Aeler); }
             if (pointppm == 1) { lcd.print(AI_Eleva); }
             if (pointppm == 2) { lcd.print(AI_Throt); }
             if (pointppm == 3) { lcd.print(AI_Rudde); }
             if (pointppm == 4) { lcd.print(Auxsw_uS); }
             if (pointppm == 5) { lcd.print(AI_Auxpot); }
             if (pointppm == 6) { lcd.print(AI_Auxpot2); }
             if (pointppm == 7) { lcd.print(Auxsw2_uS); }
             //delay(1000);
		}		
    }
}


