# Smart Light Automation System

An ESP32-based automatic light control system that uses an LDR sensor to detect ambient light and automatically switch a relay-controlled light ON or OFF. It also features a live OLED status dashboard and a keypad-based Manual/Auto mode switch.

## Demo Video

[Watch the demo here](PASTE_YOUR_VIDEO_LINK_HERE)

## Features

- **Automatic light control** — the LDR continuously senses room light and the ESP32 decides whether the light should be ON or OFF.
- **Manual override** — switch to Manual mode anytime using the keypad and directly control the light, ignoring the sensor.
- **Live OLED dashboard** — displays the current mode (Auto/Manual), light status (ON/OFF), and the raw LDR sensor reading in real time.
- **Relay-switched real load** — the relay's COM/NO terminals can drive an actual bulb, not just a simulation LED.

## Components Used

| Component | Role |
|---|---|
| ESP32 | Main controller |
| LDR Sensor Module (digital, 3-pin: VCC, GND, DO) | Light / darkness sensing |
| 1-Channel Relay Module (JQC3F-05VDC-C) | Light switching (active-LOW) |
| 0.96" OLED Display (SSD1306, I2C) | Status dashboard |
| 4x4 Matrix Keypad | Manual / Auto mode switch |
| Bulb / LED | The actual light being controlled |
| Breadboard + Jumper Wires | Wiring |

## Wiring / Pin Connections

| Module | Pin | ESP32 Pin |
|---|---|---|
| LDR | VCC | 3.3V |
| LDR | GND | GND |
| LDR | DO | GPIO25 |
| Relay | VCC | 3.3V |
| Relay | GND | GND |
| Relay | IN | GPIO5 |
| OLED | GND | GND |
| OLED | VDD | 3.3V |
| OLED | SCK | GPIO22 |
| OLED | SDA | GPIO21 |
| Keypad | R1–R4 | GPIO13, GPIO12, GPIO14, GPIO27 |
| Keypad | C1–C4 | GPIO26, GPIO33, GPIO32, GPIO15 |

> **Note:** The relay used in this build is **active-LOW** — a LOW signal turns it ON, HIGH turns it OFF. If you use a different relay module, you may need to flip the logic in the code.

## How It Works

1. The LDR continuously senses the room's light level (digital output: `1` = dark, `0` = bright).
2. In **Auto mode** (default), the ESP32 reads the LDR and automatically turns the relay ON when it's dark, and OFF when it's bright.
3. Pressing **`B`** on the keypad switches to **Manual mode**, where the LDR is ignored.
   - In Manual mode, press **`1`** to turn the light ON, and **`0`** to turn it OFF.
4. Pressing **`A`** switches back to **Auto mode**.
5. The OLED continuously displays the current mode, light status, and live LDR reading.

## Libraries Required

Install these via **Arduino IDE → Sketch → Include Library → Manage Libraries**:

- `Adafruit SSD1306`
- `Adafruit GFX Library` (installed automatically as a dependency)
- `Keypad` by Mark Stanley, Alexander Brevig

## Setup Instructions

1. Wire the components as per the table above.
2. Open `smart_light_automation.ino` in Arduino IDE.
3. Install the required libraries.
4. Select **Board: ESP32 Dev Module** and the correct COM port.
5. Upload the code.
6. Open Serial Monitor at **115200 baud** to see debug logs (optional).

## Project Status

All core phases completed and tested:

- [x] Hardware validation (LDR, Relay)
- [x] Auto logic (LDR → Relay)
- [x] OLED live dashboard
- [x] Manual/Auto mode via keypad
- [x] Debouncing and stability testing
- [x] Real load (LED/bulb) tested via relay's switching terminals

## Future Improvements

- Add a joystick-based settings menu for threshold adjustment via OLED.
- Store last-used mode in EEPROM so it persists across restarts.
- Enclose the circuit in a proper housing for a cleaner final build.

## Author

**Ata Waris**
