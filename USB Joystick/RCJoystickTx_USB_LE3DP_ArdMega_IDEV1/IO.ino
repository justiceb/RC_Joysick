/*

Analogue & Digital I/O

*/

unsigned char DItemp_a = 0;
unsigned char DItemp_b = 0;
unsigned char DItemp_c = 0;
unsigned char DItemp_d = 0;
unsigned char DItemp_e = 0;
unsigned char DItemp_f = 0;
unsigned char DItemp_g = 0;
unsigned char DItemp_h = 0;
unsigned char DItemp_i = 0;
unsigned char DItemp_j = 0;
int Expo = 50;
int AI_Aeler2 = 700;
float AI_AelerF = 700;
float AI_ElevaF = 700;
float AI_RuddeF = 700;
int AI_Elevon = 700;
int Minmult;
int Maxmult;
int AI_Valtemp;
int AI_Valset = 0;
int AI_Valtemp1;
int AI_Valset1 = 0;
char* PPMreassignmode[]={"        ", "1 2 3 4 5 6 7 8 "};
char* PPMchannels[]={"  ", "AE","EL","TH","RU","S1","P1","P2","S2"};
int PPMchannelpointer = 1;
int PPMvaluepointer = 1;
int lowtemp1 = 0;
int hightemp1 = 0;


// Read Digital Inputs
void readdigital() {

   /*
   Logitech Extreme 3D Pro Switch/Button mapping:-
   Buttons a (Joyvar5) No switch = 0
     1 = 1
     2 = 2
     3 = 4
     4 = 8
     5 = 16
     6 = 32
     7 = 64
     8 = 128 
   Buttons b (Joyvar6) No switch = 0
     9 = 1
     10= 2
     11= 4
     12= 8
   Top Hat (Joyvar2) No switch = 8 (wierd!)
     Left = 6
     Right = 2
     Forward = 0
     Back = 4
   */
  
   // Pull digital stick data from USB library
   extern int Joyvar2;  // Top Hat
   extern int Joyvar5;  // Buttons a
   extern int Joyvar6;  // Buttons b
   if (Joyvar2 == 8) { DI_Val[4] = 1; DI_Val[5] = 1; DI_Val[6] = 1; DI_Val[7] = 1; }  // No Hat pressed   
   if (Joyvar2 == 6) { DI_Val[4] = 0; }    // Left Hat
   if (Joyvar2 == 2) { DI_Val[5] = 0; }    // Right Hat
   if (Joyvar2 == 0) { DI_Val[6] = 0; }    // Forward Hat
   if (Joyvar2 == 4) { DI_Val[7] = 0; }    // Back Hat
   if (Joyvar5 == 0) { DI_Val[0] = 1; DI_Val[1] = 1; DI_Val[8] = 1; DI_Val[9] = 1; DI_Val[10] = 1; DI_Val[11] = 1; }  // No Button pressed
   if (Joyvar5 == 4) { DI_Val[8] = 0; }    // button 3
   if (Joyvar5 == 8) { DI_Val[10] = 0; }   // button 4
   if (Joyvar5 == 16) { DI_Val[9] = 0; }   // button 5
   if (Joyvar5 == 32) { DI_Val[11] = 0; }  // button 6   
   if (Joyvar5 == 64) { DI_Val[0] = 0; }   // Button 7
   if (Joyvar5 == 128) { DI_Val[1] = 0; }  // Button 8
   if (Joyvar6 == 0) { DI_Val[2] = 1; DI_Val[3] = 1; }  // No Button pressed    
   if (Joyvar6 == 2) { DI_Val[2] = 0; }    // Button 10
   if (Joyvar6 == 1) { DI_Val[3] = 0; }    // Button 9
  
   // Process Buttons 11 & 12 for onup & latching operation
   if (Joyvar6 == 4) { DItemp_e = 1; }   // Button 11 down - (Auxsw1)
   if (Joyvar6 == 0 && DItemp_e == 1) {  // Button 11 now up
       DI_Onup_e = !DI_Onup_e;  // invert latch
	   DItemp_e= 0;
	   buzzeractivate = 1;          // activate buzzer
	   if (DI_Onup_e == 1) { Auxsw_uS = pulseMax; }
	   if (DI_Onup_e == 0) { Auxsw_uS = pulseMin; }
	   int DI_Onup_e_int = DI_Onup_e;  // Write to Eprom
	   Epromvar = DI_Onup_e_int;
	   Address = 36;
       EEpromwriteDirect();
   }
   if (Joyvar6 == 8) { DItemp_f = 1; }   // Button 12 down - (Auxsw2)
   if (Joyvar6 == 0 && DItemp_f == 1) {  // Button 12 now up
       DI_Onup_f = !DI_Onup_f;  // invert latch
	   DItemp_f= 0;
	   buzzeractivate = 1;          // activate buzzer
	   if (DI_Onup_f == 1) { Auxsw2_uS = pulseMax; }
	   if (DI_Onup_f == 0) { Auxsw2_uS = pulseMin; }
	   int DI_Onup_f_int = DI_Onup_f;  // Write to Eprom
	   Epromvar = DI_Onup_f_int;
	   Address = 37;
       EEpromwriteDirect();
   }

   // Process pushbuttons for onup functionality
   if (DI_Val[0] == 0) { DItemp_a = 1; }   // Button 7 down
   if (DI_Val[0] == 1 && DItemp_a == 1) {  // Button 7 now up
       DI_Onup_a = 1;
	   DItemp_a= 0;
   }
   if (DI_Val[1] == 0) { DItemp_b = 1; }   // Button 8 down
   if (DI_Val[1] == 1 && DItemp_b == 1) {  // Button 8 now up
       DI_Onup_b = 1;
	   DItemp_b = 0;
   }
   if (DI_Val[2] == 0) { DItemp_c = 1; }   // Button 10 down
   if (DI_Val[2] == 1 && DItemp_c == 1) {  // Button 10 now up
       DI_Onup_c = 1;
	   DItemp_c = 0;
   }
   if (DI_Val[3] == 0) { DItemp_d = 1; }   // Button 9 down
   if (DI_Val[3] == 1 && DItemp_d == 1) {  // Button 9 now up
       DI_Onup_d = 1;
	   DItemp_d = 0;
   }   

   if (DI_Val[8] == 0) { DItemp_g = 1; }   // Button 3 down
   if (DI_Val[8] == 1 && DItemp_g == 1) {  // Button 3 now up
       DI_Onup_g = 1;
	   DItemp_g = 0;
   }    
   if (DI_Val[9] == 0) { DItemp_h = 1; }   // Button 5 down
   if (DI_Val[9] == 1 && DItemp_h == 1) {  // Button 5 now up
       DI_Onup_h = 1;
	   DItemp_h = 0;
   }
   if (DI_Val[10] == 0) { DItemp_i = 1; }   // Button 4 down
   if (DI_Val[10] == 1 && DItemp_i == 1) {  // Button 4 now up
       DI_Onup_i = 1;
	   DItemp_i = 0;
   }
   if (DI_Val[11] == 0) { DItemp_j = 1; }   // Button 6 down
   if (DI_Val[11] == 1 && DItemp_j == 1) {  // Button 6 now up
       DI_Onup_j = 1;
	   DItemp_j = 0;
   }

}


