# Smart Object Dispenser using IoT

An IoT-based Smart Object Dispenser developed using the **ESP32 microcontroller**, **Firebase Realtime Database**, and **Wi-Fi communication** for automated product dispensing. The system continuously monitors payment status from Firebase, automatically dispenses the selected product using dedicated servo motors, controls a conveyor mechanism through an L298N motor driver, and updates the dispensing status in real time.

---

# Table of Contents

- Overview
- Project Highlights
- Objectives
- System Architecture
- Hardware Components
- Project Workflow
- Features
- Results
- Project Demonstration
- Technologies Used
- Repository Structure
- Applications
- Future Work
- Author
- Acknowledgements
- License

---

# Overview

The Smart Object Dispenser is an IoT-enabled automated dispensing system designed to simplify product distribution through cloud connectivity and embedded automation.

The system uses an ESP32 microcontroller connected to Firebase Realtime Database over Wi-Fi. When a customer's payment is confirmed, the ESP32 automatically identifies the selected product, activates the corresponding servo motor, operates the conveyor mechanism, and updates the dispensing status back to Firebase.

This project demonstrates the integration of Embedded Systems, IoT, Cloud Computing, and Automation to create a reliable and scalable smart dispensing solution.

---

# Project Highlights

- ESP32-based Smart Object Dispenser
- Firebase Realtime Database Integration
- Wi-Fi Communication
- Automated Product Dispensing
- Three Servo Motor Control
- Conveyor Motor Control using L298N
- Relay-Controlled Power Switching
- Real-time Payment Monitoring
- Automatic Firebase Status Update
- Embedded Systems and IoT Integration

---

# Objectives

- Design an IoT-based automated dispensing system.
- Connect ESP32 with Firebase Realtime Database.
- Monitor payment status in real time.
- Dispense products automatically after payment confirmation.
- Update dispensing status in Firebase.
- Develop a low-cost smart vending solution.

---

# System Architecture

## Input

- User Payment
- Firebase Realtime Database

## Processing Unit

- ESP32 Development Board

## Output

- Servo Motors
- Conveyor Motor
- Relay Module
- Firebase Status Update

The ESP32 continuously checks the payment status stored in Firebase. Once the payment status changes to **Completed**, the corresponding servo motor dispenses the selected product while the conveyor motor assists the dispensing process. Finally, the system updates Firebase with the **Dispensed** status.

---

# Hardware Components

| Component | Purpose |
|-----------|----------|
| ESP32 DevKit | Main Controller |
| Servo Motors (3) | Product Dispensing |
| L298N Motor Driver | Conveyor Motor Control |
| Relay Module | Power Switching |
| DC Motor | Conveyor Mechanism |
| Firebase Realtime Database | Cloud Database |
| Wi-Fi | Wireless Communication |
| 12V Battery / Adapter | Power Supply |
| Buck Converter | 12V to 5V Conversion |

---

# Project Workflow

```text
START
   │
Connect ESP32 to Wi-Fi
   │
Connect to Firebase
   │
Read Payment Status
   │
Payment Completed?
   │
No ────────────────┐
                   │
Yes                │
 │                 │
Read Product Name
 │
Activate Relay
 │
Run Conveyor Motor
 │
Rotate Corresponding Servo
 │
Dispense Product
 │
Update Firebase Status
 │
Repeat Monitoring
```

---

# Features

- Automatic Product Dispensing
- ESP32-based Embedded Control
- Firebase Cloud Integration
- Wi-Fi Communication
- Three Independent Servo Motors
- Conveyor Motor Automation
- Relay-Controlled Operation
- Real-time Payment Verification
- Cloud Status Synchronization
- Low-cost IoT Solution

---

# Results

The developed Smart Object Dispenser successfully demonstrated automated dispensing using cloud connectivity.

The system successfully:

- Connected to Firebase Realtime Database.
- Monitored payment status continuously.
- Retrieved product information from Firebase.
- Dispensed products automatically after payment confirmation.
- Controlled three independent servo motors.
- Operated the conveyor motor using the L298N motor driver.
- Updated dispensing status to **Dispensed** in Firebase.
- Demonstrated reliable communication between ESP32 and the cloud database.

---

# Project Demonstration

## Circuit Diagram

![Circuit Diagram](results/circuit_diagram.png)

---

## Hardware Connections

![Hardware Connections](results/hardware_connection.png)

---

## Firebase Database (Payment Pending)

![Firebase Pending](results/firebase_pending.png)

---

## Firebase Database (Payment Completed)

![Firebase Completed](results/firebase_completed.png)

---

## Serial Monitor Output

![Serial Monitor](results/serial_monitor.png)

---

# Technologies Used

## Programming Language

- Embedded C
- Arduino

## Development Environment

- Arduino IDE

## Hardware Platform

- ESP32 Development Board

## Cloud Platform

- Firebase Realtime Database

## Communication

- Wi-Fi

## Libraries

- WiFi
- HTTPClient
- ArduinoJson
- ESP32Servo

## Hardware Modules

- Servo Motors
- L298N Motor Driver
- Relay Module
- DC Motor
- Buck Converter

---

# Repository Structure

```text
Smart-Object-Dispenser-using-IoT/

│
├── results/
│   ├── circuit_diagram.png
│   ├── hardware_connection.png
│   ├── firebase_pending.png
│   ├── firebase_completed.png
│   └── serial_monitor.png
│
├── src/
│   └── smart_object_dispenser.ino
│
├── .gitignore
├── LICENSE
├── README.md
└── requirements.txt
```

---

# Applications

- Smart Vending Machines
- Retail Automation
- Automated Product Dispensing
- Inventory Management
- Smart Cafeterias
- Educational Institutions
- Industrial Automation
- IoT-Based Smart Systems

---

# Future Work

- QR Code-Based Product Selection
- Mobile Application Integration
- UPI Payment Gateway Integration
- RFID/NFC Authentication
- AI-Based Inventory Prediction
- Cloud Analytics Dashboard
- Multi-Product Inventory Management
- Voice-Controlled Dispensing

---

# Author

**Abhishek Alankara**

B.Tech – Electronics and Communication Engineering

SRM University-AP

**LinkedIn:** https://www.linkedin.com/in/abhishekalankara/

**GitHub:** https://github.com/abhishekalankara

---

# Acknowledgements

I would like to express my sincere gratitude to the faculty members and mentors of the Department of Electronics and Communication Engineering, SRM University-AP, for their continuous guidance and support throughout this project. I also acknowledge the developers of Arduino IDE, ESP32, Firebase Realtime Database, and the open-source community for providing the tools and libraries that contributed to the successful implementation of this project.

---

# License

This project is licensed under the **MIT License**.

---

If you found this project useful, consider giving this repository a **Star**.
