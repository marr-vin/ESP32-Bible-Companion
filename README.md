# 📖 ESP32 Bible Companion

## Project Description


https://github.com/user-attachments/assets/5d867d32-f828-4551-9e26-d34ee77ad544



### An Offline Scripture and Inspirational Verse Display System

The **ESP32 Bible Companion** is an embedded electronics project designed to make Bible verses and inspirational quotations accessible without requiring an internet connection.

Built around the ESP32 microcontroller and a 16×2 I2C LCD, the device retrieves and displays scripture from locally stored data. The project combines embedded C++, Python-based data processing, structured scripture storage, and LCD interfacing to create a compact, offline-first Bible companion.

The goal is to make scripture accessible through a simple, dedicated electronic device, even in environments where internet connectivity is unreliable or unavailable.

---

## Project Overview

Unlike applications that depend on internet connectivity or mobile devices, this project is designed to operate independently.

The ESP32 handles the processing and display operations, while locally stored scripture data provides the content used by the device.

A Python-based conversion workflow is also used to process Bible source files into structured data suitable for integration with the embedded system.

### Key Features

- **Offline Operation:** Access locally stored Bible verses without requiring an internet connection.
- **Random Scripture Display:** Retrieve and display Bible verses from the available scripture collection.
- **LCD Interface:** Display scripture using a 16×2 I2C LCD.
- **Structured Scripture Data:** Organize Bible content into a format that can be processed by the ESP32.
- **Python Data Processing:** Convert source Bible files into structured C++ data.
- **Expandable Architecture:** Designed to support the integration of additional books and scripture collections.
- **Compact Embedded Design:** Combines a microcontroller, display, and locally stored content into a dedicated device.

---

## Hardware Components

| Component               | Purpose                                     |
| ----------------------- | ------------------------------------------- |
| ESP32 Development Board | Main microcontroller and processing unit    |
| 16×2 I2C LCD            | Displays Bible verses and quotations        |
| I2C Interface           | Communication between the ESP32 and LCD     |
| Supporting Wiring       | Hardware connections and power distribution |

### LCD Configuration

| LCD Pin | ESP32 Connection                              |
| ------- | --------------------------------------------- |
| SDA     | GPIO 21                                       |
| SCL     | GPIO 22                                       |
| VCC     | Appropriate supply voltage for the LCD module |
| GND     | GND                                           |

**I2C Address:** `0x27`



---

## Software and Technologies

| Technology        | Application                                 |
| ----------------- | ------------------------------------------- |
| C++               | Embedded programming and scripture handling |
| Arduino Framework | ESP32 development                           |
| Python            | Processing and converting Bible source data |
| LittleFS          | Local file storage where applicable         |
| I2C               | Communication with the LCD                  |
| ESP32             | Embedded hardware platform                  |

---

## System Architecture

The project uses a data-processing pipeline to prepare scripture content for the embedded device.

```text
       BIBLE SOURCE FILES
               |
               v
       PYTHON PROCESSING
               |
               v
      STRUCTURED VERSE DATA
               |
               v
       C++ DATA GENERATION
               |
               v
         ESP32 SYSTEM
               |
               v
        LOCAL DATA ACCESS
               |
               v
          16x2 LCD
               |
               v
       SCRIPTURE DISPLAY
```

The Python processing stage transforms source Bible data into a structured representation that can be consumed by the embedded application.

The ESP32 then handles scripture retrieval and display operations.

---

## Development Approach

### 1. Data Processing

Bible source files are processed using Python to extract and organize scripture into structured verse records.

This makes it easier to prepare large collections of scripture for use within an embedded environment.

### 2. Embedded Integration

The processed data is integrated into the ESP32 project using C++ data structures and the appropriate local storage approach.

### 3. Display Implementation

The ESP32 communicates with the 16×2 LCD through the I2C protocol to display the selected scripture.

### 4. Offline Accessibility

The device retrieves scripture from locally available data, eliminating the need for continuous internet connectivity.

---

## Project Objectives

- Build a dedicated offline Bible companion using an ESP32.
- Explore efficient storage and retrieval of structured text on embedded hardware.
- Integrate Python-based data processing with embedded C++ development.
- Implement I2C communication with an LCD.
- Develop an expandable architecture capable of accommodating a larger scripture collection.

---

## Current Development Status

**Status: Active Development**

The core system has been developed around the ESP32, structured scripture data, and LCD display.

Development is focused on expanding the available scripture collection, improving data organization, and refining the overall device experience.

---

## Skills Demonstrated

- Embedded Systems Development
- ESP32 Programming
- C++ Programming
- Python Data Processing
- I2C Communication
- LCD Interfacing
- Local Data Storage
- Hardware Integration
- Problem Solving

---

## Future Improvements

Potential future developments include:

- Expanding scripture coverage to all 66 books of the Bible.
- Improving navigation between books, chapters, and verses.
- Introducing additional display and interaction options.
- Improving scripture selection and retrieval.
- Exploring a more advanced display interface.

---

## Repository Structure

The project may be organized as follows:

```text
ESP32-Bible-Companion/
│
├── firmware/
│   ├── BibleCompanion.ino
│   └── data/
│
├── python/
│   └── bible_converter.py
│
├── generated/
│   └── scripture_data.h
│
├── assets/
│   └── project-images/
│
└── README.md
```



---

## Author

**Marvin Fosu Oppong**

