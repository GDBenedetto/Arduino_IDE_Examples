# Arduino Starter Kit – Project 10: Zoetrope  
## Vollständige technische Projektbeschreibung

---

## 1. Projektübersicht

Das **Zoetrope** ist ein mechanisches Animationsgerät, das aus einer Folge von Standbildern eine scheinbare Bewegung erzeugt („persistence of vision“, POV).  
In diesem Projekt wird ein **DC‑Motor** über eine **H‑Bridge (L293D)** angesteuert, um eine mit Schlitzen versehene Scheibe (CD + Papierstreifen) zu drehen.

**Steuerfunktionen:**

- Ein/Aus‑Schalter für den Motor
- Richtungsschalter (vorwärts / rückwärts)
- Potentiometer zur Einstellung der Drehgeschwindigkeit

Das Projekt demonstriert:

- Ansteuerung eines DC‑Motors in beide Richtungen
- Nutzung einer H‑Bridge als integrierte Schaltung
- Digitale Eingänge (Taster) und analoge Eingänge (Potentiometer)
- PWM‑Steuerung der Motordrehzahl

---

## 2. Beteiligte Komponenten

### 2.1 Aktoren

| Komponente        | Beschreibung                                      |
|-------------------|---------------------------------------------------|
| DC‑Motor          | Kleiner Gleichstrommotor, 6–9 V (im Kit enthalten) |
| Zoetrope‑Scheibe  | CD mit aufgesetztem Schlitz‑Zylinder + Bildstreifen |

### 2.2 Steuerung & Logik

| Komponente        | Beschreibung                                      |
|-------------------|---------------------------------------------------|
| Arduino Uno       | Mikrocontroller‑Board (ATmega328P, 5 V Logik)     |
| H‑Bridge IC       | L293D (Dual H‑Bridge Motor Driver)                |

### 2.3 Eingabeelemente

| Komponente           | Beschreibung                                 |
|----------------------|----------------------------------------------|
| Taster (Pushbutton)  | 2× Momentary Switch (Schließer)              |
| Potentiometer        | 10 kΩ linear (Drehregler)                    |
| Widerstände          | 2× 10 kΩ (Pull‑Down für Taster)              |

### 2.4 Stromversorgung

| Komponente           | Beschreibung                                 |
|----------------------|----------------------------------------------|
| 9 V‑Blockbatterie    | Versorgung des Motors über H‑Bridge          |
| 9 V‑Batterieclip     | Anschluss an Breadboard‑Power‑Rails          |
| USB‑Kabel            | 5 V‑Versorgung und Programmierung des Arduino |

> Wichtig: Die **9 V‑Motorversorgung** und die **5 V‑Arduino‑Versorgung** dürfen sich nur über **GND** verbinden. Die positiven Leitungen (9 V vs. 5 V) müssen getrennt bleiben.

---

## 3. Schnittstellen und Pin‑Belegung

### 3.1 Arduino ↔ H‑Bridge (L293D)

**L293D Pinout (DIP‑16, relevant für dieses Projekt):**

- Pin 1: `1,2EN` – Enable für Motor 1 (PWM‑Eingang)
- Pin 2: `1A` – Logikeingang 1 für Motor 1
- Pin 3: `1Y` – Motorausgang 1
- Pin 4: `GND` – Masse (Logik/Steuerung)
- Pin 5: `GND` – Masse (Logik/Steuerung)
- Pin 6: `2Y` – Motorausgang 2
- Pin 7: `2A` – Logikeingang 2 für Motor 1
- Pin 8: `VS` – Motoren‑Versorgungsspannung (9 V)
- Pin 9: `3,4EN` – Enable für Motor 2 (hier nicht genutzt)
- Pin 10–15: für Motor 2 (hier nicht genutzt)
- Pin 16: `VSS` – Logik‑Versorgung (5 V)

**Verbindung Arduino ↔ L293D:**