// Read Analogue Inputs
void readanalogueslow() {

   extern int Joyvar5;  // Buttons a
   extern int Joyvar2;  // Top Hat

   // Read physical input pins into var array
   AI_Val[5] = analogRead(AI_Raw[0]);  // Battery

   
   // Buttons 3,4,5&6 used for controlling AuxPot 1&2 when in Trim mode (Top Hat now does trim)
   if (TopHatMode == 1) {

	   if (Joyvar5 == 4) {  // button 3
	     DI_Onup_g = 0;
		 AI_Val[4] = AI_Val[4] - 15;    // (AuxPot 1 Down)
		 Epromvar = lowByte(AI_Val[4]);
		 Address = 38;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[4]);
		 Address = 39;
		 EEpromwriteDirect();
		 buzzeractivate = 2;
		 if (AI_Val[4] <= 0) {
			 AI_Val[4] = 0;
			 buzzeractivate = 0;
		 }
	   }
	   if (Joyvar5 == 16) {  // button 5
	     DI_Onup_h = 0;
		 AI_Val[4] = AI_Val[4] + 15;    // (AuxPot 1 Up)
		 Epromvar = lowByte(AI_Val[4]);
		 Address = 38;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[4]);
		 Address = 39;
		 EEpromwriteDirect(); 
		 buzzeractivate = 2;
		 if (AI_Val[4] >= 1024) {
			 AI_Val[4] = 1023;
			 buzzeractivate = 0;
		 }
	   } 

	   if (Joyvar5 == 8) {  // button 4
	     DI_Onup_i = 0;
		 AI_Val[6] = AI_Val[6] - 15;    // (AuxPot 2 Down)
		 Epromvar = lowByte(AI_Val[6]);
		 Address = 40;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[6]);
		 Address = 41;
		 EEpromwriteDirect(); 
		 buzzeractivate = 2;
		 if (AI_Val[6] <= 0) {
			 AI_Val[6] = 0;
			 buzzeractivate = 0;
		 }
	   }
	   if (Joyvar5 == 32) {  // button 6
	     DI_Onup_j = 0;
		 AI_Val[6] = AI_Val[6] + 15;    // (AuxPot 2 Up)
		 Epromvar = lowByte(AI_Val[6]);
		 Address = 40;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[6]);
		 Address = 41;
		 EEpromwriteDirect(); 
		 buzzeractivate = 2;
		 if (AI_Val[6] >= 1024) {
			 AI_Val[6] = 1023;
			 buzzeractivate = 0;
		 }
	   }
   }

   
   // Top Hat used for controlling AuxPot 1&2 (buttons 3,4,5&6 now used for 3-pos AuxPot 1&2 control)
   if (TopHatMode == 0) {

	   if (Joyvar2 == 4) {  // top hat back
		 AI_Val[4] = AI_Val[4] - 60;    // AuxPot 1 Down
		 if (AI_Val[4] <= 0) {
			 AI_Val[4] = 0;
		 }
	   }
	   if (Joyvar2 == 0) {  // top hat forward
		 AI_Val[4] = AI_Val[4] + 60;    // AuxPot 1 Up
		 if (AI_Val[4] >= 1024) {
			 AI_Val[4] = 1023;
		 }
	   } 

	   if (Joyvar2 == 6) {  // top hat left
		 AI_Val[6] = AI_Val[6] - 60;    // AuxPot 2 Left
		 if (AI_Val[6] <= 0) {
			 AI_Val[6] = 0;
		 }
	   }
	   if (Joyvar2 == 2) {  // top hat right
		 AI_Val[6] = AI_Val[6] + 60;    // AuxPot 2 Right
		 if (AI_Val[6] >= 1024) {
			 AI_Val[6] = 1023;
		 }
	   }

	   if (DI_Onup_g == 1 && AI_Val[4] > 0) {  // button 3 - AuxPot 1 Down
	     DI_Onup_g = 0;
		 if (AI_Val[4] <= 512) { AI_Val[4] = 0; }
		 if (AI_Val[4] > 512) { AI_Val[4] = 512; }
		 Epromvar = lowByte(AI_Val[4]);
		 Address = 38;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[4]);
		 Address = 39;
		 EEpromwriteDirect();
		 buzzeractivate = 2;
	   } else { DI_Onup_g = 0; }
	   if (DI_Onup_h == 1 && AI_Val[4] < 1023) {  // button 5 - AuxPot 1 Up
	     DI_Onup_h = 0;
		 if (AI_Val[4] >= 512) { AI_Val[4] = 1023; }
		 if (AI_Val[4] <= 512) { AI_Val[4] = 512; }
		 Epromvar = lowByte(AI_Val[4]);
		 Address = 38;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[4]);
		 Address = 39;
		 EEpromwriteDirect(); 
		 buzzeractivate = 2;
	   }  else { DI_Onup_h = 0; }

	   if (DI_Onup_i == 1 && AI_Val[6] > 0) {  // button 4 - AuxPot 2 Down
	     DI_Onup_i = 0;
		 if (AI_Val[6] <= 512) { AI_Val[6] = 0; }
		 if (AI_Val[6] > 512) { AI_Val[6] = 512; }
		 Epromvar = lowByte(AI_Val[6]);
		 Address = 40;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[6]);
		 Address = 41;
		 EEpromwriteDirect(); 
		 buzzeractivate = 2;
	   } else { DI_Onup_i = 0; }
	   if (DI_Onup_j == 1 && AI_Val[6] < 1023) {  // button 6 - AuxPot 2 Up
	     DI_Onup_j = 0;
		 if (AI_Val[6] >= 512) { AI_Val[6] = 1023; }
	     if (AI_Val[6] <= 512) { AI_Val[6] = 512; }
		 Epromvar = lowByte(AI_Val[6]);
		 Address = 40;
		 EEpromwriteDirect();
		 Epromvar = highByte(AI_Val[6]);
		 Address = 41;
		 EEpromwriteDirect(); 
		 buzzeractivate = 2;
	   } else { DI_Onup_j = 0; }
   }   
   
   // Custom: Button 1 (trigger) on stick forces AI_Val[6] to full scale
   if ((Joyvar5 == 1 || Joyvar5 == 3) && AI_Valset == 0) {
   	 buzzeractivate = 1;
     AI_Valtemp = AI_Val[6];  // Save off
	 AI_Valset = 1;
	 if (AuxSwTrigger == 1) { AI_Val[6] = AUX_Max; }
	 if (AuxSwTrigger == 2) { AI_Val[6] = AUX_Min + 500; }
	 if (AuxSwTrigger == 3) { AI_Val[6] = AUX_Min; } 
   }
   if ((Joyvar5 == 0 || Joyvar5 == 2) && AI_Valset == 1) {  // Trigger no longer but had just been used
	 AI_Val[6] = AI_Valtemp;
	 AI_Valset = 0;
   }

   // Custom: Button 2 (thumb) on stick forces AI_Val[4] to full scale
   if ((Joyvar5 == 2 || Joyvar5 == 3) && AI_Valset1 == 0) {
     buzzeractivate = 1;
     AI_Valtemp1 = AI_Val[4];  // Save off
	 AI_Valset1 = 1;
	 if (AuxSwThumb == 1) { AI_Val[4] = AUX2_Max; }
	 if (AuxSwThumb == 2) { AI_Val[4] = AUX2_Min + 500; } 	 
	 if (AuxSwThumb == 3) { AI_Val[4] = AUX2_Min; } 
     
   }
   if ((Joyvar5 == 0 || Joyvar5 == 1) && AI_Valset1 == 1) {  // Thumb button no longer but had just been used
     AI_Val[4] = AI_Valtemp1;
     AI_Valset1 = 0;
   }
   
}

