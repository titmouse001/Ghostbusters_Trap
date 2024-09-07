#include <Servo.h>

/*
 * This sketch mainly controls servos operating the doors of a Ghostbusters Trap.
 * 
 * Two servos, servo_A and servo_B (connected to pins 8 and 9), move the doors in opposite directions.
 * Manual operation and a demo mode (demo opens/closes doors randomly) are included. 
 *
 * Demo is triggered by holding the button during startup, a 2nd press cancles the demo for normal operation.
 * The demo mode's activation duration is influenced by how long you hold the foot pedal
 * during power-up, with a factor of 4. For example, holding the foot pedal for 
 * 2 seconds results in an 8-second hidden wait before demo activation.
 *
 * Pin 3 detects a foot pedal input: press to open, release to close.
 *
 * NEW: feature added to control a bright strobe LED COB (Chip-on-Board) connected to pin 2.
 * The head torch/lamp behavior is somewhat odd, requiring three clicks to access the flashing mode.
 * To enable head torch/lamp control, two thin wires have been soldered to the switch poles and 
 * connected to the Arduino Pro Mini's pin 2 and ground pins.
 */


/*
 * Arduino pin assignment
 */
#define _FOOT_PEDAL_PIN  (3) // Foot pedal
#define _COB_CONTROL_PIN (2) // Signal for strobe/flasher

/*
 *Servo limits
 */
#define _START (1055)        // Initial position (closed)
#define _END   (1695)        // Fully open position

/*
 * Using Arduino Servo linrary, 
 * see https://github.com/arduino-libraries/Servo for details
 */
Servo servo_A;  
Servo servo_B;

volatile bool buttonPressed = false;  // set true in the interrupt serive routine 'buttonISR' 
bool demoMode = false;                // hold down _FOOT_PEDAL_PIN at startup to active demo

/*
 * Notes about writeMicroseconds() used in this sketch:
 * Sends a value in microseconds (us) to the servo, controlling its position accordingly.
 * For a standard servo, a value of 1000 corresponds to fully counter-clockwise, 
 * 2000 to fully clockwise and 1500 to the middle position.
 * However, it's important to note that some manufacturers may deviate from this standard, causing 
 * servos to respond to values between 700 and 2300.
 */

void setup() {
 // Serial.begin(9600); Serial.println("!!!LOGGING IS ON - TUNR ME OFF FOR RELEASE!!!");

  /*
   * Assign an arduino pin to each servo
   */
  servo_A.attach(8, _START, _END); 
  servo_B.attach(9, _START, _END);
  /* 
   * Upon powering up, we ensure the doors are closed initially.
   * Note: The code rotates each servo in opposite directions because both servos 
   * share the same alignment orientation, but the two door mechanisms require opposite rotations.
   */
  servo_A.writeMicroseconds(_START);
  servo_B.writeMicroseconds(_END);

  /*
   * Setup Arduino pin directions
   */
  pinMode(_FOOT_PEDAL_PIN, INPUT_PULLUP);   // to conrol doors
  pinMode(_COB_CONTROL_PIN, OUTPUT);        // active head lamp

  /*
   * ISR: Capture button state changes without needing to loop in the main program.
   */
  attachInterrupt(digitalPinToInterrupt(_FOOT_PEDAL_PIN), buttonISR, FALLING);

  int buttonPressStartTime = millis();

  // LOW = button down , HIGH = button up
  // When button held enalbe demo mode at power on
  if (digitalRead(_FOOT_PEDAL_PIN) == LOW) {
    demoMode = true;
  }
  if (demoMode) {
    // allows user to setup and active a hide and wait depending on initial press
    while (digitalRead(_FOOT_PEDAL_PIN) == LOW) {  // Wait for button release
      delay(1);
    }
    int buttonHoldDuration = millis() - buttonPressStartTime;
    delay(buttonHoldDuration * 4);
    // Serial.println(buttonHoldDuration);
  }

  buttonPressed = false;
}

void loop() {
  if (demoMode) {
    //Serial.println("demo");
    demo();
  } else {
    //Serial.println("normal operation");
    process();
  }
}

bool waitForButton (int rnd_wait_max) {
  int randNumber = random(rnd_wait_max);
  while (randNumber > 0) {
    randNumber -= 100;
    delay(100);
    if (buttonPressed)
      return true;
  }
  return false;
}

void demo() {
/* 
  * This function opens and closes the doors at random intervals and will 
  * continue indefinitely until stopped.
  * The specific values of 15000 and 5000 (in milliseconds) are not critical.
  * Adjust the values to prioritize longer waits before and after opening the doors.
  * Button press will immediately stop the demo and return to normal operation.
  */
  while (buttonPressed == false) {  // button down stops demo
    if (waitForButton (15000)) { break; }  
    for (int i = _START; i < _END; i++) {  // open doors
      servo_A.writeMicroseconds(i);
      servo_B.writeMicroseconds(_START + (_END - i));
    }
    if (waitForButton (5000)) { break; }
    for (int i = _END; i > _START; i--) {  //close doors
      servo_A.writeMicroseconds(i);
      servo_B.writeMicroseconds(_START + (_END - i));
    }
  }
  buttonPressed = false;
  demoMode = false;
}

void process() {
  /* 
  * '_FOOT_PEDAL_PIN' is configured with 'INPUT_PULLUP' mode, thus:
  *   - LOW: Button is pressed down
  *   - HIGH: Button is released
  */
  while (digitalRead(_FOOT_PEDAL_PIN) == HIGH) {  // wait for button down
    delay(1);
  }

  for (int i = _START; i < _END; i++) {  // open doors
    servo_A.writeMicroseconds(i);
    servo_B.writeMicroseconds(_START + (_END - i));
    delayMicroseconds(300);
  }
  
  HeadLampOn();

  while (digitalRead(_FOOT_PEDAL_PIN) == LOW) {  // Wait for button release
    delay(1);
  }

  for (int i = _END; i > _START; i--) {  //close doors
    servo_A.writeMicroseconds(i);
    servo_B.writeMicroseconds(_START + (_END - i));
    delayMicroseconds(300);
  }

  HeadLampOff();
}

void HeadLampOn() {
  pulseHeadLamp();
  pulseHeadLamp();
  pulseHeadLamp();
}

void HeadLampOff() {
  pulseHeadLamp();
}

void pulseHeadLamp() {
  /*
   * This is a cheap lamp that has a non-latching button click. 
   * It does not deliver voltage; it just tells a lamp chip to toggle 
   * through 3 modes then turn off on the 4th click.
   * 1 press: bright
   * 2 presses: dim
   * 3 presses: flashing
   * (Holding down for a while does the SOS thing)
   * EBAY: "COB LED Head Torch Headlamp Work Light Headlight Waterproof Outdoor Battery"
   */
  digitalWrite(_COB_CONTROL_PIN, HIGH);  // simulated button pressed
  delay(10);
  digitalWrite(_COB_CONTROL_PIN, LOW);  // button up
  delay(10);
}

void buttonISR() {
  buttonPressed = true;
  //  Serial.println("buttonISR");
}
