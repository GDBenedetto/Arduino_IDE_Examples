# System Requirements Specification (SRS)
## Motorized Pinwheel (Arduino Starter Kit – Project 09)

---

## 1. Introduction
This document specifies the system requirements for the *Motorized Pinwheel* system.  
The system demonstrates safe control of a DC motor using a microcontroller and a digital input.  
This specification follows INCOSE guidelines and conforms to IEEE 29148:2018 and ISO/IEC/IEEE 15288.

---

## 2. Purpose
The purpose of the system is to control a DC motor using a push-button input.  
The motor drives a pinwheel, which rotates when activated, demonstrating basic actuator control and safe switching of higher currents.

---

## 3. System Overview
The system consists of:
- 1 digital input (push-button)
- 1 actuator (DC motor with driver circuit)
- 1 microcontroller

The push-button controls the activation state of the motor.  
A transistor-based driver circuit is used to safely switch the motor.

---

## 4. System Context
The system operates on an Arduino Uno.

- **User** interacts via a push-button  
- **System** processes digital input  
- **Actuator subsystem** (transistor + motor) converts control signal into motion  
- **Power subsystem** provides sufficient current for motor operation  
- **Protection elements** (flyback diode) ensure safe operation  

---

## 5. Interface Requirements

| Type      | Pin | Component              | Description                              |
|-----------|-----|------------------------|------------------------------------------|
| Input     | D2  | Push-button            | Digital input (HIGH/LOW)                 |
| Output    | D9  | Transistor (Motor Driver) | PWM/digital control signal               |
| Actuator  | —   | DC Motor               | Drives the pinwheel                      |
| Power     | —   | External Supply        | Provides motor voltage (e.g. 9V)         |
| Protection| —   | Flyback Diode          | Protects against voltage spikes          |

---

## 6. Functional Requirements

- **FR-001**: The system shall read the state of the push-button on pin D2.  
- **FR-002**: The system shall activate the motor (via D9) when the button is pressed.  
- **FR-003**: The system shall deactivate the motor when the button is released.  
- **FR-004**: The system shall configure pin D2 as INPUT and pin D9 as OUTPUT during initialization.  
- **FR-005**: The system shall control the motor via a transistor driver circuit.  

---

## 7. Behavioral Requirements

- **BR-001**: The motor shall start rotating immediately after the button is pressed.  
- **BR-002**: The motor shall stop immediately after the button is released.  
- **BR-003**: The system shall continuously monitor the button state.  
- **BR-004**: The system shall maintain stable motor operation without unintended switching.  

---

## 8. Non-Functional Requirements

- **NFR-001**: The system shall prevent overcurrent through the microcontroller pins.  
- **NFR-002**: The system shall include a flyback diode for inductive load protection.  
- **NFR-003**: The system shall operate with an external power supply matching the motor voltage (e.g. 9V).  
- **NFR-004**: The system shall respond to input changes within 50 ms.  
- **NFR-005**: The system shall ensure stable switching behavior without oscillations or noise effects.  
- **NFR-006**: The system shall be simple and suitable for educational purposes.  

---

## 9. Assumptions and Constraints

- The system uses fixed pins (D2, D9).  
- The DC motor requires higher current than the microcontroller can supply directly.  
- A transistor is required as a switching element.  
- The flyback diode must be correctly oriented across the motor.  
- No advanced speed control (PWM modulation) is required in the basic version.  

---

## 10. Verification Methods

| Requirement | Method        | Description                              |
|-------------|--------------|------------------------------------------|
| FR-001–003  | Test         | Verify motor response to button input    |
| FR-004      | Inspection   | Check correct pin configuration          |
| FR-005      | Inspection   | Validate presence of driver circuit      |
| BR-001–004  | Observation  | Observe motor start/stop behavior        |
| NFR-001–003 | Inspection   | Verify safe circuit design               |
| NFR-004–005 | Measurement  | Measure response time and signal stability|

---

## 11. Traceability (optional)

| Requirement | Source                      |
|-------------|-----------------------------|
| FR-001–005  | Functional system behavior   |
| BR-001–004  | Operational dynamics         |
| NFR-001–006 | Safety and performance       |

---