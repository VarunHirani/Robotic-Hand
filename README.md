# 🤖 Robotic Hand — ESP32 + MQTT

A wirelessly controlled 4-servo robotic hand built using two ESP32 boards communicating over the MQTT protocol. One ESP32 publishes servo angle commands, and a second ESP32 subscribes to those commands and actuates the servos in real time.

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue)](https://www.espressif.com/en/products/socs/esp32)
[![Protocol](https://img.shields.io/badge/Protocol-MQTT-orange)](https://mqtt.org/)
[![IDE](https://img.shields.io/badge/IDE-Arduino-teal)](https://www.arduino.cc/)

---

## 📋 Table of Contents
- [Overview](#-overview)
- [Features](#-features)
- [System Architecture](#-system-architecture)
- [Hardware Requirements](#-hardware-requirements)
- [Software & Libraries](#-software--libraries)
- [MQTT Topics](#-mqtt-topics)
- [How It Works](#-how-it-works)
- [Getting Started](#-getting-started)
- [Demo & Resources](#-demo--resources)
- [Future Improvements](#-future-improvements)
- [Authors](#-authors)
- [License](#-license)

---

## 🔍 Overview

This project demonstrates a publisher–subscriber architecture for controlling a robotic hand wirelessly. Instead of wiring a controller directly to the servos, one ESP32 acts as a **publisher** — sending servo angle commands over WiFi using MQTT — while a second ESP32 acts as a **subscriber**, receiving those commands and driving four servo motors that form the hand's fingers/joints.

This decoupled design is a foundational step toward more advanced control schemes, such as glove- or IMU-based gesture control and mobile app integration (see [Future Improvements](#-future-improvements)).

## ✨ Features

- **Real-time wireless control** over WiFi — no physical link between controller and hand
- **MQTT publisher–subscriber architecture** for reliable, low-latency messaging
- **Smooth servo motion** across the full 0°–180° range
- **Scalable design** — additional topics/servos can be added with minimal changes
- **Decoupled hardware** — publisher and subscriber can be developed/tested independently

## 🏗 System Architecture

```
┌─────────────────┐         WiFi / MQTT          ┌──────────────────┐
│  Publisher ESP32 │ ───────────────────────────▶ │ Subscriber ESP32 │
│  (sends angles)   │   robotic/servo1..4          │ (drives servos)  │
└─────────────────┘                               └──────────────────┘
                                                          │
                                                          ▼
                                                 ┌─────────────────┐
                                                 │  4x Servo Motors │
                                                 │  (Robotic Hand)   │
                                                 └─────────────────┘
```

Both boards connect to the same MQTT broker over WiFi. The publisher sends angle values (0–180) on four dedicated topics; the subscriber listens on those topics and moves the corresponding servo.

## 🔧 Hardware Requirements

| Component | Quantity |
|---|---|
| ESP32 Development Board | 2 |
| Servo Motors (SG90 or similar) | 4 |
| External Power Supply (for servos) | 1 |
| Jumper Wires | As needed |

## 💻 Software & Libraries

- **IDE:** [Arduino IDE](https://www.arduino.cc/en/software)
- **Libraries:**
  - [`WiFi.h`](https://www.arduino.cc/en/Reference/WiFi) — WiFi connectivity for ESP32
  - [`PubSubClient.h`](https://github.com/knolleary/pubsubclient) — MQTT client
  - [`ESP32Servo.h`](https://github.com/madhephaestus/ESP32Servo) — Servo control on ESP32

## 📡 MQTT Topics

| Topic | Description |
|---|---|
| `robotic/servo1` | Angle command for Servo 1 (0–180°) |
| `robotic/servo2` | Angle command for Servo 2 (0–180°) |
| `robotic/servo3` | Angle command for Servo 3 (0–180°) |
| `robotic/servo4` | Angle command for Servo 4 (0–180°) |

## ⚙️ How It Works

1. The **publisher ESP32** sends servo angle values (0–180°) over the four MQTT topics.
2. The **subscriber ESP32** subscribes to these topics and listens for incoming messages.
3. On receiving a message, the subscriber moves the corresponding servo to the specified angle, actuating the robotic hand.

## 🚀 Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/VarunHirani/Robotic-Hand.git
   ```
2. **Install the required libraries** in the Arduino IDE (`WiFi.h`, `PubSubClient.h`, `ESP32Servo.h`).
3. **Update WiFi and MQTT broker credentials** in both sketches (SSID, password, broker address).
4. **Upload the publisher sketch** to the first ESP32.
5. **Upload the subscriber sketch** to the second ESP32.
6. **Power both boards** and connect the servos to the subscriber ESP32.
7. **Observe synchronized servo movement** as the publisher sends commands.

## 🎥 Demo & Resources

- 🎥 [Demonstration Video](https://drive.google.com/drive/folders/1whoozLBYLV4UELsts1uAZSLfFE4VfzJN)
- 📊 [Presentation Slides](https://drive.google.com/drive/folders/1whoozLBYLV4UELsts1uAZSLfFE4VfzJN)
- 📄 [Project Proposal, Flowchart & Bill of Materials](https://drive.google.com/drive/folders/1whoozLBYLV4UELsts1uAZSLfFE4VfzJN)

> All demo and documentation files are available in this shared [Google Drive folder](https://drive.google.com/drive/folders/1whoozLBYLV4UELsts1uAZSLfFE4VfzJN).

## 🔮 Future Improvements

- 🖐 **Gesture control** using a glove or IMU sensor for intuitive hand mimicry
- 📈 **Feedback sensors** (e.g., flex or force sensors) for closed-loop control
- 📱 **Mobile app interface** for direct control over MQTT

## 👤 Authors

**Varun Hirani**
Electrical Engineering, IIT Goa
📧 [hirani.varun@gmail.com](mailto:hirani.varun@gmail.com)

**Kamal Assudani**
Electrical Engineering, IIT Goa
📧 [kamal.assudani.23063@iitgoa.ac.in](mailto:kamal.assudani.23063@iitgoa.ac.in)

---

⭐ If you found this project useful or interesting, consider giving it a star on GitHub!
