# ESP32 DO RS485 Communication

This project demonstrates how to use an ESP32 microcontroller to communicate with a device over RS485 using the MAX485 module.


## Datasheet
[Datasheet](datasheet/18-RS-LDO-N01-1-Dissolved-Oxygen-Transmitter-Instruction-Manual-1.pdf)


## Wiring

| ESP32 | 12V Adapter | MAX485 | DO RS485 |
|-------|-------------|--------|----------|
| GND   | GND         | GND    | Black    |
| 3.3V  |             | VCC    |          |
|       | 12V         |        | Brown    |
| 4     |             | RE & DE|          |
| 18    |             | RO     |          |
| 19    |             | DI     |          |
|       |             | A      | Yellow   |
|       |             | B      | Blue     |
 

## Usage

1. Connect the ESP32, MAX485 module, and DO RS485 device as per the wiring table above.
2. Place the required datasheets in the `datasheet/` folder for reference.
3. Compile and upload the `main.cpp` file to the ESP32 using your preferred IDE (e.g., Arduino IDE or PlatformIO).
4. Monitor the serial output to verify communication.
