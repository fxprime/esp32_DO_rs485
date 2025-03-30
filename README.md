# ESP32 DO RS485 Communication

This project demonstrates how to use an ESP32 microcontroller to communicate with a dissolved oxygen transmitter over RS485 using a MAX485 module. The transmitter, based on the RS-LDO-N01-1 model, utilizes fluorescence technology to measure dissolved oxygen without consuming oxygen or requiring an electrolyte. It also features a built-in temperature sensor for automatic temperature compensation.

## Overview

### Device Description

The RS-LDO-N01-1 is a fluorescence dissolved oxygen transmitter designed for applications in water treatment, aquaculture, environmental monitoring, and other industries. It measures dissolved oxygen using the fluorescence method, ensuring high accuracy and minimal interference with the measured sample.

### Key Features

- **Measurement Range:** 0~20 mg/L (0~200% saturation)
- **Measurement Resolution:** 0.01 mg/L and 0.1% saturation; temperature resolution of 0.1℃
- **Measurement Principle:** Fluorescence (non-consumptive, no electrolyte required)
- **Power Supply:** DC 10~30V; Power consumption: 0.2W
- **Communication Interface:** RS485 using Modbus RTU protocol
  - **Default Baud Rate:** 4800 bps (configurable up to 115200 bps)
  - **Default Modbus Address:** 0x01
- **Additional Parameters:** Configurable registers for calibration, salinity, and atmospheric pressure

### Technical Specifications

- **Modbus Data Frame Format:**
  - **Address Code:** 1 byte
  - **Function Code:** 1 byte (read: 0x03/0x04; write: 0x06)
  - **Data Area:** N bytes (register address and content)
  - **Error Check:** 16-bit CRC
- **Calibration:** Supports both zero oxygen and full-scale (100% oxygen) calibration via Modbus commands

## Wiring

Connect the components as shown in the table below:

| ESP32 | 12V Adapter | MAX485 | DO RS485 Transmitter |
|-------|-------------|--------|----------------------|
| GND   | GND         | GND    | Black                |
| 3.3V  |             | VCC    |                      |
|       | 12V         |        | Brown                |
| 4     |             | RE & DE|                      |
| 18    |             | RO     |                      |
| 19    |             | DI     |                      |
|       |             | A      | Yellow               |
|       |             | B      | Blue                 |

## Setup and Usage

1. **Hardware Connections:**
   - Wire the ESP32, MAX485 module, and DO RS485 transmitter as per the table above.
   - Ensure the device receives a proper power supply (DC 10~30V).

2. **Software Configuration:**
   - Place the transmitter's datasheet in the `datasheet/` folder for reference.
   - Use the provided `main.cpp` file to compile and upload the firmware to the ESP32 using your preferred IDE (e.g., Arduino IDE or PlatformIO).
   - Configure Modbus settings (baud rate and device address) if required by using the provided 485 parameter configuration software.

3. **Monitoring Communication:**
   - Open the serial monitor to verify that the ESP32 successfully communicates with the transmitter.
   - Use Modbus RTU commands to read measurements like dissolved oxygen saturation, oxygen concentration, and temperature.

## Modbus Communication Details

- **Data Frame Structure:**
  - **Address Code:** 1 byte (default 0x01)
  - **Function Code:** 1 byte (read registers with 0x03/0x04; write registers with 0x06)
  - **Data Area:** Contains the register address and corresponding data
  - **CRC Code:** 2 bytes for error checking
- **Example Read Command:**
  - **Send Frame:** `0x01 0x03 0x00 0x00 0x00 0x06 [CRC]`
  - **Response:** Includes dissolved oxygen saturation, oxygen concentration, and temperature (data transmitted in big-endian format)
- **Calibration Commands:**
  - To perform zero oxygen calibration, write `0x0001` to register `0x1010`.
  - For full-scale (100% oxygen) calibration, use the corresponding command as described in the datasheet.

## Calibration Instructions

### Calibration Preparation

- **Zero Oxygen Calibration:**
  - Prepare a zero oxygen standard solution by dissolving 5g of anhydrous sodium sulfite in 95g of water.
  - Allow the solution to stand for 1 hour to deplete oxygen.
- **Full-Scale Calibration:**
  - Create a 100% oxygen environment by aerating water with an air pump for 1 hour or by vigorously shaking water in a closed container.

### Calibration Process

1. Place the sensor in the 100% oxygen environment until the reading stabilizes.
2. Execute the full-scale calibration command via the Modbus interface.
3. Next, immerse the sensor in the zero oxygen solution and wait for stabilization.
4. Execute the zero oxygen calibration command.
5. Ensure the sensor's fluorescent film is kept approximately 1cm above the water surface to prevent water bead formation.

## Precautions and Maintenance

- **Handling:**
  - Avoid collisions and scratches on the sensor head to maintain measurement accuracy.
- **Cleaning:**
  - Clean the exterior with tap water and a soft cloth.
  - For stubborn dirt, use a diluted household detergent solution; avoid harsh chemicals on the optical window.
- **Storage:**
  - For long-term storage, keep the fluorescent film moist by wetting the protective cover.
  - Allow the device to equilibrate to ambient conditions for at least 48 hours before use.
- **Maintenance:**
  - Calibrate the device before each measurement or at least every 3 months for long-term use.
  - Replace the fluorescent film annually under normal usage conditions.

## Additional Information

For detailed instructions and specifications, refer to the transmitter's datasheet available in the `datasheet/` folder:

- [Datasheet](datasheet/18-RS-LDO-N01-1-Dissolved-Oxygen-Transmitter-Instruction-Manual-1.pdf) :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
 