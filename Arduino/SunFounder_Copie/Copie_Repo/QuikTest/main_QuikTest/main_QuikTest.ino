/*
Please read the QuickTest_README.md file for instructions
*/

#include <Arduino.h>
#include <SoftPWM.h>
#include "soft_servo.h"
#include "SunFounder_AI_Camera.h"

#define WIFI_MODE WIFI_MODE_AP
#define SSID "GalaxyRVR"
#define PASSWORD "12345678"
#define PORT "8765"

#define NAME "GalaxyRVR"
#define TYPE "GalaxyRVR"

#define SERVO_PIN 6

AiCamera aiCam = AiCamera(NAME, TYPE);
SoftServo servo;
uint8_t servoAngle = 90;

void onReceive()
{
  int temp = aiCam.getSlider(REGION_D);
  if (servoAngle != temp)
  {
    servoAngle = constrain(temp, 0, 140);
  }
}

void setup(){
  Serial.begin(115200);
  Serial.println(F("Test_connection: starting..."));
  #if defined(ARDUINO_AVR_UNO)
    SoftPWMBegin();
  #endif
  servo.attach(SERVO_PIN);
  servo.write(servoAngle);
  aiCam.begin(SSID, PASSWORD, WIFI_MODE, PORT);
  aiCam.setOnReceived(onReceive);
  Serial.println(F("Ready."));
}

void loop(){
  aiCam.loop();
  servo.write(servoAngle);
}
