# Arduino Register-Level DHT11 and I2C LCD Project
## Project Purpose
The purpose of this project is not only to read temperature data from the DHT11 sensor and display it on an LCD screen, but also to program the Arduino at the register level to improve my low-level programming skills and gain a deeper understanding of how protocols like I2C work at their core.
## Project Overview
Through this project, I experienced:
- Direct register manipulation on AVR microcontrollers  
- Implementing low-level protocols 
- Hardware interaction and timing-critical programming  
## Hardware Components Used
- Arduino Uno  
- DHT11 Temperature/Humidity Sensor  
- 16x2 I2C LCD Display  
- 5kΩ resistor for DHT11  
- 2x 4.8kΩ pull-up resistors for I2C  
- Breadboard and jumper wires  
## Technical Implementation
### Register-Level Programming
```cpp
// Direct port manipulation examples
#define DTHPORT PORTD
#define DTHDDR DDRD
#define DTHPINREG PIND
// Function that initiates I2C communication
void i2c_start() {
    I2CDDR |= (1 << SDA_PIN | 1 << SCL_PIN);

    I2CPORT |= (1 << SCL_PIN | 1 << SDA_PIN);
    i2c_dly();

    I2CPORT &= ~(1 << SDA_PIN);
    i2c_dly();

    I2CPORT &= ~(1 << SCL_PIN);
    i2c_dly();
}
```
## I2C Protocol Implementation
-  I implemented the I2C protocol
-  Generating start/stop conditions
-  Data transmission and reception
-  Handling ACK/NACK signals
-  Clock stretching support

## DHT Communication Protocol
-  To read temperature and humidity data from the DHT11, I implemented the protocol defined in its datasheet:
-  MCU pulls DATA pin LOW for 18ms to send start signal
-  MCU releases pin HIGH and waits for response
-  DHT11 responds with a signal (LOW 80μs + HIGH 80μs)
-  40-bit data transmission begins (LOW 50μs + HIGH 26–70μs)
-  Each bit: LOW 50μs + HIGH duration (26μs = 0, 70μs = 1)

Note: For more details, please refer to the DHT11 datasheet.

## Key Skills Gained
-  Through this project, I improved my:
-  AVR architecture and register manipulation
-  Precise timing skills for sensor communication
-  Knowledge of how protocols work at a fundamental level
-  Debugging skills using both code analysis and hardware tools
-  Hardware integration skills for multiple components

## Project Structure
```
├── include/
│   ├── dth11.h     # DHT11 register definitions
│   ├── i2c.h       # I2C protocol functions
│   └── i2c_lcd.h   # LCD control functions
├── src/
│   ├── main.cpp    # Main application
│   ├── dth11.cpp   # DHT11 implementation
│   ├── i2c.cpp     # I2C communication
│   └── i2c_lcd.cpp # LCD control implementation
└── platformio.ini  # Build configuration
```
## Circuit Diagram
<img width="1454" height="1007" alt="Screenshot 2025-08-23 133358" src="https://github.com/user-attachments/assets/8dfcf1d3-5013-457e-a3a5-8aae356b7644" /> 
## Note
-  This schematic was designed using EasyEDA
-  For educational/personal use only
-  [EasyEDA](https://easyeda.com/)
-  Free electronic design tool
---
⭐ If you find this project useful or interesting, don’t forget to give it a star!
