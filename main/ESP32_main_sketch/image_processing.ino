#define MINIMUM_MIN_MAX 32

uint8_t matrix[18][18];

uint8_t border_coord[16 * 16 + 1][2];
uint8_t gradient_modules[16][16];

void clear_matrix_val () {
  for (uint16_t i = 0; i < 18 * 18; i++) {
    matrix[i / 18][i % 18] &= 0b00111111;      // Only last 6 bits encode brightness
  }
}

bool circle_border () {
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
    return 0;
  }
  /*
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
  */
  calculate_gradient_matrix();
  return 1;
}


void calculate_gradient_matrix () {
  for (int8_t y = 0; y < 16; y++) {
    for (int8_t x = 0; x < 16; x++) {
      gradient_modules[x][y] = sqrt(pow(matrix[x + 2][y + 1] - matrix[x][y + 1], 2) + pow(matrix[x + 1][y + 2] - matrix[x + 1][y], 2)) + 0.5;
      //      Serial.println(String(x) + ", " + String(y) + " : " + String(pow(matrix[x + 2][y + 1] - matrix[x][y + 1], 2)) + ", " + String(pow(matrix[x + 1][y + 2] - matrix[x + 1][y], 2)) + "   -->  " + String(gradient_modules[x][y]));
    }
  }
}
