/*
RC Joystick PPM USB Version (8 channel)
  By Ian Johnston (www.ianjohnston.com)

Version V8.76 (30/08/12)
  
DISCLAIMER:
  With this design, including both the hardware & software I offer no guarantee that it is bug
  free or reliable. So, if you decide to build one and your plane, quad etc crashes and/or causes
  damage/harm to you, others or property then you are on your own. This work is experimental.

INFORMATION:
  See ReadMe.txt for lots of info including I/O allocation.  
  
*/

#include <avr/pgmspace.h>
#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <Usb.h>
#include <usbhub.h>
#include <address.h>
#include <hid.h>
#include <hiduniversal.h>
#include "le3dp_rptparser.h"
#include <printhex.h>
#include <message.h>
#include <hexdump.h>
#include <parsetools.h>
#include "EEPROM.h"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);

char* Version[]={"  Version 8.76 ", "  USB JOYSTICK  "};

// User adjustable settings
int pulseMin = 700, pulseMid = 1200, pulseMax = 1700;	        // PPM Pulse widths in uS
float RateMultLO = 0.5, RateMultMI = 0.75, RateMultHI = 1.0;    // Rates LO, MI & HI multipliers
int ReverseAuxpot = 0;                                          // 0 = Non-invert, 1 = Inverted AuxPot1 output
int ReverseAuxpot2 = 0;                                         // 0 = Non-invert, 1 = Inverted AuxPot2 output
int InvertPPM = 0;                                              // 0 = Non-invert, 1 = Inverted PPM output

// Setup stick range and centres
int AEL_Min = 0,  AEL_Center = 512, AEL_Max = 1023;             // Aeleron (USB 10-bit)
int ELE_Min = 0,  ELE_Center = 512, ELE_Max = 1023;             // Elevator (USB 10-bit)
int RUD_Min = 0,  RUD_Center = 128, RUD_Max = 255;              // Rudder (USB 8-bit)
int THR_Min = 0,  THR_Max = 255;                                // Throttle (USB 8-bit)
int AUX_Min = 0,  AUX_Max = 1023;                               // Aux pot (ANA input 10-bit)
int AUX2_Min = 0, AUX2_Max = 1023;                              // Aux2 pot (ANA input 10-bit)

// Setup LCD
#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define BUTTON_PIN_1 46
#define BUTTON_PIN_2 44
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// Assign physical analogue & digital I/O pins
int AI_Raw[3] = { 0, 1, 2 };     // physical analog input pins
int AI_Val[7];                   // total analogue input vars, physical & USB
int DI_Val[12];                  // total digital input vars, USB only
int AuxPot1;
int AuxPot2;
unsigned char AI_pincount = 3;     // physical analogue pin count
unsigned char outPinPPM = 12;      // PPM output pin (do not change - Timer1 on MEGA)
unsigned char outPinBuzz = 13;     // Buzzer output pin

// Various vars
float RateMult;
int AI_Auxpot, AI_Auxpot2, AI_Throt, AI_Rudde, AI_Eleva, AI_Aeler, Auxsw_uS, Auxsw2_uS;
int DI_Onup_a = 0, DI_Onup_b = 0, DI_Onup_c = 0, DI_Onup_d = 0, DI_Onup_g = 0, DI_Onup_h = 0, DI_Onup_i = 0, DI_Onup_j = 0;
boolean DI_Onup_e = false, DI_Onup_f = false;
int oneshot = 0;
int Model = 1;

// Mode vars
int ChangeModeHIMIDLO = 0;
int trimMax = 75, trimMin = (~trimMax)+1;         // Trim limits
int Offset;
int ModeTest = 0, ElevonMode = 0, ExpoModeAEL = 0, ExpoModeELE = 0, ExpoModeRUD = 0, Timermode = 0, ModeDispSet = 0, TopHatMode = 0;
int ReverseAeleron = 0, ReverseElevator = 0, ReverseRudder = 0, ReverseThrottle = 0, AuxSwThumb = 0, AuxSwTrigger = 0;
char* MenuDisplay[]={"        ", "AE", "EL", "RU", "Elevon  ", "Expo. Aeleron", "Invert  ", "Test Mode", "Raw I/O & PPM Ch", "Expo. Elevator", "Expo. Rudder", "Expo-Off"};

