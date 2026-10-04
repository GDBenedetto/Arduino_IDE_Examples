# System Requirements Specification (SRS)
## Mood Cue (Arduino Starter Kit – Project 05)

---

## 1. Introduction
This document specifies the system requirements for the *Mood Cue* system.  
The system demonstrates the interaction between an analog input device and a mechanical actuator.  
This specification follows INCOSE guidelines and conforms to IEEE 29148:2018 and ISO/IEC/IEEE 15288.

---

## 2. Purpose
The purpose of the system is to provide a mechanical indicator for mood representation.  
A potentiometer allows the user to adjust a servo-driven pointer, mapping human input to a physical output.

---

## 3. System Overview
The system consists of:
- 1 analog input (potentiometer)
- 1 actuator (servo motor)
- 1 microcontroller

The potentiometer value (0–1023) is mapped to a servo angle (0–179°), representing a continuous mood scale.

---

## 4. System Context
The system operates on an Arduino Uno.  

- **User** interacts via a potentiometer  
- **System** processes analog input  
- **Actuator** (servo) provides physical feedback  
- Optional: Serial interface for diagnostics  

---

## 5. Interface Requirements

| Type     | Pin | Component        | Description                          |
|----------|-----|------------------|--------------------------------------|
| Input    | A0  | Potentiometer    | Analog input (0–1023)                |
| Output   | D9  | Servo Motor      | PWM signal for angle control         |
| Interface| USB | Serial Monitor   | Debugging and diagnostics            |

---

## 6. Functional Requirements

- **FR-001**: The system shall read analog values from the potentiometer on pin A0.  
- **FR-002**: The system shall map input values (0–1023) to servo angles (0–179°).  
- **FR-003**: The system shall set the servo position according to the mapped angle.  
- **FR-004**: The system shall generate a PWM signal on pin D9 to control the servo.  
- **FR-005**: The system shall transmit diagnostic data via serial communication at 9600 baud.  

---

## 7. Behavioral Requirements

- **BR-001**: The servo shall update its position continuously based on input changes.  
- **BR-002**: The system shall update the servo position at least every 50 ms.  
- **BR-003**: The servo shall cover the full motion range corresponding to the input scale.  
- **BR-004**: The system shall operate without abrupt or unstable movements under normal conditions.  

---

## 8. Non-Functional Requirements

- **NFR-001**: The system shall respond to input changes within 100 ms.  
- **NFR-002**: The servo control signal shall maintain stable timing (PWM consistency).  
- **NFR-003**: The system shall operate continuously without failure under normal conditions.  
- **NFR-004**: The system shall be implementable on standard Arduino hardware without additional libraries beyond Servo.h.  
- **NFR-005**: The system shall maintain readability and simplicity suitable for educational purposes.  

---

## 9. Assumptions and Constraints

- The system uses fixed pins (A0, D9).  
- The servo operates within a range of 0–179°.  
- Power is supplied via USB or equivalent stable source.  
- No advanced filtering or smoothing is required (basic implementation).  

---

## 10. Verification Methods

| Requirement | Method        | Description                          |
|-------------|--------------|--------------------------------------|
| FR-001–003  | Test         | Verify mapping and servo response    |
| FR-004      | Measurement  | Check PWM signal on pin D9           |
| FR-005      | Inspection   | Validate serial output               |
| BR-001–004  | Observation  | Visual verification of motion        |
| NFR-001–002 | Measurement  | Timing analysis (e.g. oscilloscope)  |

---

## 11. Traceability (optional)

| Requirement | Source                  |
|-------------|-------------------------|
| FR-001–005  | System functionality     |
| BR-001–004  | Dynamic system behavior  |
| NFR-001–005 | Performance & constraints|

---



## 📄 Documentation

- [AI SRS Guide](/small_SE_projects/docs/AI_SRS_GUIDE.md)