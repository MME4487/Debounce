#define BUTTON 0
#define DEBOUNCE 250

volatile unsigned long button_time = 0;
volatile unsigned long last_button_time = 0;
uint32_t numberPresses = 0;
bool pressed = false;

void IRAM_ATTR isr() {
  button_time = millis();
  if (button_time - last_button_time > DEBOUNCE) {
    numberPresses++;
    pressed = true;
    last_button_time = button_time;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(BUTTON, isr, FALLING);
}

void loop() {
  if (pressed) {
    Serial.printf("Button has been pressed %u times\n", numberPresses);
    pressed = false;
  }
}


