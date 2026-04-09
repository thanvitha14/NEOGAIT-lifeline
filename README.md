# NEOGAIT-lifeline
An IoT-based smart cane with fall detection, health monitoring, SOS alerts, and voice guidance in local languages—enhancing safety and accessibility for all.

## Project Overview
This project focuses on regional language voice alerts to improve accessibility and avoid false alarms. It is an IoT-based smart safety system that detects falls using sensors, monitors health, and tracks location.
If a fall is detected, a voice alert confirms the user’s condition, and if there is no response, an emergency message with location is sent automatically.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Required Libraries](#required-libraries)
- [ESP32 Board Setup](#esp32-board-setup)
- [Account Requirements](#account-requirements)
- [WiFi Setup](#wifi-setup)
- [Pin Connection](#pin-connection)

## Features
- Fall Detection using MPU6050 accelerometer
- Heart Rate Monitoring using MAX30105 sensor
- GPS Location Tracking using Neo-6M module
- WiFi Connectivity for sending alerts
- Buzzer Alert System for immediate warning
- Voice Alert Trigger using ISD1820 module
- Emergency Notification via Pushbullet API
- User Safety Button to cancel false alarms

## Technologies-used
- Arduino (ESP32) – Microcontroller platform
- C/C++ (Arduino IDE) – Programming language
- MPU6050 – Accelerometer for fall detection
- MAX30105 – Heart rate sensor
- TinyGPS++ – GPS data processing
- WiFi & HTTPClient – Communication protocols
- Pushbullet API – Sending emergency alerts

## Hardware requirements
- ESP32 Development Board (any variant)
- MPU6050 Accelerometer (Fall Detection)
- MAX30105 Heart Rate Sensor
- NEO-6M GPS Module
- ISD1820 Voice Recording Module
- 5V Buzzer
- Push Button (Normally Open)
- 9V Battery / Power Bank
- Jumper Wires (Male to Female)
- Walking Stick / PVC Pipe

## Software Requirements
- Arduino IDE Version: 1.8.19 or newer

## Board Package
- ESP32 by Espressif Systems (version 2.0.14 or newer)

## Required Libraries
- Wire (built-in)
- WiFi (built-in)
- HTTPClient (built-in)
- WiFiClientSecure (built-in)
- MAX30105 by SparkFun (version 1.1.3)
- heartRate by SparkFun (version 1.0.1)
- TinyGPS++ by Mikal Hart (version 1.0.3)

## ESP32 board setup
- File → Preferences → Additional Boards Manager URLs
- Add: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
- Tools → Board → Boards Manager → Search "ESP32" → Install
- Select Board: ESP32 Dev Module
- Select Port: (COM3 or /dev/ttyUSB0)

## Account Requirements
 PushBullet Account (Free):
- Sign up at https://www.pushbullet.com
- Generate API Access Token
- Install PushBullet app on phone

## wifi-setup
- Mobile hotspot or WiFi network
- SSID and password required

## Pin connection
- MPU6050     → SDA=21, SCL=22,Vin-3.3V, GND = GND
- MAX30105    → SDA=21, SCL=22,Vin-3.3V, GND = GND
- GPS NEO-6M  → TX=16, RX=17,Vin-5V, GND = GND
- ISD1820     → PLAY-E=19,Vin-3.3V, GND = GND
- Buzzer      → GPIO 18, GND = GND
- Button      → GPIO 5 (INPUT_PULLUP), GND = GND


  
