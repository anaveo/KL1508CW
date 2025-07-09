# KL1508CW

**KL1508CW** is an Arduino library for driving the KL1508CW (and similar) 3-digit Charlieplexed LED display.

---

## Wiring

The KL1508CW is charlieplexed, so **only two pins are active at a time** (1 HIGH, 1 LOW, others are High-Z). You must connect 5 digital pins to the display pins in the correct order.

For example:

| Display Pin | ESP32 Pin Default|
|-------------|-------------|
| A           | 18          |
| B           | 19          |
| C           | 21          |
| D           | 22          |
| E           | 23          |

```cpp
const uint8_t displayPins[5] = {18, 19, 21, 22, 23};
KL1508CW display(displayPins);
```

> Make sure to match the physical wiring order to the order used in your code.

---

## Getting Started

### 1. Install the Library

Clone or download this repository and place it inside your Arduino `libraries/` folder:

```
Arduino/
└── libraries/
    └── KL1508CW/
```

Then restart the Arduino IDE.

---

### 2. Basic Example

```cpp
#include <KL1508CW.h>

const uint8_t displayPins[5] = {18, 19, 21, 22, 23};
KL1508CW display(displayPins);

void setup() {
  display.displayNumber(123, true);  // Show number on startup with percent sign
}

void loop() {
  display.tick();  // Continuously refresh Charlieplexed display
}
```

> The `tick()` function must be called as frequently as possible to maintain display persistence.

---

## Example: Number Sweep

```cpp
#include <KL1508CW.h>

const uint8_t displayPins[5] = {18, 19, 21, 22, 23};
KL1508CW display(displayPins);

uint16_t currentValue = 1;
unsigned long lastUpdate = 0;

void setup() {
  display.displayNumber(currentValue, true);
}

void loop() {
  display.tick();  // Refresh Charlieplexing

  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
    currentValue = (currentValue % 199) + 1;
    display.displayNumber(currentValue, true);
  }
}
```

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