// Read Analogue Inputs
void readanalogue() {

   // Pull analogue stick data from USB library
   extern int Joyvar0;   // Pull ELE from USB routine
   extern int Joyvar1;   // Pull AEL from USB routine
   extern int Joyvar3;   // Pull RUD from USB routine
   extern int Joyvar4;   // Pull THR from USB routine
   AI_Val[1] = Joyvar0;  // ELE 0-1023
   AI_Val[0] = Joyvar1;  // AEL 0-1023
   AI_Val[2] = Joyvar3;  // RUD 0-255
   AI_Val[3] = Joyvar4;  // THR 0-255
 
   // Incorporate Rate Multiplier then scale inputs to produce PPM values
   Minmult = (pulseMid - (RateMult * ((pulseMax - pulseMin) / 2)));  // Generate scaled graph depending on current RateMult
   Maxmult = (pulseMid + (RateMult * ((pulseMax - pulseMin) / 2)));
   
   if (ReverseElevator == 0) {
     if (AI_Val[0] < ELE_Center) { AI_Eleva = map(AI_Val[0], ELE_Min, ELE_Center-1, Minmult, pulseMid) + TrEleEEprom; }          // Elevator / Aeleron 2
     if (AI_Val[0] >= ELE_Center) { AI_Eleva = map(AI_Val[0], ELE_Center, ELE_Max, pulseMid + 1, Maxmult) + TrEleEEprom; }       // Elevator / Aeleron 2
   } else {
     if (AI_Val[0] < ELE_Center) { AI_Eleva = map(AI_Val[0], ELE_Max, ELE_Center, Minmult, pulseMid) + TrEleEEprom; }            // Elevator / Aeleron 2 (reversed)
     if (AI_Val[0] >= ELE_Center) { AI_Eleva = map(AI_Val[0], ELE_Center-1, ELE_Min, pulseMid + 1, Maxmult) + TrEleEEprom; }     // Elevator / Aeleron 2 (reversed)
   }
   
   if (ReverseAeleron == 0) {  
     if (AI_Val[1] < AEL_Center) { AI_Aeler = map(AI_Val[1], AEL_Min, AEL_Center-1, Minmult, pulseMid) + TrAelEEprom; }          // Aeleron 1
     if (AI_Val[1] >= AEL_Center) { AI_Aeler = map(AI_Val[1], AEL_Center, AEL_Max, pulseMid + 1, Maxmult) + TrAelEEprom; }       // Aeleron 1
   } else {   
     if (AI_Val[1] < AEL_Center) { AI_Aeler = map(AI_Val[1], AEL_Max, AEL_Center, Minmult, pulseMid) + TrAelEEprom; }            // Aeleron 1 (reversed)
     if (AI_Val[1] >= AEL_Center) { AI_Aeler = map(AI_Val[1], AEL_Center-1, AEL_Min, pulseMid + 1, Maxmult) + TrAelEEprom; }     // Aeleron 1 (reversed)
   }

   if (ReverseRudder == 0) {   
     if (AI_Val[2] < RUD_Center) { AI_Rudde = map(AI_Val[2], RUD_Min, RUD_Center-1, Minmult, pulseMid) + TrRudEEprom; }          // Rudder  
     if (AI_Val[2] >= RUD_Center) { AI_Rudde = map(AI_Val[2], RUD_Center, RUD_Max, pulseMid + 1, Maxmult) + TrRudEEprom; }       // Rudder  
   } else {
     if (AI_Val[2] < RUD_Center) { AI_Rudde = map(AI_Val[2], RUD_Max, RUD_Center, Minmult, pulseMid) + TrRudEEprom; }            // Rudder (reversed)
     if (AI_Val[2] >= RUD_Center) { AI_Rudde = map(AI_Val[2], RUD_Center-1, RUD_Min, pulseMid + 1, Maxmult) + TrRudEEprom; }     // Rudder (reversed)
   }
   
   if (ReverseThrottle == 0) { 
     AI_Throt = map(AI_Val[3], THR_Min, THR_Max, pulseMax, pulseMin) + 0;       // Throttle
   } else {
     AI_Throt = map(AI_Val[3], THR_Max, THR_Min, pulseMax, pulseMin) + 0;       // Throttle (reversed)
   }
   
   if (ReverseAuxpot == 0) { 
		AI_Auxpot = map(AI_Val[4], AUX_Min, AUX_Max, pulseMin, pulseMax) + 0;      // Aux pot 1
		} else {
		AI_Auxpot = map(AI_Val[4], AUX_Min, AUX_Max, pulseMax, pulseMin) + 0;      // Aux pot 1 (reversed)
   }

   if (ReverseAuxpot2 == 0) { 
		AI_Auxpot2 = map(AI_Val[6], AUX2_Min, AUX2_Max, pulseMin, pulseMax) + 0;   // Aux pot 2
		} else {
		AI_Auxpot2 = map(AI_Val[6], AUX2_Min, AUX2_Max, pulseMax, pulseMin) + 0;   // Aux pot 2 (reversed)
   }
}


