int button_pressed(){
  
  static int pin1 = 52;
  static int buttonState1;             // the current reading from the input pin
  static int lastButtonState1 = LOW;   // the previous reading from the input pin
  static long lastDebounceTime1 = 0;  // the last time the output pin was toggled
  static long debounceDelay = 50;    // the debounce time; increase if the output flickers
  
  // read the state of the button into a local variable:
  int reading = digitalRead(pin1);
  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  } 
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state
    // if the button state has changed:
    if (reading != buttonState1) {
      buttonState1 = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        Serial.println("pressed"); 
      }
    }
  }
  lastButtonState1 = reading;
  
}
