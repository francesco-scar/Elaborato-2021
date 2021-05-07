#define MINIMUM_MIN_MAX 32
#define K 1                                    // Coefficient of gradient in gradient descent step

#define SGN(x) (x < 0 ? -1 : 1)                 // Sign of the number (used in derivatives)

uint8_t matrix[18][18];

uint8_t gradient_modules[16][16];
float progressive_approximations[256*3];

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
      gradient_modules[x][y] = sqrt(pow(matrix[x + 2][y + 1] - matrix[x][y + 1], 2) + pow(matrix[x + 1][y + 2] - matrix[x + 1][y], 2)) + 0.5;
      //      Serial.println(String(x) + ", " + String(y) + " : " + String(pow(matrix[x + 2][y + 1] - matrix[x][y + 1], 2)) + ", " + String(pow(matrix[x + 1][y + 2] - matrix[x + 1][y], 2)) + "   -->  " + String(gradient_modules[x][y]));
    }
  }
}


// This function is the core of this project it finds a circle that minimize the error with the gradient matrix "border"
// The coordinate sistem used in this function is centered in the "top-left" corner of the gradient matrix, traslation is made afterward
void gradient_descent (float x, float y, float r, uint8_t recurse_n) {
  if (recurse_n == 0) {
    return;
  }

  float dx = 0.0, dy = 0.0, dr = 0.0;
  for (uint8_t y_p = 0; y_p < 16; y_p++) {
    for (uint8_t x_p = 0; x_p < 16; x_p++) {
      float x_diff = x_p - x;
      float y_diff = y_p - y;
      float x_diff_2 = pow(x_diff, 2);
      float y_diff_2 = pow(y_diff, 2);
      if ((x_diff_2 + y_diff_2) == 0) {                               // Not sure if this is right (when denominator of derivative is 0 just skip the case, considering 0 the derivative)
        continue;
      }
      dx -= gradient_modules[x_p][y_p] * SGN(sqrt(x_diff_2 + y_diff_2) - r) * x_diff / sqrt(x_diff_2 + y_diff_2);     // It's -= instead of += just because I used x_diff (x_p - x) instead of - x_diff (same in the line below)
      dy -= gradient_modules[x_p][y_p] * SGN(sqrt(x_diff_2 + y_diff_2) - r) * y_diff / sqrt(x_diff_2 + y_diff_2);
      dr -= gradient_modules[x_p][y_p] * SGN(sqrt(x_diff_2 + y_diff_2) - r);
//      Serial.println(String(x_p)+", "+String(y_p)+", "+String(dx));
    }
  }
  progressive_approximations[recurse_n*3] = x + dx * K - 7.5;
  progressive_approximations[recurse_n*3+1] = y + dy * K - 7.5;
  progressive_approximations[recurse_n*3+2] = r + dr * K;
  Serial.println(String(recurse_n)+" - "+String(progressive_approximations[recurse_n*3])+", "+String(progressive_approximations[recurse_n*3+1])+", "+String(progressive_approximations[recurse_n*3+2]));
  gradient_descent (x + dx * K, y + dy * K, r + dr * K, recurse_n - 1);
}
