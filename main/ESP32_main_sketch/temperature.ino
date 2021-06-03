#define DHT_PIN 27

class DHT_11 {                           // Classe per sensore dht22
  public:
    float humidity, temperature;         // Attributi pubblici

    DHT_11(int pin) {
      this->pin = pin;
    }

    void read() {                        // Metodo pubblico, acquisizione
      pinMode(pin, OUTPUT);

      digitalWrite(pin, LOW);            // Richiesta dati
      delay(20);
      pinMode(pin, INPUT_PULLUP);

      delayMicroseconds(55);
      // Attesa risposta del sensore
      unsigned long timeout_t = millis();
      while (digitalRead(pin) != 1 && millis() - timeout_t < 10);
      timeout_t = millis();
      while (digitalRead(pin) != 0 && millis() - timeout_t < 10);

      byte bytes[5] = {0, 0, 0, 0, 0};
      long t = 0;

      for (int i = 0; i < 40; i++) {     // Lettura dei 5 byte
        t = pulseIn(pin, HIGH, 1000);

        bytes[i / 8] = bytes[i / 8] << 1;

        if (t > 40) {                    // Bit valore 1
          bytes[i / 8] += 1;
        } else if (t == 0) {             // Errore nella lettura
          this->humidity = -999;
          this->temperature = -999;

          return;
        }
      }


      // Controllo checksum e calcolo
      if (uint8_t(bytes[0] + bytes[1] + bytes[2] + bytes[3]) != bytes[4]) {
        this->humidity = -999;
        this->temperature = -999;

        return;
      }
      //      this->humidity = (bytes[0] << 8 | bytes[1]) / 10.0;                                                                   // This was for DHT22 only
      //      this->temperature = (((bytes[2] & 0b01111111)  << 8) | bytes[3]) * ((bytes[2] & 0b10000000) ? -1 : 1) / 10.0;         // This was for DHT22 only
      this->humidity = bytes[0];                        // Ignore decimal part
      this->temperature = bytes[2] ;
    }

  private:
    int pin;                             // Attributo privato, pin dht
};


DHT_11 sensor(DHT_PIN);                  // Oggetti per sensore


float get_temperature() {
  sensor.read();                         // Lettura dei valori
  return sensor.temperature;
}
