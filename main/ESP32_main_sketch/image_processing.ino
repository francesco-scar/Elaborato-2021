#define MINIMUM_MIN_MAX 32

uint8_t border_coord[16 * 16 + 1][2];

void clear_matrix_val () {
  for (uint16_t i = 0; i < 18 * 18; i++) {
    matrix[i / 18][i % 18] &= 0b00111111;      // Only last 6 bits encode brightness
  }
}

uint8_t circle_border () {
  uint8_t max_val = 0;
  uint8_t min_val = 63;     //
  for (uint16_t i = 0; i < 18 * 18; i++) {
    if (matrix[i / 18][i % 18] > max_val) {
      max_val = matrix[i / 18][i % 18];
    }
    if (matrix[i / 18][i % 18] < min_val) {
      min_val = matrix[i / 18][i % 18];
    }
  }
  if ((max_val - min_val) < MINIMUM_MIN_MAX) {
    return 255;
  }

  uint8_t threshold = get_threshold();
  uint8_t i = 0;
  for (uint8_t x = 1; x < 17; x++) {
    for (uint8_t y = 1; y < 17; y++) {
      if (matrix[x][y] >= threshold && ((matrix[x + 1][y] < threshold) || (matrix[x - 1][y] < threshold) || (matrix[x][y + 1] < threshold) || (matrix[x][y - 1] < threshold))) {
        border_coord[i][0] = x;
        border_coord[i][1] = y;
        i++;
      }
    }
  }
  border_coord[i][0] = 255;                   // To detect end of valid coords (maximum valid value is 16)
  return threshold;
}


uint8_t get_threshold () {
  for (uint8_t threshold = 1; threshold < 64; threshold++) {                      // The threshold is the minimum value that is in the circle(included)
    bool stop = false;
    uint16_t over_threshold = 0;
    for (uint8_t x = 1; x < 17 && !stop; x++) {
      for (uint8_t y = 1; y < 17 && !stop; y++) {
        if (matrix[x][y] >= threshold) {
          over_threshold++;
          if (((matrix[x + 1][y] >= threshold) + (matrix[x - 1][y] >= threshold) + (matrix[x][y + 1] >= threshold) + (matrix[x][y - 1] >= threshold)) < 2) {
            stop = true;
          }
        }
      }
    }
    if (!stop && over_threshold < 16*16*3/4) {                                    // Less then 3/4 of internal pixels should be over or equal to threshold
      return threshold;
    }
  }
  return 255;
}
