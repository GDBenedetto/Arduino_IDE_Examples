#include <Arduino.h>

int switchState = 0; // Speichert Zustand des Tasters (HIGH/LOW)

void setup() {

  // Konfiguriert Pins: LEDs als Ausgang, Taster als Eingang
  pinMode(3, OUTPUT); // grüne LED
  pinMode(4, OUTPUT); // rote LED (links)
  pinMode(5, OUTPUT); // rote LED (rechts)
  pinMode(2, INPUT);  // Taster

}

void loop() {
  
  // Liest den aktuellen Zustand des Tasters
  switchState = digitalRead(2);

  if (switchState == LOW) { // Taster nicht gedrückt (Idle-Modus)

    digitalWrite(3, HIGH); // grüne LED EIN
    digitalWrite(4, LOW);  // rote LEDs AUS
    digitalWrite(5, LOW);

  } else { // Taster gedrückt (Aktiv-Modus)
    
    digitalWrite(3, LOW);  // grüne LED AUS

    digitalWrite(4, LOW);  
    digitalWrite(5, HIGH); // erste rote LED EIN

    delay(250); // Wartezeit (Blinkintervall)
    
    // LEDs wechseln (Blinken)
    digitalWrite(4, HIGH); // zweite rote LED EIN
    digitalWrite(5, LOW);
    
    delay(250); // Wartezeit

  }
}