/*

Model Selection

*/

char* Modelnames[]={"    ", "MD1 ", "MD2 ", "MD3 ", "MD4 ", "Model Select"};

// Model Selection
void ModelSelection() {

    // Model Seletion
	if (ModeDispSet == 12) {
	     LCDgoTo(2); lcd.print(Modelnames[5]);
		 ModelSelectionDisplay();
		 
		 if (DI_Onup_c == 1) {
		    DI_Onup_c = 0;
			Model++;
			if (Model == 5) { Model = 4; }
			buzzeractivate = 1;                  // activate buzzer
			ModelSelectionDisplay();
			Epromvar = Model;
			Address = 1000;
            EEpromwriteDirectNoOffset();
			RunSubs();                      // Pull the new data from EEprom
		 }
		
		 if (DI_Onup_b == 1) {
		    DI_Onup_b = 0;
			Model--;
			if (Model == 0) { Model = 1; }
			buzzeractivate = 1;                  // activate buzzer
			ModelSelectionDisplay();
			Epromvar = Model;
			Address = 1000;
            EEpromwriteDirectNoOffset();
			RunSubs();                      // Pull the new data from EEprom
		 }
		 
	}
}	
	
void ModelSelectionDisplay() {

		 if (Model == 1) {
		     ModelAddressOffset = 0;
			 if (slowflag == 1) { LCDgoTo(16); lcd.print(Modelnames[1]); }
			 if (slowflag == 0) { LCDgoTo(16); lcd.print(Modelnames[0]); }
			 LCDgoTo(20); lcd.print(Modelnames[2]);
		     LCDgoTo(24); lcd.print(Modelnames[3]);
		     LCDgoTo(28); lcd.print(Modelnames[4]);
	     }
		 if (Model == 2) {
		     ModelAddressOffset = 100;
    		 LCDgoTo(16); lcd.print(Modelnames[1]);
			 if (slowflag == 1) { LCDgoTo(20); lcd.print(Modelnames[2]); }
			 if (slowflag == 0) { LCDgoTo(20); lcd.print(Modelnames[0]); }
		     LCDgoTo(24); lcd.print(Modelnames[3]);
		     LCDgoTo(28); lcd.print(Modelnames[4]);			 
	     }		 
		 if (Model == 3) {
		     ModelAddressOffset = 200;
		     LCDgoTo(16); lcd.print(Modelnames[1]);
		     LCDgoTo(20); lcd.print(Modelnames[2]);
			 if (slowflag == 1) { LCDgoTo(24); lcd.print(Modelnames[3]); }
			 if (slowflag == 0) { LCDgoTo(24); lcd.print(Modelnames[0]); }
		     LCDgoTo(28); lcd.print(Modelnames[4]);
	     }		 
		 if (Model == 4) {
		     ModelAddressOffset = 300;
			 LCDgoTo(16); lcd.print(Modelnames[1]);
		     LCDgoTo(20); lcd.print(Modelnames[2]);
		     LCDgoTo(24); lcd.print(Modelnames[3]);
			 if (slowflag == 1) { LCDgoTo(28); lcd.print(Modelnames[4]); }
			 if (slowflag == 0) { LCDgoTo(28); lcd.print(Modelnames[0]); }
	     }
}

// *********************** Setup **************************

void ModelSelectionSetup() {
 
 Address = 1000;           // Read from EEprom
 EEpromreadDirectNoOffset();
 Model = Epromvar;
 if (Model < 1 || Model > 4) {  // Set to default if out of range
	 Model = 1;
	 Epromvar = Model;
	 Address = 1000;
     EEpromwriteDirectNoOffset();
  }
}