| L293D‑Pin | Funktion          | Arduino‑Pin | Beschreibung                            |
|----------|-------------------|-------------|-----------------------------------------|
| 1        | `1,2EN` (Enable)  | 9 (PWM)     | PWM‑Signal für Motordrehzahl            |
| 2        | `1A` (Input 1)    | 3           | Logik‑Input 1 für Drehrichtung          |
| 3        | `1Y` (Output 1)   | –           | Motoranschluss (+)                      |
| 4,5      | `GND`             | GND         | Gemeinsame Masse (Logik)                |
| 6        | `2Y` (Output 2)   | –           | Motoranschluss (−)                      |
| 7        | `2A` (Input 2)    | 2           | Logik‑Input 2 für Drehrichtung          |
| 8        | `VS` (Motor‑VCC)  | 9 V (Batt+) | Motor‑Versorgung (separate 9 V‑Schiene) |
| 16       | `VSS` (Logic‑VCC) | 5 V         | Logik‑Versorgung der H‑Bridge           |

### 3.2 Arduino ↔ Eingabeelemente

#### Taster (2×)

Jeder Taster hat:

- Eine Seite an **+5 V**
- Andere Seite an:
  - Arduino‑Digital‑Pin (als Eingang)
  - 10 kΩ Pull‑Down‑Widerstand nach **GND**

| Taster              | Arduino‑Pin | Funktion                        |
|---------------------|-------------|---------------------------------|
| On/Off‑Taster       | 5           | Motor läuft, solange der Taster gedrückt ist |
| Richtungs‑Taster    | 4           | Wechselt Drehrichtung           |

Schaltung pro Taster:

- `5 V` → Taster‑Pin 1  
- Taster‑Pin 2 → `Digital Pin` (4 oder 5) **und** über 10 kΩ nach `GND`

#### Potentiometer (10 kΩ)

| Potentiometer‑Anschluss | Verbindung     | Beschreibung                         |
|-------------------------|----------------|--------------------------------------|
| Außenlinks              | 5 V            | Versorgung                           |
| Außenrechts             | GND            | Masse                                |
| Mittelanschluss (Schleifer) | A0 (Analog In) | Spannungsteiler für Geschwindigkeit |

Der Arduino liest über `A0` einen Wert von 0–1023, der auf 0–255 (PWM) skaliert wird.

### 3.3 Arduino ↔ Motor (über H‑Bridge)

Der Motor wird nicht direkt am Arduino, sondern an der H‑Bridge angeschlossen:

| Motor‑Anschluss | L293D‑Pin | Beschreibung                      |
|-----------------|-----------|-----------------------------------|
| Motor +         | 3 (`1Y`)  | Ausgang 1 der H‑Bridge            |
| Motor −         | 6 (`2Y`)  | Ausgang 2 der H‑Bridge            |

Die Polarität an den Ausgängen 3 und 6 wird durch die Logik‑Inputs 2 und 7 gesteuert.

---

## 4. Vollständige Schaltbeschreibung

### 4.1 Stromversorgung

1. **Arduino‑Versorgung:**
   - Über USB (5 V) oder Vin (extern 7–12 V, falls verwendet)
   - 5 V‑Schiene auf dem Breadboard wird vom Arduino‑5 V‑Pin gespeist.

2. **Motor‑Versorgung:**
   - 9 V‑Batterieclip an separates Power‑Rail‑Paar auf dem Breadboard.
   - `+9 V` → Pin 8 (`VS`) der L293D.
   - `GND` der 9 V‑Batterie → `GND`‑Schiene des Breadboards → `GND` des Arduino.
   - **Nur GND** ist zwischen 9 V‑ und 5 V‑Seite gemeinsam.

3. **Logik‑Versorgung der H‑Bridge:**
   - Pin 16 (`VSS`) der L293D → 5 V‑Schiene (vom Arduino).
   - Pins 4 und 5 (`GND`) der L293D → GND‑Schiene.

### 4.2 Digitale Eingänge (Taster)