// Check limits & set outputs
void checklimitsmodessetouputs() {
 
   // Exponential Aelerons
   if (ReverseAeleron == 0) {
       if (ExpoModeAEL == 1) {
           if (AI_Val[1] < AEL_Center ){
	          AI_AelerF = AI_Aeler - pulseMid;  // zero
	          AI_AelerF = ((((AI_AelerF*-1)/10) * ((AI_AelerF*-1)/10))) * -1;  // low side calc
		      AI_AelerF = AI_AelerF * .3;  // reduce gain
	          AI_Aeler = AI_AelerF + pulseMid;
           }
           if (AI_Val[1] >= AEL_Center ){
              AI_AelerF = AI_Aeler - pulseMid;  // zero
	          AI_AelerF = (AI_AelerF/10) * (AI_AelerF/10);  // high side calc
			  AI_AelerF = AI_AelerF * .3;  // reduce gain
	          AI_Aeler = AI_AelerF + pulseMid;
           }
       }
   } else {
        if (ExpoModeAEL == 1) {
           if (AI_Val[1] < AEL_Center ){
              AI_AelerF = AI_Aeler - pulseMid;  // zero
	          AI_AelerF = (AI_AelerF/10) * (AI_AelerF/10);  // high side calc
			  AI_AelerF = AI_AelerF * .3;  // reduce gain
	          AI_Aeler = AI_AelerF + pulseMid;
           }
           if (AI_Val[1] >= AEL_Center ){
	          AI_AelerF = AI_Aeler - pulseMid;  // zero
	          AI_AelerF = ((((AI_AelerF*-1)/10) * ((AI_AelerF*-1)/10))) * -1;  // low side calc
		      AI_AelerF = AI_AelerF * .3;  // reduce gain
	          AI_Aeler = AI_AelerF + pulseMid;
           }
       }  
   
   }

   // Exponential Elevators
   if (ReverseElevator == 0) {
       if (ExpoModeELE == 1) {
           if (AI_Val[0] < ELE_Center ){
	          AI_ElevaF = AI_Eleva - pulseMid;  // zero
	          AI_ElevaF = ((((AI_ElevaF*-1)/10) * ((AI_ElevaF*-1)/10))) * -1;  // low side calc
		      AI_ElevaF = AI_ElevaF * .3;  // reduce gain
	          AI_Eleva = AI_ElevaF + pulseMid;
           }
           if (AI_Val[0] >= ELE_Center ){
              AI_ElevaF = AI_Eleva - pulseMid;  // zero
	          AI_ElevaF = (AI_ElevaF/10) * (AI_ElevaF/10);  // high side calc
		      AI_ElevaF = AI_ElevaF * .3;  // reduce gain
	          AI_Eleva = AI_ElevaF + pulseMid;
           }
       }
   } else {
       if (ExpoModeELE == 1) {
           if (AI_Val[0] < ELE_Center ){
              AI_ElevaF = AI_Eleva - pulseMid;  // zero
	          AI_ElevaF = (AI_ElevaF/10) * (AI_ElevaF/10);  // high side calc
		      AI_ElevaF = AI_ElevaF * .3;  // reduce gain
	          AI_Eleva = AI_ElevaF + pulseMid;
           }
           if (AI_Val[0] >= ELE_Center ){
	          AI_ElevaF = AI_Eleva - pulseMid;  // zero
	          AI_ElevaF = ((((AI_ElevaF*-1)/10) * ((AI_ElevaF*-1)/10))) * -1;  // low side calc
		      AI_ElevaF = AI_ElevaF * .3;  // reduce gain
	          AI_Eleva = AI_ElevaF + pulseMid;
           }
       }   
   }

   // Exponential Rudder
   if (ReverseRudder == 0) {
       if (ExpoModeRUD == 1) {
           if (AI_Val[2] < RUD_Center ){
	          AI_RuddeF = AI_Rudde - pulseMid;  // zero
	          AI_RuddeF = ((((AI_RuddeF*-1)/10) * ((AI_RuddeF*-1)/10))) * -1;  // low side calc
		      AI_RuddeF = AI_RuddeF * .3;  // reduce gain
	          AI_Rudde = AI_RuddeF + pulseMid;
           }
           if (AI_Val[2] >= RUD_Center ){
              AI_RuddeF = AI_Rudde - pulseMid;  // zero
	          AI_RuddeF = (AI_RuddeF/10) * (AI_RuddeF/10);  // high side calc
		      AI_RuddeF = AI_RuddeF * .3;  // reduce gain
	          AI_Rudde = AI_RuddeF + pulseMid;
           }
	   }
   } else { 
       if (ExpoModeRUD == 1) {
           if (AI_Val[2] < RUD_Center ){
              AI_RuddeF = AI_Rudde - pulseMid;  // zero
	          AI_RuddeF = (AI_RuddeF/10) * (AI_RuddeF/10);  // high side calc
		      AI_RuddeF = AI_RuddeF * .3;  // reduce gain
	          AI_Rudde = AI_RuddeF + pulseMid;
           }
           if (AI_Val[2] >= RUD_Center ){
	          AI_RuddeF = AI_Rudde - pulseMid;  // zero
	          AI_RuddeF = ((((AI_RuddeF*-1)/10) * ((AI_RuddeF*-1)/10))) * -1;  // low side calc
		      AI_RuddeF = AI_RuddeF * .3;  // reduce gain
	          AI_Rudde = AI_RuddeF + pulseMid;
           }
	   }
   }   
   
   // Flying Wing - Elevon mode assumes Aeleron servo's mounted mirror image to each other
   if (ElevonMode == 1) {
      AI_Aeler2 = AI_Aeler;              // Generate 2nd Aeleron var
   	  AI_Elevon = AI_Eleva - pulseMid;   // Copy elevator input off & zero it, this becomes the modifier for the 2 Aelerons
	  AI_Aeler = AI_Aeler + AI_Elevon;   // Output - Aeleron 1 goes up
      AI_Eleva = AI_Aeler2 - AI_Elevon;  // Output - Aeleron 2 goes down  (inverted servo) 
   }

   // Check limits
   if (AI_Aeler < pulseMin) AI_Aeler = pulseMin;
   if (AI_Aeler > pulseMax) AI_Aeler = pulseMax;   
   if (AI_Eleva < pulseMin) AI_Eleva = pulseMin;
   if (AI_Eleva > pulseMax) AI_Eleva = pulseMax; 
   if (AI_Throt < pulseMin) AI_Throt = pulseMin;
   if (AI_Throt > pulseMax) AI_Throt = pulseMax; 
   if (AI_Rudde < pulseMin) AI_Rudde = pulseMin;
   if (AI_Rudde > pulseMax) AI_Rudde = pulseMax;   
   if (AI_Auxpot < pulseMin) AI_Auxpot = pulseMin;
   if (AI_Auxpot > pulseMax) AI_Auxpot = pulseMax;  
   if (AI_Auxpot2 < pulseMin) AI_Auxpot2 = pulseMin;
   if (AI_Auxpot2 > pulseMax) AI_Auxpot2 = pulseMax;    
 
   // Load PPM channel array with final channel values
   PPM_arrayT[0] = AI_Aeler + Fixed_uS;
   PPM_arrayT[1] = AI_Eleva + Fixed_uS;
   PPM_arrayT[2] = AI_Throt + Fixed_uS;
   PPM_arrayT[3] = AI_Rudde + Fixed_uS;
   PPM_arrayT[4] = Auxsw_uS + Fixed_uS;
   PPM_arrayT[5] = AI_Auxpot + Fixed_uS;
   PPM_arrayT[6] = AI_Auxpot2 + Fixed_uS;
   PPM_arrayT[7] = Auxsw2_uS + Fixed_uS;
   
   // Load PPM channel array with final channel values
   PPM_array[0] = PPM_arrayT[PPM_arrayTemp[1]-1];
   PPM_array[1] = PPM_arrayT[PPM_arrayTemp[2]-1];
   PPM_array[2] = PPM_arrayT[PPM_arrayTemp[3]-1];
   PPM_array[3] = PPM_arrayT[PPM_arrayTemp[4]-1];
   PPM_array[4] = PPM_arrayT[PPM_arrayTemp[5]-1];
   PPM_array[5] = PPM_arrayT[PPM_arrayTemp[6]-1];
   PPM_array[6] = PPM_arrayT[PPM_arrayTemp[7]-1];
   PPM_array[7] = PPM_arrayT[PPM_arrayTemp[8]-1];
   
}

