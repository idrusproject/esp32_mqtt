# ESP32 MQTT Client

## Overview

Welcome to the ESP32 MQTT Client project! This project demonstrates how to connect an ESP32 microcontroller to an MQTT broker using WiFi. The ESP32 will publish an introductory message upon successful connection and subscribe to a topic to listen for incoming messages. This setup allows for seamless two-way communication between the ESP32 and other devices or systems connected to the MQTT broker.

## Features

- **WiFi Connectivity**: Connects to a WiFi network using SSID and Password.
- **MQTT Communication**: Establishes a connection to an MQTT broker and manages subscriptions and publications.
- **Message Handling**: Publishes an introductory message and displays received messages via the Serial Monitor.
- **JSON Parsing**: Parses incoming JSON payloads to extract and handle data.

## Board and Library Versions

- **ESP32 by Espressif Systems**: 3.0.3
- **ArduinoJson by Benoit Blanchon**: 7.1.0

## Getting Started

### Prerequisites

- **Hardware**: ESP32 Development Board
- **Software**: Arduino IDE with the following libraries installed:
  - `WiFi` (usually included with the ESP32 board package)
  - `PubSubClient` for MQTT communication
  - `ArduinoJson` for JSON handling

### Installation

1. **Install Arduino IDE**: Download and install the Arduino IDE from the [Arduino website](https://www.arduino.cc/en/software).

2. **Install ESP32 Board Support**:
   - Open Arduino IDE.
   - Go to `File` -> `Preferences`.
   - In the "Additional Board Manager URLs" field, add: `https://dl.espressif.com/dl/package_esp32_index.json`
   - Go to `Tools` -> `Board` -> `Boards Manager`.
   - Search for `esp32` and install the package.

3. **Install Required Libraries**:
   - Go to `Sketch` -> `Include Library` -> `Manage Libraries`.
   - Search for and install `PubSubClient` and `ArduinoJson`.

4. **Upload the Code**:
   - Open the provided `.ino` file in Arduino IDE.
   - Replace the placeholders in the code with your WiFi and MQTT broker details.
   - Connect your ESP32 to your computer.
   - Select the appropriate board and port from `Tools` -> `Board` and `Tools` -> `Port`.
   - Click `Upload` to compile and upload the code to the ESP32.
