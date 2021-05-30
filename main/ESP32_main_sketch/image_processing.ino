#define MINIMUM_MIN_MAX 32
#define GRADIENT_THRESHOLD 15
#define K 0.0001                                    // Coefficient of gradient in gradient descent step

#define SGN(x) (x < 0 ? -1 : 1)                 // Sign of the number (used in derivatives)
/*
uint8_t matrix[18][18] =
{ {202, 73, 73, 73, 73, 73, 73, 73, 72, 72, 72, 74, 75, 76, 77, 78, 79, 80},
  {74, 74, 73, 73, 73, 73, 73, 73, 72, 72, 72, 73, 74, 75, 76, 77, 78, 79},
  {74, 74, 74, 73, 73, 73, 73, 73, 73, 72, 72, 72, 73, 74, 75, 76, 76, 77},
  {75, 74, 74, 74, 74, 75, 80, 87, 90, 87, 79, 74, 73, 74, 75, 75, 75, 75},
  {75, 75, 74, 75, 80, 100, 111, 112, 111, 111, 110, 99, 80, 74, 74, 75, 75, 75},
  {76, 76, 75, 83, 110, 113, 112, 111, 111, 111, 110, 111, 108, 84, 75, 74, 75, 75},
  {77, 76, 80, 109, 113, 112, 112, 112, 112, 111, 111, 110, 111, 109, 80, 74, 74, 74},
  {77, 77, 97, 114, 113, 113, 113, 113, 112, 111, 111, 111, 111, 111, 95, 75, 74, 74},
  {77, 79, 111, 113, 114, 113, 113, 113, 113, 112, 111, 111, 110, 111, 107, 76, 74, 73},
  {78, 83, 115, 114, 114, 114, 113, 113, 113, 113, 112, 111, 111, 111, 111, 80, 73, 73},
  {78, 84, 115, 114, 114, 114, 113, 113, 114, 113, 111, 111, 111, 111, 111, 80, 73, 73},
  {79, 83, 115, 114, 114, 114, 114, 114, 113, 113, 112, 111, 111, 111, 109, 77, 73, 72},
  {79, 80, 108, 114, 114, 114, 113, 114, 113, 113, 112, 112, 111, 112, 100, 75, 73, 73},
  {79, 79, 91, 116, 114, 113, 114, 114, 113, 113, 112, 112, 112, 112, 84, 74, 73, 73},
  {79, 79, 80, 102, 113, 114, 114, 114, 114, 113, 113, 112, 113, 93, 76, 74, 73, 73},
  {80, 79, 79, 79, 88, 114, 115, 114, 114, 113, 114, 110, 90, 77, 75, 74, 74, 73},
  {80, 79, 79, 78, 79, 83, 95, 103, 105, 101, 91, 80, 76, 76, 75, 74, 74, 73},
  {80, 79, 79, 78, 78, 77, 78, 78, 78, 78, 77, 76, 76, 75, 75, 75, 74, 74}
};             // A test image with circle center about left-bottom of matrix center
*/
uint8_t matrix[18][18] =
{ {197, 69, 69, 69, 69, 68, 69, 69, 68, 68, 68, 69, 68, 68, 68, 68, 68, 67},
  {69, 69, 69, 69, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {69, 69, 69, 69, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {69, 69, 68, 69, 68, 69, 68, 69, 68, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {69, 69, 68, 68, 68, 68, 68, 68, 69, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {69, 68, 68, 68, 68, 69, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 67},
  {68, 68, 68, 68, 68, 68, 69, 68, 68, 69, 68, 68, 68, 68, 68, 68, 68, 67},
  {68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 68, 68, 68, 68, 68, 67},
  {68, 68, 68, 68, 69, 69, 69, 70, 71, 72, 71, 70, 69, 69, 68, 68, 68, 67},
  {68, 68, 69, 69, 69, 71, 76, 85, 93, 99, 95, 87, 77, 71, 69, 68, 68, 67},
  {68, 69, 69, 69, 72, 87, 108, 118, 121, 125, 124, 120, 116, 92, 73, 69, 68, 67},
  {68, 69, 69, 71, 88, 120, 124, 121, 123, 123, 119, 118, 122, 117, 93, 72, 68, 67},
  {68, 69, 69, 79, 112, 123, 117, 125, 121, 124, 124, 120, 123, 123, 116, 88, 70, 67},
  {68, 69, 71, 98, 121, 121, 125, 120, 120, 123, 119, 119, 122, 118, 118, 110, 74, 68},
  {68, 69, 75, 111, 119, 122, 119, 119, 122, 122, 118, 121, 120, 123, 118, 116, 80, 68},
  {68, 69, 79, 115, 122, 120, 124, 120, 121, 125, 124, 119, 121, 121, 118, 120, 84, 68}
};             // A test image with circle center on the bottom edge (max y coord)

uint8_t gradient_modules[16][16];
float progressive_approximations[GRADIENT_DESCENT_ITERATIONS * 3];

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
  calculate_gradient_matrix();
  return 1;
}


void calculate_gradient_matrix () {
  for (int8_t y = 0; y < 16; y++) {
    for (int8_t x = 0; x < 16; x++) {
      gradient_modules[y][x] = sqrt(pow(matrix[y + 2][x + 1] - matrix[y][x + 1], 2) + pow(matrix[y + 1][x + 2] - matrix[y + 1][x], 2)) + 0.5;
    }
  }
}


void detect_starting_point (float *result, uint8_t threshold) {
  *result = 0.0;
  *(result + 1) = 0.0;
  uint16_t total_coefficients = 0;

  for (uint16_t y = 0; y < 18; y++) {
    for (uint16_t x = 0; x < 18; x++) {
      if (matrix[y][x] >= threshold) {
        result[0] += matrix[y][x] * x;
        result[1] += matrix[y][x] * y;
        total_coefficients += matrix[y][x];
      }
    }
  }
  result[0] /= total_coefficients;
  result[1] /= total_coefficients;

  result[0] -= 1;
  result[1] -= 1;
}

// This function is the core of this project it finds a circle that minimize the error with the gradient matrix "border"
// The coordinate sistem used in this function is centered in the "top-left" corner of the gradient matrix, traslation is made afterward
void gradient_descent (float x, float y, float r, uint16_t iterations) {
  for (uint16_t recurse_n = 0; recurse_n < iterations; recurse_n++) {
    float dx = 0.0, dy = 0.0, dr = 0.0;
    for (uint8_t y_p = 0; y_p < 16; y_p++) {
      for (uint8_t x_p = 0; x_p < 16; x_p++) {
        if (gradient_modules[y_p][x_p] > GRADIENT_THRESHOLD) {                           // Filter noise (real edge gradients are around 50, using torch, so 15 seems ok)
          float x_diff = x_p - x;
          float y_diff = y_p - y;
          float x_diff_2 = pow(x_diff, 2);
          float y_diff_2 = pow(y_diff, 2);
          if ((x_diff_2 + y_diff_2) == 0) {                               // Not sure if this is right (when denominator of derivative is 0 just skip the case, considering 0 the derivative)
            continue;
          }
          dx -= (gradient_modules[y_p][x_p] - GRADIENT_THRESHOLD) * SGN(sqrt(x_diff_2 + y_diff_2) - r) * x_diff / sqrt(x_diff_2 + y_diff_2);   // It's -= instead of += just because I used x_diff (x_p - x) instead of - x_diff (same in the line below)
          dy -= (gradient_modules[y_p][x_p] - GRADIENT_THRESHOLD) * SGN(sqrt(x_diff_2 + y_diff_2) - r) * y_diff / sqrt(x_diff_2 + y_diff_2);
          dr -= (gradient_modules[y_p][x_p] - GRADIENT_THRESHOLD) * SGN(sqrt(x_diff_2 + y_diff_2) - r);
          //      Serial.println(String(x_p)+", "+String(y_p)+", "+String(dx));
        }
      }
      yield();                                                         // Allows to manage wifi related functions and avoid crashes
    }

    x -= dx * K;
    y -= dy * K;
    r -= dr * K;
    progressive_approximations[recurse_n * 3] = x - 7.5;
    progressive_approximations[recurse_n * 3 + 1] = y - 7.5;
    progressive_approximations[recurse_n * 3 + 2] = r;
    //Serial.println(String(recurse_n) + ": " + String(progressive_approximations[recurse_n * 3]) + ", " + String(progressive_approximations[recurse_n * 3 + 1]) + ", " + String(progressive_approximations[recurse_n * 3 + 2]));
  }
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
    if (!stop && over_threshold < 16 * 16 * 3 / 4) {                              // Less then 3/4 of internal pixels should be over or equal to threshold
      return threshold;
    }
  }
  return 0;
}