Für **beide** Taster identisch:

- Ein Taster‑Pin → `5 V`
- Anderer Taster‑Pin → 
  - Arduino‑Digital‑Pin (4 oder 5)
  - Parallel dazu: 10 kΩ Widerstand nach `GND` (Pull‑Down)

Dadurch:

- Taster offen → Pin liest `LOW` (durch Pull‑Down)
- Taster gedrückt → Pin liest `HIGH` (direkt mit 5 V verbunden)

### 4.3 Analogeingang (Potentiometer)

- Potentiometer außen links → `5 V`
- Potentiometer außen rechts → `GND`
- Potentiometer Mitte → `A0`

Der Arduino liest eine Spannung zwischen 0 und 5 V als digitalen Wert 0–1023.

### 4.4 H‑Bridge Ansteuerung

**Logik‑Signale vom Arduino:**

- `controlPin1 = 2` → L293D Pin 7 (`2A`)
- `controlPin2 = 3` → L293D Pin 2 (`1A`)
- `enablePin = 9` → L293D Pin 1 (`1,2EN`)

**Funktionsweise:**

- `controlPin1 = HIGH`, `controlPin2 = LOW`  
  → Motor dreht in Richtung „vorwärts“
- `controlPin1 = LOW`, `controlPin2 = HIGH`  
  → Motor dreht in Richtung „rückwärts“
- Beide gleich (`HIGH/HIGH` oder `LOW/LOW`)  
  → Motor stoppt (Bremsen / Freilauf, je nach H‑Bridge‑Design)
- `enablePin` per PWM (0–255)  
  → Bestimmt die effektive Motorspannung und damit die Drehzahl

---

## 5. Technischer Ablauf (Software‑Logik)

### 5.1 Konstanten und Variablen

**Pin‑Konstanten:**

```cpp
const int controlPin1 = 2;         // L293D Pin 7
const int controlPin2 = 3;         // L293D Pin 2
const int enablePin   = 9;         // L293D Pin 1 (PWM)

const int directionSwitchPin = 4;  // Taster Richtung
const int onOffSwitchStateSwitchPin = 5; // Taster Ein/Aus

const int potPin = A0;             // Potentiometer
```

**Zustandsvariablen:**

```cpp
int motorEnabled = 0;      // 0 = aus, 1 = ein
int motorSpeed   = 0;      // 0–255 (PWM)
int motorDirection = 0;    // 0 = vorwärts, 1 = rückwärts

int onOffSwitchState = 0;
int directionSwitchState = 0;
int lastDirectionSwitchState = 0;
```

### 5.2 Initialisierung (`setup()`)

- Setze `directionSwitchPin` und `onOffSwitchStateSwitchPin` als `INPUT`.
- Setze `controlPin1`, `controlPin2`, `enablePin` als `OUTPUT`.
- Schalte `enablePin` initial auf `LOW` (Motor aus).

### 5.3 Hauptschleife (`loop()`)

1. **Eingänge lesen:**
   - `onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin)`
   - `directionSwitchState = digitalRead(directionSwitchPin)`
   - `motorSpeed = analogRead(potPin) / 4` (0–1023 → 0–255)

2. **Motorfreigabe über den Ein/Aus‑Taster:**
  - Solange `onOffSwitchState == HIGH` ist, wird `motorEnabled = 1` gesetzt.
  - Bei `LOW` wird `motorEnabled = 0` gesetzt und der Motortreiber ausgeschaltet.

3. **Drehrichtung beim Drücken ändern:**
  - Der aktuelle Tasterwert wird mit `lastDirectionSwitchState` verglichen.
  - Wenn der Taster jetzt gedrückt ist und zuvor losgelassen war, wird
    `motorDirection` umgeschaltet.
  - Danach wird der aktuelle Wert in `lastDirectionSwitchState` gespeichert.
  - Gedrückt halten oder Loslassen löst keinen weiteren Richtungswechsel aus.