void PPMreassign() {
	if (ModeDispSet == 9) {    // Re-assign PPM channels
	 
	     LCDgoTo(0); lcd.print(PPMreassignmode[1]); // Top line
	     LCDgoTo(16); lcd.print(PPMchannels[PPM_arrayTemp[1]]); //AE
	     LCDgoTo(18); lcd.print(PPMchannels[PPM_arrayTemp[2]]); //ELE
	     LCDgoTo(20); lcd.print(PPMchannels[PPM_arrayTemp[3]]); //TH
	     LCDgoTo(22); lcd.print(PPMchannels[PPM_arrayTemp[4]]); //RU
	     LCDgoTo(24); lcd.print(PPMchannels[PPM_arrayTemp[5]]); //S1
	     LCDgoTo(26); lcd.print(PPMchannels[PPM_arrayTemp[6]]); //P1
	     LCDgoTo(28); lcd.print(PPMchannels[PPM_arrayTemp[7]]); //P2
	     LCDgoTo(30); lcd.print(PPMchannels[PPM_arrayTemp[8]]); //S2
		 if (slowflag == 1) { LCDgoTo((PPMchannelpointer * 2) + 14); lcd.print(PPMchannels[PPM_arrayTemp[PPMchannelpointer]]); }
		 if (slowflag == 0) { LCDgoTo((PPMchannelpointer * 2) + 14); lcd.print(PPMchannels[0]); }
	
	 if (DI_Onup_c == 1) {    // Advance cursor
	     DI_Onup_c = 0;
	     buzzeractivate = 1;                  // activate buzzer
		 PPMchannelpointer++;
		 if (PPMchannelpointer == 9) { PPMchannelpointer = 1; }
		 PPMvaluepointer = PPM_arrayTemp[PPMchannelpointer];  // load starting point ready for next press of update target button
	 }

	 if (DI_Onup_b == 1) {    // update target PPM channel
	     DI_Onup_b = 0;
	     buzzeractivate = 1;                  // activate buzzer
		 PPMvaluepointer++;                   // starts at 1
	     if (PPMvaluepointer == 9) { PPMvaluepointer = 1; }
		 PPM_arrayTemp[PPMchannelpointer] = PPMvaluepointer;  // Now PPM_arrayTemp[1-8] contains 1-8 final info on new channel designation
		 Epromvar = PPMvaluepointer;
		 Address = PPMchannelpointer+60;
         EEpromwriteDirect();
	 }
	 
    }
}	
	

