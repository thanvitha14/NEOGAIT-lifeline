# NEOGAIT-lifeline
An IoT-based smart cane with fall detection, health monitoring, SOS alerts, and voice guidance in local languages—enhancing safety and accessibility for all.

## Project Overview
This project focuses on regional language voice alerts to improve accessibility and avoid false alarms. It is an IoT-based smart safety system that detects falls using sensors, monitors health, and tracks location.
If a fall is detected, a voice alert confirms the user’s condition, and if there is no response, an emergency message with location is sent automatically.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Technologies Used](#technologies-used)

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

  
