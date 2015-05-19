/*

LCD = 4bit mode LCD

*/

// ******************** LCD COMMANDS **********************

void clearLCD() {
     lcd.setCursor(0,0); lcd.print("                ");
     lcd.setCursor(0,1); lcd.print("                ");
}

void LCDgoTo(int position) {
     if (position < 16){ lcd.setCursor(position,0);
	 } else {	 
	     lcd.setCursor(position-16,1);
	 }
}

// *********************** Setup **************************
void LCDSetup() {
  lcd.begin(16,2);  // Set up the LCD Col and Row count  (library routine)
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();       // Home cursor LCD (library routine)
  //LCDgoTo(0); lcd.print(Version[1]);
  //LCDgoTo(16); lcd.print(Version[0]);
  delay(1000);
}
 
