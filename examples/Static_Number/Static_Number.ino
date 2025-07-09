#include "KL1508CW.h"

const uint8_t displayPins[5] = {18, 19, 21, 22, 23}; // Change these to match your pins
KL1508CW display(displayPins);

void setup() {
  display.displayNumber(123, true);  // Show initial number with percent
}

void loop() {
  display.tick();              // Keep display refreshed
}
