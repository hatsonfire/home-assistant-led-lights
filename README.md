# Home Assistant LED Lights

This is an Arduino project for controlling addressable LED strips (WS2812B) with an ESP32, designed for seamless integration with Home Assistant via MQTT.

It provides a flexible effect system that allows for easy creation of new lighting animations. Currently, it supports a solid color effect and a pulsing effect. The project is structured to control two separate LED strips connected to different data pins.

## Features

* **MQTT Control:** Integrates as an MQTT JSON Light in Home Assistant, allowing control over state (on/off), brightness, color, and effects.
* **Dynamic Effects:** Easily switch between different lighting animations. The initial effects are "Solid" and "Pulsing".
* **Dependency Management:** Uses Git submodules to manage external libraries (`FastLED`, `ArduinoJson`, `PubSubClient`), ensuring a reproducible build environment.

## Physical Design

The physical construction of this project is based on the **"Chromance"** LED sculpture designed by YouTuber and certified punster **Zach Freedman (Voidstar Lab)**. The complex mapping of the 40 LED edges and 25 nodes is implemented in `LedStructure.cpp` to match this specific design.

For instructions on how to build the physical structure, please refer to the official guide:
* **[Chromance Assembly Instructions](https://voidstar.dozuki.com/Guide/Chromance+Assembly+Instructions/6)**

## Getting Started

### Prerequisites

* Arduino IDE or PlatformIO set up for ESP32 development.
* An ESP32 microcontroller.
* An MQTT broker set up and accessible on your network.

### Installation

To ensure all dependencies are downloaded correctly and the project folder is named properly for the Arduino IDE, follow these specific cloning instructions.

1.  **Clone the Repository**

    Open your terminal or Git Bash and run the following command. This will clone the main project, initialize all the required library submodules, and place it in a folder named `LedLights`.

    ```bash
    git clone --recurse-submodules [https://github.com/hatsonfire/home-assistant-led-lights.git](https://github.com/hatsonfire/home-assistant-led-lights.git) LedLights
    ```

    **IMPORTANT:**
    * Using `--recurse-submodules` is essential to download the `FastLED`, `ArduinoJson`, and `PubSubClient` libraries.
    * Specifying `LedLights` as the target directory is required for the Arduino IDE to correctly open and compile the `LedLights.ino` sketch.

2.  **Configure Secrets**

    Before uploading, you need to provide your network and MQTT credentials.
    * In the project folder, copy the example secrets file `ArduinoSecrets.h.example` to a new file named `ArduinoSecrets.h`.
    * Edit `ArduinoSecrets.h` with your WiFi SSID, WiFi password, and MQTT password.

3.  **Configure Settings**

    Open `Settings.h` to configure your specific hardware and MQTT setup:
    * Set the correct number of LEDs for your strips (`NUM_LEDS_1`, `NUM_LEDS_2`).
    * Verify the data pins (`DATA_PIN_1`, `DATA_PIN_2`).
    * Update your `MQTT_SERVER` IP address and other MQTT-related topics if needed.

4.  **Compile and Upload**

    Open the `LedLights.ino` sketch in the Arduino IDE, select your ESP32 board and port, and upload the code.

## License

This project is licensed under the Apache License, Version 2.0.
