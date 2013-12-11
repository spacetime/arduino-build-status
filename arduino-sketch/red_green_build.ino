/*
  Modified from: Physical Pixel and Fade (examples)
  http://www.arduino.cc/en/Tutorial/PhysicalPixel
  http://www.arduino.cc/en/Tutorial/Fade
 
 The circuit:
 * RGB LED cathodes at pin 9 (PWM required)
 * RGB LED Red Anode at pin 6 
 * RGB LED Green Anode at pin 7
 
 created December 3 2013
 Author: Rishab Arora (spacetime)
 */

const int common_cathode = 9; // the pin that the LED is attached to
const int green_led = 6;
const int red_led = 7;

int incomingByte;      // a variable to read incoming serial data into
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int led = common_cathode;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pins as an output:
  pinMode(common_cathode, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  // initialize state as red
  digitalWrite(red_led, 1);   
  digitalWrite(green_led, 0);
  
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();

    // if it's a capital H (Build is red), turn the LEDs red:
    if (incomingByte == 'H') {
      digitalWrite(red_led, 0); 
      digitalWrite(green_led, 1); 
    } 

    // if it's a capital C (Compiling), turn the LEDs red+green:
    if (incomingByte == 'C') {
      digitalWrite(red_led, 0); 
      digitalWrite(green_led, 0); 
    }

    // if it's a capital L (Build is green), turn the LEDs green:
    if (incomingByte == 'L') {
      digitalWrite(red_led, 1); 
      digitalWrite(green_led, 0); 
    }
  }
  blink_n_times();
}

void blink_n_times() {
  for (int i = 0; i < 10; i = i+1) {
    bright_loop();
  }  

  digitalWrite(common_cathode, LOW);
}

void bright_loop()  { 
  // set the brightness of pin 9:
  analogWrite(led, brightness);    
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 100) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 50 milliseconds to see the dimming effect    
  delay(50);                            
}

