/*

  Debounce
  Language: Arduino
  Author: Michael Naish
  Date: 23/01/22

  This code will use a pin change interrupt debounce a mechanical button/switch connected to a GPIO
  pin. It is assumed that the button is connected to ground. An internal pullup resistor will be 
  enabled to prevent a "floating" input. Using a normally-open pushbutton, the normal state on the 
  input pin will be high, going low when the button is pressed (high to low transistion).

  Rev 1 - Initial version 
  
*/

#define BUTTON 0                                   // select the GPIO pin for button
#define DEBOUNCE 250                               // debounce interval in milliseconds
                                                 
volatile unsigned long button_time = 0;            // time of button press in ms
volatile unsigned long last_button_time = 0;       // time of last button press in ms
uint32_t numberPresses = 0;                        // counter for number of button presses
bool pressed = false;                              // state variable to indicate "valid" button press

// Interrupt service routine
void IRAM_ATTR isr() {
  button_time = millis();                          // capture current time
  if (button_time - last_button_time > DEBOUNCE) { // if enough time has passed to consider a valid press
    numberPresses++;                               // increment button press counter
    pressed = true;                                // indicate valid button press state
    last_button_time = button_time;                // update time to measure next press against
  }
}

void setup() {
  Serial.begin(115200);                            // start serial communications at 115200 baud
  pinMode(BUTTON, INPUT_PULLUP);                   // set GPIO pin as input with internal pullup enabled
  attachInterrupt(BUTTON, isr, FALLING);           // attach ISR for button, triggering on a falling edge
}

void loop() {
  if (pressed) {                                   // if button state is true, send serial output
    Serial.printf("Button has been pressed %u times\n", numberPresses);
    pressed = false;                               // reset button state
  }
}


