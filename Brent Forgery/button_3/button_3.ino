
/* 
 DESCRIPTION
 ====================
 Simple example of the Bounce library that switches the debug LED when 
 either of 2 buttons are pressed.
 */
 
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define BUTTON_PIN_1 52
#define BUTTON_PIN_2 50
#define DEBOUNCE_TIME 30

// Instantiate a Bounce object
Bounce debouncer1 = Bounce(); 

// Instantiate another Bounce object
Bounce debouncer2 = Bounce(); 

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:    
  
  // After setting up the button, setup the Bounce instance :
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(DEBOUNCE_TIME); // interval in ms
  
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(DEBOUNCE_TIME); // interval in ms

}

void loop() {
  delay(10);
  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();
  
  if(debouncer1.read() == HIGH) {  Serial.println("button 1 pressed"); }
  if(debouncer2.read() == HIGH) {  Serial.println("button 2 pressed"); }


}


