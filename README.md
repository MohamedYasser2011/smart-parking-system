# 🚗 Smart Parking System


![smart_parking img (2)](https://github.com/user-attachments/assets/db573ff3-d0e8-4833-b583-097c2823ec07)


## 📋 Project Description

This project is an **automatic smart parking system** using **ultrasonic sensors**, a **servo gate**, LEDs, and an **LCD display**. It checks if cars are present in parking slots and at the entrance gate:
- If there are **free slots**, the gate opens automatically.
- If the parking is **full**, the gate stays closed.
- An LCD shows each slot’s status (**Free/Full**) in real-time.
- Green and red LEDs show slot availability for drivers.

---

## ⚙️ Pins Used

| Component | Pins | Purpose |
|-----------|------|---------|
| Gate Ultrasonic Trigger | A2 | Send ultrasonic pulse |
| Gate Ultrasonic Echo | A3 | Receive ultrasonic echo |
| Slot 1 Ultrasonic Trigger | 2 | Send pulse for slot 1 |
| Slot 1 Ultrasonic Echo | 3 | Receive echo for slot 1 |
| Slot 2 Ultrasonic Trigger | 4 | Send pulse for slot 2 |
| Slot 2 Ultrasonic Echo | 5 | Receive echo for slot 2 |
| Slot 3 Ultrasonic Trigger | 6 | Send pulse for slot 3 |
| Slot 3 Ultrasonic Echo | 7 | Receive echo for slot 3 |
| Slot 1 Green LED | 8 | Slot 1 available indicator |
| Slot 2 Green LED | 10 | Slot 2 available indicator |
| Slot 3 Green LED | 12 | Slot 3 available indicator |
| Slot 1 Red LED | A0 | Slot 1 full indicator |
| Slot 2 Red LED | 11 | Slot 2 full indicator |
| Slot 3 Red LED | 13 | Slot 3 full indicator |
| Servo Motor | 9 | Gate control |
| I2C LCD | SDA/SCL | Display slot status |

---

## 🧰 Hardware Required

- **1× Arduino board** (Uno, Mega, etc.)
- **4× Ultrasonic sensors** (1 for gate, 3 for slots)
- **1× Servo motor** (gate barrier)
- **1× I2C LCD (16×2)** module
- **3× Green LEDs**
- **3× Red LEDs**
- **Jumper wires & breadboard**

---

## ✅ Key Features

- Automatic gate control if slots are available.
- Displays slot status on LCD.
- Visual indicators for slot availability using red/green LEDs.
- Saves time and avoids overcrowding in parking areas.

---

**This system is ideal for smart parking lots, malls, or small private garages!**
