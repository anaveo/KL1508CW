#include "KL1508CW.h"

// ----- Segment lookup tables
byte dig_1_p_vals[2][4] = {{0b00010100, 0b00010100, 0b00010100, 0b00010100}, // 0 (empty)
                          {0b00110011, 0b00010100, 0b00110011, 0b00010100}, // 1
                          };

byte dig_2_vals[10][4] = {{0b11100001, 0b11010010, 0b11100001, 0b11010010}, // 0
                          {0b00100001, 0b01000010, 0b00100001, 0b01000010}, // 1
                          {0b11100001, 0b00010010, 0b10000011, 0b10000011}, // 2
                          {0b01100001, 0b01010010, 0b10000011, 0b10000011}, // 3
                          {0b00100001, 0b11000010, 0b10000011, 0b10000011}, // 4
                          {0b01000001, 0b11010010, 0b10000011, 0b10000011}, // 5
                          {0b11000001, 0b11010010, 0b10000011, 0b10000011}, // 6
                          {0b00100001, 0b01010010, 0b00100001, 0b01010010}, // 7
                          {0b11100001, 0b11010010, 0b10000011, 0b10000011}, // 8
                          {0b01100001, 0b11010010, 0b10000011, 0b10000011}, // 9
                          };

byte dig_3_vals[10][4] = {{0b01110000, 0b00001001, 0b00001010, 0b00001011}, // 0
                          {0b00010000, 0b00001010, 0b00010000, 0b00001010}, // 1
                          {0b10110000, 0b00001001, 0b00001011, 0b00001011}, // 2
                          {0b10110000, 0b00001001, 0b00001010, 0b00001010}, // 3
                          {0b11010000, 0b00001010, 0b11010000, 0b00001010}, // 4
                          {0b11100000, 0b00001001, 0b00001010, 0b00001010}, // 5
                          {0b11100000, 0b00001001, 0b00001010, 0b00001011}, // 6
                          {0b00010000, 0b00001001, 0b00001010, 0b00001010}, // 7
                          {0b11110000, 0b00001001, 0b00001010, 0b00001011}, // 8
                          {0b11110000, 0b00001001, 0b00001010, 0b00001010}, // 9
                          };

KL1508CW::KL1508CW(const uint8_t pins[5]) {
  for (int i = 0; i < 5; i++) {
    _pins[i] = pins[i];
    pinMode(_pins[i], INPUT);  // Start all pins High-Z
  }
}

void KL1508CW::extractDigits(uint8_t number, uint8_t &hundreds, uint8_t &tens, uint8_t &ones) {
  if (number > 199) number = 199;
  hundreds = number / 100;
  tens = (number % 100) / 10;
  ones = number % 10;
}

void KL1508CW::displayNumber(uint8_t number) {
  uint8_t h, t, o;
  extractDigits(number, h, t, o);

  for (int i = 0; i < 4; i++) {
    _segments[0][i] = dig_1_p_vals[h][i];
    _segments[1][i] = dig_2_vals[t][i];
    _segments[2][i] = dig_3_vals[o][i];
  }
}

void KL1508CW::driveSegment(uint8_t segment) {
  const uint8_t low_pin_idx = segment & 0b00000111;
  const uint8_t high_pin_idxs = segment >> 3;

  for (int i = 0; i < 5; ++i) {
    if (i == low_pin_idx) {
      pinMode(_pins[i], OUTPUT);
      digitalWrite(_pins[i], LOW);
    } else if (high_pin_idxs & (1 << i)) {
      pinMode(_pins[i], OUTPUT);
      digitalWrite(_pins[i], HIGH);
    } else {
      pinMode(_pins[i], INPUT);  // High-Z
    }
  }
}

void KL1508CW::tick() {
  static uint8_t digit = 0;

  driveSegment(_segments[digit][(_phase++) % 4]);

  if (_phase >= 4) {
    _phase = 0;
    digit = (digit + 1) % 3;
  }

  delayMicroseconds(500);  // Tune this to reduce flicker
}
