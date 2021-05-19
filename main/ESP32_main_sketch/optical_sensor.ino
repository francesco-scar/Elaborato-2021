// High level functions
void getImageMatrix() {
  write(0x00, 0b00000001);
  delay(1);
  write(0x08, 0xff);
  delay(1);
  int i = 0;
  while (i < 18 * 18) {
    delayMicroseconds(1);
    yield();
    uint8_t data = read(0x08);
//    println_full_bin(data);
    if (data & 0b01000000) {
      matrix[i/18][i%18] = data;
      i++;
    } else {
      Serial.print('-');
    }
  }
}


void print_full_bin(uint8_t bin) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((bool) (bin & (1 << i)));
  }
}

void println_full_bin(uint8_t bin) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((bool) (bin & (1 << i)));
  }
  Serial.println();
}


// Middle level functions
void write(uint8_t register_addr, uint8_t data) {
  register_addr |= 0b10000000;                  // Set MSB to 1

  write_byte(register_addr);

  delayMicroseconds(200);

  write_byte(data);

  delayMicroseconds(200);
}

uint8_t read(uint8_t register_addr) {
  register_addr &= 0b01111111;                  // Set MSB to 0

  write_byte(register_addr);

  pinMode(SDIO, INPUT);                         // High-Z mode

  delayMicroseconds(100);                       // T_hold >= 100us from specifications

  uint8_t read_data = 0;
  for (int8_t i = 7; i >= 0; i--) {
    digitalWrite(SCK, LOW);                     // Start clock signal
    delayMicroseconds(50);                      // Same as mouse application
    digitalWrite(SCK, HIGH);                    // Data must be read on transition from 0 to 1
    read_data += digitalRead(SDIO) << i;        // Data line must be read here
    delayMicroseconds(50);                      // Same as mouse application
  }

  return read_data;
}


// Low level functions
void write_byte (uint8_t byte_val) {
  pinMode(SDIO, OUTPUT);

  for (int8_t i = 7; i >= 0; i--) {
    digitalWrite(SCK, LOW);                     // Start clock signal
    digitalWrite(SDIO, byte_val & (1 << i));    // Data line must be set here
    delayMicroseconds(50);                      // Same as mouse application
    digitalWrite(SCK, HIGH);                    // A2610 latchs data on transition from 0 to 1
    delayMicroseconds(50);                      // Same as mouse application
  }
}
