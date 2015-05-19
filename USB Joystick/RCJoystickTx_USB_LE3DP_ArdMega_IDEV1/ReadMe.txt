HARDWARE
================================
  Arduino MEGA 2560 (will not work with other Arduino's)
  LRS Tx module (Thomas Scherrer's system) or any other system using compatible PPM input.
  12vdc battery (i.e. 1500mah 3S Lipo)
  Logitech Extreme 3D Pro Joystick (uses USB interface)
  USB Host Shield (P/N=DFRobot DFR0138 or Circuits@Home Rev 2.0)
  LCD - Parallel mode Hitachi HD44780 or compatible. Used in 4-bit mode and using LiquidCrystal library

PPM Channels:
  PPM Ch.1 - Aeleron  - Elevon mix Aeleron 1 (Invert mode) (Exponential mode)
  PPM Ch.2 - Elevator - Elevon mix Aeleron 2 (Invert mode) (Exponential mode)
  PPM Ch.3 - Throttle -                      (Invert mode)
  PPM Ch.4 - Rudder   -                      (Invert mode) (Exponential mode)
  PPM Ch.5 - Aux switch 1
  PPM Ch.6 - Aux switch 2
  PPM Ch.7 - Aux potentiometer 1
  PPM Ch.8 - Aux potentiometer 2
  (Note: PPM channels can be re-assigned)
  
Physical Analogue Inputs pins:
  Pin 0 = Battery Voltage (2.2v at input to display 12.6v)

Physical Digital Output pins:
  Pin 13 = Buzzer
  Pin 12 = PPM
  Pin 2  = LCD D7
  Pin 3  = LCD D6
  Pin 4  = LCD D5
  Pin 5  = LCD D4
  Pin 6  = LCD RS
  Pin 7  = LCD ENABLE

  
SOURCE CODE NOTES
================================
ModeDispSet pointer:
  1  trim setting AEL
  2  trim setting ELE
  3  trim setting RUD
  4  elevon mode
  5  exponential AE,EL,RU mode
  6  invert AE,EL,RU,TH mode
  7  auxsw thumb set
  8  auxsw trigger set
  9  raw/ppm mode test
  10 test mode
  11 Pan & Tilt
  12 Model Selection
  13 Timer

EEprom Addresses:
  0  = Aeleron Lo Rates
  1  = Elevator Lo Rates
  2  = Rudder Lo Rates
  3  = Aeleron Mi Rates
  4  = Elevator Mi Rates
  5  = Rudder Mi Rates
  6  = Aeleron Hi Rates
  7  = Elevator Hi Rates
  8  = Rudder Hi Rates
  20 = Elevon Mode
  22 = Expo. Aeleron
  23 = Expo. Elevator
  24 = Expo. Rudder
  32 = Invert Aeleron
  33 = Invert Elevator
  34 = Invert Rudder
  35 = Invert Throttle
  36 = Aux Sw1 setting
  37 = Aux Sw2 setting
  38 = Aux Pot1 setting (low byte)
  39 = Aux Pot1 setting (high byte)
  40 = Aux Pot2 setting (low byte)
  41 = Aux Pot2 setting (high byte)  
  48 = Thumb button 0%/100%
  49 = Trigger button 0%/100%
  50 = Pan & Tilt / Trim mode
  61 = PPM Channel 1 assignment
  62 = PPM Channel 2 assignment
  63 = PPM Channel 3 assignment
  64 = PPM Channel 4 assignment
  65 = PPM Channel 5 assignment
  66 = PPM Channel 6 assignment
  67 = PPM Channel 7 assignment
  68 = PPM Channel 8 assignment
  1000 = Current Model Selection

  Notes:
  1. EEprom addresses 0 to 8 use pointers.
  2. Addresses 0-68 are duplicated at 100-168, 200-268 & 300-368 for the 4 Models (see address 1000)
  

PPM TIMING INFO
================================
PPM example - 8ch * (1700mS + 300mS) = 16000mS max, therefore 22500 - 16000 = 6500mS sync pulse minimum.

Standard ( =< 9 Channel) PPM Frame Spec is 22.5mS (22500uS)

Each frame consists of 4 to 9 channels (5 to 10 pulses),
700uS to 1700uS in length followed by a sync gap >250uS
in length..

The width of each channel is 1 to 2mS (1.5mS when sticks centered).
The sync gap is at least 2.5mS long,
The frame length is approximately 22.5 mS (22500 uS).

The output signal should look something like this:-

           |<---------------- 1 frame (~22.5mS) ---------------->|
           |< 1~2mS >|                                
            _         _        _        _        _                _
___________| |_______| |______| |______| |______| |______________| |____
sync gap   ch1       ch2      ch3      ch4      etc.  sync gap   ch1
     
9 Channels should take a maximum of 18mS (18000uS) leaving
4.5mS (450uS) for syncronization.

NOTES

(1)    PPM frame period duration is not critical and depends on
       RC Transmitter type & Manufacturer.

       JR/Graupner, Sanwa/Airtronics use POSITIVE shift

       Futaba, Hitec, Tower Hobbies use NEGATIVE shift

(2)    Frame separation sync gap depends on number of transmitter
       channels and will vary accordingly.


  