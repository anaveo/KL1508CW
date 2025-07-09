#ifndef KL1508CW_H
#define KL1508CW_H

#include <Arduino.h>

class KL1508CW {
public:
  KL1508CW(const uint8_t pins[5]);  // Constructor

  void displayNumber(uint8_t number);         // Set a number to display (1–199)
  void tick();                                // Call frequently in loop() to refresh display

private:
  uint8_t _pins[5];
  uint8_t _segments[3][4];  // Current frame data for each digit
  uint8_t _phase = 0;       // Scan phase (0–3)

  void driveSegment(uint8_t segment);
  void extractDigits(uint8_t number, uint8_t &hundreds, uint8_t &tens, uint8_t &ones);
};

#endif
