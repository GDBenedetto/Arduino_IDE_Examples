# System Requirements Specification (SRS)
## Spaceship Interface (Arduino Starter Kit – Project 02)

---

## 1. Introduction
This document specifies the system requirements for the *Spaceship Interface*.  
The system demonstrates basic embedded control using digital inputs and outputs.  
This specification follows guidelines from INCOSE, IEEE 29148:2018 and ISO/IEC/IEEE 15288.

---

## 2. Purpose
The system simulates a retro-style spaceship control panel.  
A push button controls LED indicators to represent system states.  
The goal is to demonstrate fundamental interaction between input and output signals using a microcontroller.

---

## 3. System Overview
The system consists of:
- 1 digital input (push button)
- 3 digital outputs (LEDs)

### Operating Modes
- **Idle Mode**: Green LED ON (system ready)
- **Active Mode**: Green LED OFF, red LEDs blinking alternately

---

## 4. System Context
The system runs on an Arduino Uno.  
User interaction occurs via a push button.  
Visual feedback is provided through LEDs.

---

## 5. Interface Requirements

| Type   | Pin | Component        | Description                          |
|--------|-----|------------------|--------------------------------------|
| Input  | D2  | Push Button      | Triggers mode switching              |
| Output | D3  | Green LED        | Indicates idle mode                  |
| Output | D4  | Red LED (left)   | Blinks in active mode                |
| Output | D5  | Red LED (right)  | Alternates with D4                   |

---

## 6. Functional Requirements

- **FR-001**: The system shall read the state of the push button on pin D2.  
- **FR-002**: The system shall activate the green LED (D3) when the button is not pressed.  
- **FR-003**: The system shall deactivate the green LED when the button is pressed.  
- **FR-004**: The system shall alternately (de: abwechselnd) blink red LEDs (D4, D5) with a period of 250 ms when the button is pressed.  
- **FR-005**: The system shall return to idle mode when the button is released.  

---

## 7. Behavioral Requirements

- **BR-001**: In idle mode, the green LED shall remain continuously ON.  
- **BR-002**: In active mode, the system shall toggle between the two red LEDs every 250 ms.  
- **BR-003**: Mode transitions shall occur immediately upon button state change.  

---

## 8. Non-Functional Requirements

- **NFR-001**: The system shall respond to input changes within 50 ms.  
- **NFR-002**: The blink timing tolerance shall be ±10%.  
- **NFR-003**: The system shall operate continuously without failure under normal conditions.  

---

## 9. Assumptions and Constraints

- The system uses fixed digital pins (D2–D5).  
- The hardware platform is limited to Arduino Uno.  
- No debouncing mechanism is required (basic implementation).  

---

## 10. Verification Methods

| Requirement | Method        | Description                          |
|-------------|--------------|--------------------------------------|
| FR-001–005  | Test         | Functional test using hardware       |
| BR-001–003  | Observation  | Visual verification of LED behavior  |
| NFR-001–002 | Measurement  | Timing verification (e.g. oscilloscope) |

---

## 11. Traceability (optional)

| Requirement | Source              |
|-------------|--------------------|
| FR-001–005  | System behavior     |
| BR-001–003  | Operational logic   |
| NFR-001–003 | Performance needs   |

---