4. **H‑Bridge‑Signale setzen:**
   - Wenn `motorDirection == 1`:
     - `controlPin1 = HIGH`, `controlPin2 = LOW`
   - Sonst:
     - `controlPin1 = LOW`, `controlPin2 = HIGH`

5. **Motor‑Enable / PWM:**
   - Wenn `motorEnabled == 1`:
     - `analogWrite(enablePin, motorSpeed)`
   - Bei `LOW` setzt die Ein/Aus‑Logik `enablePin` auf `LOW`.

6. **Zustände speichern** für nächsten Durchlauf.

---

## 6. Mechanischer Aufbau (Zoetrope)

1. **CD als Träger:**
   - CD fest auf der Motorwelle befestigen (ggf. mit etwas Kleber oder Reibschluss).
2. **Schlitz‑Zylinder:**
   - Aus dem mitgelieferten Papier‑/Kartonzuschnitt einen Zylinder mit vertikalen Schlitzen formen.
   - Zylinder auf der CD befestigen (zentriert).
3. **Bildstreifen:**
   - Den bedruckten Streifen mit den Einzelbildern innen in den Zylinder kleben.
4. **Motorhalterung:**
   - Motor auf einer stabilen Unterlage fixieren (z. B. kleine Box mit Loch für die Welle).
5. **Betrieb:**
   - Bei Drehung durch die Schlitze schauen → scheinbare Bewegung der Bilder.

---

## 7. Technische Kennwerte (typisch)

| Größe                      | Wert / Bereich                         |
|----------------------------|----------------------------------------|
| Arduino‑Logikspannung      | 5 V (digital), 0–5 V (analog)          |
| L293D Logik‑VCC (`VSS`)    | 4.5–7 V (hier 5 V vom Arduino)         |
| L293D Motor‑VCC (`VS`)     | 4.5–36 V (hier 9 V‑Batterie)           |
| Max. Dauerstrom pro Kanal  | ca. 600 mA (L293D, abhängig von Kühlung) |
| DC‑Motor (Kit)             | 6–9 V, typ. < 500 mA im Leerlauf       |
| Potentiometer              | 10 kΩ linear                           |
| Taster‑Pull‑Down           | 10 kΩ                                  |
| PWM‑Frequenz (Pin 9)       | ca. 490 Hz (Arduino Uno, Standard)     |

---

## 8. Sicherheitshinweise

- **9 V‑Batterie erst im letzten Schritt anschließen**, nachdem alle Verbindungen geprüft sind.
- Sicherstellen, dass:
  - 9 V‑Positive **nicht** mit 5 V‑Positive verbunden ist.
  - Nur **GND** gemeinsam ist.
- Motorwelle und Zoetrope‑Zylinder nicht im Betrieb berühren (Verletzungs‑/Quetschgefahr).
- Bei längerem Betrieb auf Erwärmung der H‑Bridge achten (kann warm werden).

---

## 9. Zusammenfassung der Schnittstellen

| Schnittstelle          | Typ            | Signale / Werte                     |
|------------------------|----------------|-------------------------------------|
| Arduino → H‑Bridge     | Digital / PWM  | `controlPin1` (2), `controlPin2` (3), `enablePin` (9, PWM) |
| Arduino ← Taster       | Digital In     | `directionSwitchPin` (4), `onOffSwitchStateSwitchPin` (5) |
| Arduino ← Potentiometer| Analog In      | `potPin` (A0), Wert 0–1023          |
| H‑Bridge → Motor       | Leistung       | 0–9 V, bis ca. 600 mA               |
| 9 V‑Batterie → H‑Bridge| Leistung       | 9 V, Masse gemeinsam mit Arduino    |




# Projektstruktur

```txt
project_10_zoetrope/
  project_10_zoetrope.ino
  README.md
  docs/
    schaltplan.png        (oder .fzz / .svg)
    aufbau.txt
  extras/
    original_code.ino     (optional: unveränderter Originalcode als Referenz)
```