// *********************** Setup **************************

void PPMreassignSetup() {   // Read PPM Channel assignments from EEprom
    Address = 61;  EEpromreadDirect();  PPM_arrayTemp[1] = Epromvar;  if (PPM_arrayTemp[1] < 1 || PPM_arrayTemp[1] > 8) { PPM_arrayTemp[1] = 1; }
	Address = 62;  EEpromreadDirect();  PPM_arrayTemp[2] = Epromvar;  if (PPM_arrayTemp[2] < 1 || PPM_arrayTemp[2] > 8) { PPM_arrayTemp[2] = 2; }
	Address = 63;  EEpromreadDirect();  PPM_arrayTemp[3] = Epromvar;  if (PPM_arrayTemp[3] < 1 || PPM_arrayTemp[3] > 8) { PPM_arrayTemp[3] = 3; }
	Address = 64;  EEpromreadDirect();  PPM_arrayTemp[4] = Epromvar;  if (PPM_arrayTemp[4] < 1 || PPM_arrayTemp[4] > 8) { PPM_arrayTemp[4] = 4; }
	Address = 65;  EEpromreadDirect();  PPM_arrayTemp[5] = Epromvar;  if (PPM_arrayTemp[5] < 1 || PPM_arrayTemp[5] > 8) { PPM_arrayTemp[5] = 5; }
	Address = 66;  EEpromreadDirect();  PPM_arrayTemp[6] = Epromvar;  if (PPM_arrayTemp[6] < 1 || PPM_arrayTemp[6] > 8) { PPM_arrayTemp[6] = 6; }
	Address = 67;  EEpromreadDirect();  PPM_arrayTemp[7] = Epromvar;  if (PPM_arrayTemp[7] < 1 || PPM_arrayTemp[7] > 8) { PPM_arrayTemp[7] = 7; }
	Address = 68;  EEpromreadDirect();  PPM_arrayTemp[8] = Epromvar;  if (PPM_arrayTemp[8] < 1 || PPM_arrayTemp[8] > 8) { PPM_arrayTemp[8] = 8; }	
}

