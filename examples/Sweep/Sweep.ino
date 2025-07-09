#include <KL1508CW.h>

const uint8_t displayPins[5] = {18, 19, 21, 22, 23}; // Change these to match your pins
KL1508CW display(displayPins);

uint16_t currentValue = 1;
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 250; // Change number every 100ms

void setup() {
  display.displayNumber(currentValue);
}

void loop() {
  // Continuously refresh display
  display.tick();

  // Change number based on time
  unsigned long now = millis();
  if (now - lastUpdate >= updateInterval) {
    lastUpdate = now;

    currentValue++;
    if (currentValue > 199) currentValue = 1;

    display.displayNumber(currentValue);
  }
}
