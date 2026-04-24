# Robotic Hand (ESP32 + MQTT)

## Overview
This project implements a 4-servo robotic hand controlled wirelessly using MQTT protocol. Two ESP32 boards are used:
- Publisher: Sends servo angle commands
- Subscriber: Receives commands and actuates servos

## Features
- Real-time wireless control over WiFi
- MQTT-based publisher–subscriber architecture
- Smooth servo motion (0°–180° sweep)
- Scalable to multiple actuators

## Hardware
- ESP32 (2 units)
- 4x Servo Motors
- Power supply
- Connecting wires

## Software
- Arduino IDE
- Libraries:
  - WiFi.h
  - PubSubClient.h
  - ESP32Servo.h

## MQTT Topics
- robotic/servo1
- robotic/servo2
- robotic/servo3
- robotic/servo4

## Working
1. Publisher ESP32 sends angle values (0–180) over MQTT topics
2. Subscriber ESP32 receives data
3. Corresponding servo moves to specified angle

## Setup
1. Update WiFi credentials
2. Upload publisher code to one ESP32
3. Upload subscriber code to another ESP32
4. Power both devices
5. Observe synchronized servo movement

## Future Improvements
- Add gesture control (glove/IMU)
- Add feedback sensors
- Mobile app interface