void AuxSW12Setup() {
	Address = 36;                                                // Read AuxSW1 from EEprom
	EEpromreadDirect();
	DI_Onup_e = Epromvar; 
	if (DI_Onup_e == 1) { Auxsw_uS = pulseMax; }
	if (DI_Onup_e == 0) { Auxsw_uS = pulseMin; }
	if (DI_Onup_e > 1) {
		DI_Onup_e = 0;
		Epromvar = 0;
		Address = 36;
		EEpromwriteDirect();
	} 
   
	Address = 37;                                                // Read AuxSW2 from EEprom
	EEpromreadDirect();
	DI_Onup_f = Epromvar;   
	if (DI_Onup_f == 1) { Auxsw2_uS = pulseMax; }
	if (DI_Onup_f == 0) { Auxsw2_uS = pulseMin; }
	if (DI_Onup_f > 1) {
		DI_Onup_f = 0;
		Epromvar = 0;
		Address = 37;
		EEpromwriteDirect();
	} 
}

void AuxPOT12Setup() {
	if (TopHatMode == 1) {
		Address = 38;                                                   // Read AuxPOT1 from EEprom
		EEpromreadDirect();
		lowtemp1 = Epromvar; 
		Address = 39;
		EEpromreadDirect();
		hightemp1 = Epromvar; 
		AI_Val[4] = word(hightemp1, lowtemp1);
		Address = 40;                                                   // Read AuxPOT2 from EEprom
		EEpromreadDirect();
		lowtemp1 = Epromvar; 
		Address = 41;
		EEpromreadDirect();
		hightemp1 = Epromvar; 		
		AI_Val[6] = word(hightemp1, lowtemp1);
	} else {
		AI_Val[4] = 512; // centre
		AI_Val[6] = 512;
	}
}