// EEprom vars
int RatesHIMIDLOEEprom = 1;
int TrAelEEprom = 0, TrEleEEprom = 0, TrRudEEprom = 0, EpromPointer = 0, AuxSW1EEprom = 0, AuxSW2EEprom = 0;
int Epromvar, Address;
int ModelAddressOffset = 0;

// Buzzer vars
long previousMillis = 0;
unsigned long currentMillis;
unsigned char buzzeractivate = 0;

// Sub timing vars
int tick0 = 0, tick1 = 0, tick2 = 0, tick3 = 0, tick4 = 0;
unsigned char slowflag;
unsigned char slooowflag;

// Manual Timer, Interrupt Timer vars
unsigned char TimerStart = 0;    
int secflag = 0, minflag = 0, secflaghold = 0, minflaghold = 0, TimerInhibit;
int PPM_array[9];
int PPM_arrayTemp[9];
int PPM_arrayT[9];
int PPMFreq_uS = 22500;          // PPM frame length total in uS
int Fixed_uS = 300;              // PPM frame padding LOW phase in uS


// *********************** Setup **************************
void setup() {

  Serial.begin(115200);
  Serial.println("Start");
  if (Usb.Init() == -1)	  lcd.print("OSC did not start.");
  delay(200);
  if (!Hid.SetReportParser(0, &Joy))    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  ); 

  LCDSetup();
  clearLCD();
  
  // Setup Digital I/O
  pinMode(outPinPPM, OUTPUT);      // set as output
  pinMode(outPinBuzz, OUTPUT);     // set as output
  pinMode(BUTTON_PIN_1, INPUT);  
  pinMode(BUTTON_PIN_2, INPUT); 
  
  // Beep-Beep
  digitalWrite(outPinBuzz, HIGH);
  delay(50);
  digitalWrite(outPinBuzz, LOW);
  delay(50);
  digitalWrite(outPinBuzz, HIGH);
  delay(50);
  digitalWrite(outPinBuzz, LOW);
  
  // Initialize PPM channel array
  char i=0;
  for(i=0; i<8; i++) { PPM_array[i] = pulseMin; }
  PPM_array[i] = -1;   // Mark end
  
  // TIMER INFO: Timer 1 = PPM Gen (11,12), Timer 2 = USB Host (9,10), Timer 3 = ISR
  
  // Initialise ISR Timer 1 - PPM generation
  TCCR1A = B00110001;     // Compare register B used in mode 3
  TCCR1B = B00010010;     // WGM13 & CS11 set to 1
  TCCR1C = B00000000;     // All set to 0
  TIMSK1 = B00000010;     // Interrupt on compare B
  TIFR1  = B00000010;     // Interrupt on compare B
  OCR1A = PPMFreq_uS;     // PPM frequency
  OCR1B = Fixed_uS;       // PPM off time (lo padding)
  if (InvertPPM == 1) { TCCR1A = B00100001; }
  
  // Initialise ISR Timer 3 - Subroutine timing - 7.5mS approx
  TCCR3B = B00000000;     // Disable Timer3 while we set it up
  TCCR3B = 0; 
  TCNT3  = 65458;         // Reset Timer Count  (65535-"178")
  TIFR3  = B00000000;     // Timer3 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK3 = (1 << TOIE1);  // enable Timer1 overflow interrupt:
  TCCR3A = 0;             // set entire TCCR3A register to 0
  TCCR3B |= (1 << CS10);  // Set CS10 bit so timer runs at clock speed:

  // Other
  currentMillis = millis();        // Prepare keypress buzzer timing
  previousMillis = millis();
  
  ModelSelectionSetup();           // Pull Model Selection from EEprom (1 of 4)
  RunSubs();                       // Pull all EEprom data based on selected Model

}


// *********************** RunSubs **************************
void RunSubs() {  // Run Various Setup subs
  AuxPotTrimModeSetup();           // Pull Pan & Tilt / Trim Mode from EEprom
  HiMiLoRatesSetup();              // Pull Rates & Trim settings from EEprom
  ElevonModeSetup();               // Pull Elevon Mode from EEprom
  ExpoModeSetup();                 // Pull AEL, ELE & RUD Expo Mode from EEprom
  InvertChannelsSetup();           // Pull AEL Invert Mode from EEprom
  AuxSW12Setup();                  // Pull AuxSW1&2 from EEprom
  AuxPOT12Setup();                 // Pull AuxPOT1&2 from EEprom
  AuxSwitchesSetup();              // Pull AuxSw 1/2 max/min from EEprom
  PPMreassignSetup();              // Pull PPM re-assignment from EEprom
}


