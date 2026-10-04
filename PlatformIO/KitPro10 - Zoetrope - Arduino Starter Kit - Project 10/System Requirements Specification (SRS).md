# System Requirements Specification (SRS)
## Zoetrope (Arduino Starter Kit – Project 10)

---

## 1. Introduction
This document specifies the system requirements for the *Zoetrope* system.  
The system demonstrates synchronization between mechanical motion and timed light pulses to create a visual animation effect.  
This specification follows INCOSE guidelines and conforms to IEEE 29148:2018 and ISO/IEC/IEEE 15288.

---

## 2. Purpose
The purpose of the system is to create the illusion of motion using a rotating disk and a stroboscopic light source.  
The system demonstrates timing control, synchronization, and interaction between hardware and human visual perception.

---

## 3. System Overview
The system consists of:
- 1 actuator (DC motor driving a rotating disk)
- 1 light source (LED)
- 1 analog input (potentiometer)
- 1 microcontroller

The motor rotates the disk continuously, while the LED emits periodic light pulses.  
The potentiometer adjusts timing parameters (e.g., blink frequency or motor speed) to achieve synchronization.

---

## 4. System Context
The system operates on an Arduino Uno.

- **User** adjusts a potentiometer  
- **Control system** processes timing and control logic  
- **Actuator subsystem** (motor + driver circuit) generates motion  
- **Lighting subsystem** (LED) produces stroboscopic pulses  
- **Power subsystem** supplies energy to motor and electronics  
- **Physical system** (rotating disk with images) creates the visual effect  

---

## 5. Interface Requirements

| Type      | Pin | Component              | Description                              |
|-----------|-----|------------------------|------------------------------------------|
| Input     | A0  | Potentiometer          | Analog input (0–1023)                    |
| Output    | D9  | Motor Driver (PWM)     | Controls motor speed                     |
| Output    | D3  | LED                    | Generates stroboscopic light pulses      |
| Actuator  | —   | DC Motor               | Rotates the disk                         |
| Power     | —   | External Supply        | Provides motor power                     |
| Protection| —   | Flyback Diode          | Protects motor circuit                   |

---

## 6. Functional Requirements

- **FR-001**: The system shall read analog input from the potentiometer on pin A0.  
- **FR-002**: The system shall control motor speed via PWM on pin D9.  
- **FR-003**: The system shall generate periodic LED pulses on pin D3.  
- **FR-004**: The system shall adjust timing parameters based on potentiometer input.  
- **FR-005**: The system shall operate motor and LED concurrently.  

---

## 7. Behavioral Requirements

- **BR-001**: The motor shall rotate continuously during operation.  
- **BR-002**: The LED shall blink at a defined periodic interval.  
- **BR-003**: The LED pulse timing shall be adjustable via user input.  
- **BR-004**: The system shall maintain consistent synchronization between rotation and light pulses under stable conditions.  

---

## 8. Non-Functional Requirements

- **NFR-001**: The system shall maintain timing accuracy within ±10%.  
- **NFR-002**: The system shall respond to input changes within 100 ms.  
- **NFR-003**: The system shall ensure safe operation of the motor using a driver circuit.  
- **NFR-004**: The system shall include a flyback diode for protection against inductive voltage spikes.  
- **NFR-005**: The system shall operate continuously without failure under normal conditions.  
- **NFR-006**: The system shall produce a visually stable animation under correct tuning conditions.  
- **NFR-007**: The system shall be suitable for educational use and demonstration purposes.  

---

## 9. Assumptions and Constraints

- The system uses fixed pins (A0, D9, D3).  
- The motor requires an external power supply and driver circuit.  
- Synchronization depends on manual tuning via potentiometer.  
- Environmental lighting conditions may affect visibility of the animation.  
- No closed-loop feedback for motor speed is implemented.  

---

## 10. Verification Methods

| Requirement | Method        | Description                              |
|-------------|--------------|------------------------------------------|
| FR-001–004  | Test         | Verify input reading and control signals |
| FR-005      | Observation  | Confirm concurrent motor and LED operation|
| BR-001–003  | Observation  | Observe rotation and LED blinking        |
| BR-004      | Test         | Evaluate synchronization stability       |
| NFR-001     | Measurement  | Timing analysis (e.g. oscilloscope)      |
| NFR-002     | Measurement  | Measure response time                    |
| NFR-003–004 | Inspection   | Verify circuit design and protection     |
| NFR-006     | Observation  | Evaluate visual animation quality        |

---

## 11. Traceability (optional)

| Requirement | Source                          |
|-------------|----------------------------------|
| FR-001–005  | Functional system behavior       |
| BR-001–004  | Dynamic and temporal behavior    |
| NFR-001–007 | Performance and safety needs     |

---