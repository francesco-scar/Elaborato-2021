#define CLOCK 2
#define DATA 3

volatile int data = 0;

volatile int i = 10;

void getSerialBit() {
  if (i >= 0 && digitalRead(CLOCK) == 0){
    data += digitalRead(DATA) << i;
    i--;
  }
  if (i == -1 && digitalRead(CLOCK) == 1) {
    println_full_bin(data, 11);
    i = 10;
  }
}

void setup() {
  pinMode(CLOCK, INPUT);
  pinMode(DATA, INPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(CLOCK), getSerialBit, CHANGE);
}

void loop() {
  //println_full_bin(data, 11);
}


void println_full_bin(uint8_t bin, uint8_t bits){
  for (int i = bits-1; i >= 0; i--) {
    Serial.print((bool) (bin & (1 << i)));
  }
  Serial.println();
}
