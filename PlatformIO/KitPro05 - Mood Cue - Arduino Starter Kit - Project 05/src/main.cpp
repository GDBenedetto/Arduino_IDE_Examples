#include <Arduino.h>


// include the Servo library
#include <Servo.h>

Servo myServo;  // create a servo object

int const potPin = A0;  // (Analog Input)analog pin used to connect the potentiometer Analog in pins A0-A5 can report back a value between 0-1023 (10 bit), which maps to a range from 0 volts to 5 volts. 
int potVal;             // variable to read the value from the analog pin
int angle;              // variable to hold the angle for the servo motor

void setup() {
  myServo.attach(9);   // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);  // open a serial connection to your computer
}

void loop() {
  potVal = analogRead(potPin);  // read the value of the potentiometer
  
  // print out the value to the Serial Monitor
  Serial.print("potVal: ");
  Serial.print(potVal);
  Serial.print("\t potPin: ");
  Serial.print(analogRead(potPin));

  // scale the numbers from the pot
  angle = map(potVal, 0, 1023, 0, 179);

  // print out the angle for the servo motor
  Serial.print(", angle: ");
  Serial.println(angle);

  // set the servo position
  myServo.write(angle);

  // wait for the servo to get there
  delay(50);
}

