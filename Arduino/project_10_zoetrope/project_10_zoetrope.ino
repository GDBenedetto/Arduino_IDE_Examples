// ============================================================
// Arduino Starter Kit – Project 10: Zoetrope
// ============================================================
// Funktion:
//   Steuerung eines DC‑Motors über einen H‑Bridge.
//   - Ein/Aus‑Schalter
//   - Richtungsschalter
//   - Potentiometer für die Geschwindigkeit
//
// Hardware:
//   - Arduino Uno
//   - H‑Bridge IC
//   - DC‑Motor
//   - 2 Taster (On/Off, Richtung)
//   - 10 kΩ Pull‑Down‑Widerstände
//   - Potentiometer
//   - 9 V Batterie für den Motor
// ============================================================

// ------------------------------------------------------------
// 1. Pin‑Definitionen (Konstanten)
// ------------------------------------------------------------

const int controlPin1 = 2;        // H‑Bridge Control Pin 1
const int controlPin2 = 3;        // H‑Bridge Control Pin 2
const int enablePin   = 9;        // H‑Bridge Enable (PWM)

const int directionSwitchPin = 4; // Schalter für Drehrichtung
const int onOffSwitchStateSwitchPin = 5; // Schalter für Ein/Aus
const int potPin = A0;            // Potentiometer für Geschwindigkeit

// ------------------------------------------------------------
// 2. Globale Variablen (Zustand)
// ------------------------------------------------------------

int motorEnabled = 0;     // 0 = aus, 1 = ein
int motorSpeed   = 0;     // 0–255 (PWM)
int motorDirection = 0;   // 0 = vorwärts, 1 = rückwärts

int onOffSwitchState = 0;
int directionSwitchState = 0;
int lastDirectionSwitchState = 0;

// ------------------------------------------------------------
// 3. setup()
// ------------------------------------------------------------

void setup() {
  // Eingänge
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);

  // Ausgänge (H‑Bridge)
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Motor initial aus
  digitalWrite(enablePin, LOW);

  // Optional: Serial für Debugging
  Serial.begin(9600);
}

// ------------------------------------------------------------
// 4. loop()
// ------------------------------------------------------------

void loop() {
  // 4.1 Schalter auslesen
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin) / 4;  // 0–1023 → 0–255

  // 4.2 Ein/Aus‑Logik
  if (onOffSwitchState == HIGH) {
    motorEnabled = 1;
  } else {
    motorEnabled = 0;
    digitalWrite(enablePin, LOW);  // Motor sicher aus
  }

  // 4.3 Richtung einmal beim Drücken ändern, nicht beim Loslassen
  if (directionSwitchState != lastDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;  // umschalten
    }
    lastDirectionSwitchState = directionSwitchState;
    delay(50);  // einfacher Prellschutz
  }

  // 4.4 Motor ansteuern, wenn enabled
  if (motorEnabled) {
    if (motorDirection == 0) {
      // Vorwärts
      digitalWrite(controlPin1, HIGH);
      digitalWrite(controlPin2, LOW);
    } else {
      // Rückwärts
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2, HIGH);
    }
    analogWrite(enablePin, motorSpeed);
  }

  // 4.5 Optional: Status auf Serial ausgeben (zum Lernen / Debuggen)
  Serial.print("Enabled: ");
  Serial.print(motorEnabled);
  Serial.print(" | Direction: ");
  Serial.print(motorDirection);
  Serial.print(" | Speed: ");
  Serial.println(motorSpeed);

  delay(10);  // kleine Stabilisierungszeit
}