// *********************** Main Loop **************************
void loop() {  // Main loop

  Usb.Task();                    // Joystick
  buzzer();                      // Refresh buzzer
  readanalogue();                // Read analogue I/O
  
  if (tick3 >= 20) {             // Run these subs at fixed rate
	  tick3 = 0;
	  readanalogueslow();        // Read analogue I/O
          readbutton();
  }
  
  checklimitsmodessetouputs();
  
  if (tick0 >= 25) {             // Run these subs at fixed rate
	  tick0 = 0;
	  ModelSelection();          // Model Selection
	  batterymonitor_auxpot();   // Battery check
	  readdigital();             // Read digital I/O
          HiMiLoRates();             // Rates
	  TrimSettings();            // Trims
	  ElevonModeSet();           // Elevon Mode
	  ExpoMode();                // Exponential Modes
	  PPMreassign();             // Re-assign PPM outputs
	  InvertChannel();           // Invert Channels
	  AuxSwitchThumbSet();       // Aux Sw max/min setting
	  ModeTesting();             // Mode Test
	  TimerDisplay();            // Timer
	  AuxPotTrimMode();          // AuxPOT 1&2, Trim Modes

	  // Function button processing
      if (DI_Onup_d == 1 && ModeTest == 0 && Timermode == 0) {
	     lcd.noCursor();
	     DI_Onup_d = 0;
	     buzzeractivate = 1;          // activate buzzer
	     LCDgoTo(0); Serial.print("   ");
	     ModeDispSet = ModeDispSet + 1;
		 if (ModeDispSet != 2 && ModeDispSet != 3) { clearLCD(); }
		 oneshot = 0;                 // reset oneshot var
	     if (ModeDispSet == 14) { ModeDispSet = 0; }
      }
      if (DI_Onup_a == 1 && ModeTest == 0 && Timermode == 0) {
	     lcd.noCursor();
	     DI_Onup_a = 0;
	     buzzeractivate = 1;          // activate buzzer
	     LCDgoTo(0); Serial.print("   ");
	     ModeDispSet = ModeDispSet - 1;
		 if (ModeDispSet != 1 && ModeDispSet != 2) { clearLCD(); }
		 oneshot = 0;                 // reset oneshot var
	     if (ModeDispSet == -1) { ModeDispSet = 13; }
      }	  
  }
  
  // Generate slow changing flag
  if (tick1 <= 100) {
	  slowflag = 0;
  }
  if (tick1 >= 100 && tick1 <=200) {
	  slowflag = 1;
  }
  if (tick1 >= 200) {
	  slowflag = 0;
	  tick1 = 0;
  } 

  // Generate sloooooow changing flag
  if (tick4 <= 600) {
	  slooowflag = 0;
  }
  if (tick4 >= 600 && tick4 <=1200) {
	  slooowflag = 1;
  }
  if (tick4 >= 1200) {
	  slooowflag = 0;
	  tick4 = 0;
  }
  
  // generate 1sec tick
  if (TimerStart == 1) {
      if (tick2 >= 240) {  // 1000mS
	      secflag++;
	      tick2 = 0;
      } 
      if (secflag >= 60) {
	      secflag = 0;
	      minflag++;
      }  
      if (minflag >= 100) {  // 100 mins reached, reset everything
	      minflag = 0;
		  secflag = 0;
      }
	  if (ReverseThrottle == 0) {
		  if (AI_Throt < (pulseMin + 10) && TimerInhibit == 1) {           // Throttle less than 1% so pause timer
			  secflag = secflaghold;
			  minflag = minflaghold;
		  }	else {
			  secflaghold = secflag;
			  minflaghold = minflag;
		  }
	  }
	  if (ReverseThrottle == 1) {
		  if (AI_Throt > (pulseMax - 10) && TimerInhibit == 1) {           // Throttle less than 1% so pause timer
			  secflag = secflaghold;
			  minflag = minflaghold;
		  }	else {
			  secflaghold = secflag;
			  minflaghold = minflag;
		  }
	  }	  
  
      } else {
	    tick2 = 0;
   }

}
