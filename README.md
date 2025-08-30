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

This project is built using PlatformIO, a professional development ecosystem for embedded development. The recommended editor is Visual Studio Code.

### Prerequisites

* An ESP32 microcontroller.
* An MQTT broker set up and accessible on your network.
* **Visual Studio Code:** Download and install from the [official website](https://code.visualstudio.com/).
* **PlatformIO IDE Extension:**
    1. Open Visual Studio Code.
    2. Go to the Extensions view (click the icon with four squares on the left-hand sidebar).
    3. Search for `PlatformIO IDE` and click **Install**.
    4. Restart VS Code after the installation is complete.

### Installation

To ensure all dependencies are downloaded correctly, follow these specific cloning instructions.

1.  **Clone the Repository**

    Open your terminal or Git Bash and run the following command. This will clone the main project and initialize all the required library submodules.

    ```bash
    git clone --recurse-submodules [https://github.com/hatsonfire/home-assistant-led-lights.git](https://github.com/hatsonfire/home-assistant-led-lights.git)
    ```

    **IMPORTANT:** Using `--recurse-submodules` is essential to download the `FastLED`, `ArduinoJson`, and `PubSubClient` libraries.

2.  **Open in PlatformIO**

    * In Visual Studio Code, go to the PlatformIO Home screen (click the alien head icon on the left sidebar).
    * Click on "Open Project".
    * Navigate to and select the `home-assistant-led-lights` folder you just cloned.

3.  **Configure Secrets**

    Before uploading, you need to provide your network and MQTT credentials.
    * In the VS Code explorer, navigate to the `src/` folder.
    * Copy the example secrets file `ArduinoSecrets.h.example` to a new file named `ArduinoSecrets.h` within the same `src/` folder.
    * Edit `ArduinoSecrets.h` with your WiFi SSID, WiFi password, and MQTT password.

4.  **Configure Settings**

    Open `src/Settings.h` to configure your specific hardware and MQTT setup:
    * Set the correct number of LEDs for your strips (`NUM_LEDS_1`, `NUM_LEDS_2`).
    * Verify the data pins (`DATA_PIN_1`, `DATA_PIN_2`).
    * Update your `MQTT_SERVER` IP address and other MQTT-related topics if needed.

## License

This project is licensed under the Apache License, Version 2.0.