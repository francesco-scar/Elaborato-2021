#include <avr/pgmspace.h>
#include "special_keys_definition.h"

#define _sda_pin 11
#define _scl_pin 12

/*
 * D0-D7    8-bit IO bus
 * D8       PS2 Keyboard interrupt
 * D13      PS2 Keyboard buffer enable
 */


volatile char c = 0;
volatile bool maiusc = 0;
volatile bool altgr = 0;
volatile bool endScanCode = 0;

ISR (PCINT0_vect) {                   // Handle pin change interrupt for D8 to D13 here
  if (PINB & 0b00000001) {            // If it was high
    PORTB |= 0b00100000;              // Turn on D13 (PS2 Keyboard buffer)
    delayMicroseconds(5);
    char scanCode = PIND;             // Read Keyboard buffer output
    PORTB &= 0b11011111;              // Turn off D13 (PS2 Keyboard buffer)
    c = scanCode;
/*    
    if (scanCode < 132){
      c = keymap[0][scanCode];
//      if (scanCode)
    } else {
      c = 0;
    }*/
  }
}                                     // End of PCINT2_vect


void setup () {
  // pin change interrupt (example for D4)
  PCMSK0 |= bit (PCINT0);  // want pin 8
  PCIFR  |= bit (PCIF0);    // clear any outstanding interrupts
  PCICR  |= bit (PCIE0);    // enable pin change interrupts for D8 to D13

  DDRB &= 0b11111110;       // Pin 8 as input
  DDRB |= 0b00100000;       // Pin 13 as output
  PORTB |= 0b00000001;      // Pullup pin 8
  PORTB &= 0b11011111;      // Put pin 13 LOW

  DDRD = 0b00000000;        // All portB pin as input
  PORTD = 0b11111111;       // Pullup
  
  pinMode (13, OUTPUT);
}  // end of setup

void loop () {
  if (c){
    writeI2C(1, c);
    c = 0;
  }
}


uint8_t writeI2C(uint8_t _Addr, uint8_t _data){
    /* This is the function that actually sends data in I2C protocol
     * it has a similar function of:
     *   Wire.begin();
     *   Wire.beginTransmission(_Addr);
     *   Wire.write((int)(_data|_backlightval));
     *   Wire.endTransmission();
     * 
     * but it allows you to use any pin you want (passed as 4th and 5th argument in lcd object constructor).
     * As you can see some delays are commented out because the write operation itself already take enought time
     */
    
    pinMode(_sda_pin, INPUT_PULLUP);    // I put those in pullup before set pinmode OUTPUT to avoid LOW level glitches
    pinMode(_scl_pin, INPUT_PULLUP);
    pinMode(_sda_pin, OUTPUT);
    pinMode(_scl_pin, OUTPUT);
    digitalWrite(_sda_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(_scl_pin, LOW);
    
    for (int8_t i = 6; i >= 0; i--){
        digitalWrite(_scl_pin, LOW);
        digitalWrite(_sda_pin, _Addr & (1<<i));
//        delayMicroseconds(5);
        digitalWrite(_scl_pin, HIGH);
//        delayMicroseconds(5);
    }
    digitalWrite(_scl_pin, LOW);
    digitalWrite(_sda_pin, LOW);    // Write flag
//    delayMicroseconds(5);
    digitalWrite(_scl_pin, HIGH);
//    delayMicroseconds(5);
    
    digitalWrite(_scl_pin, LOW);
    pinMode(_sda_pin, INPUT_PULLUP);
    delayMicroseconds(5);
    digitalWrite(_scl_pin, HIGH);
    
    if (digitalRead(_sda_pin) == 1){    // Received NACK flag
//        return 1;
    }
    
    delayMicroseconds(5);
    digitalWrite(_scl_pin, LOW);
    delayMicroseconds(5);
    pinMode(_sda_pin, OUTPUT);
    
    for (int8_t i = 7; i >= 0; i--){
        digitalWrite(_scl_pin, LOW);
        digitalWrite(_sda_pin, (_data) & (1<<i));
//        delayMicroseconds(5);
        digitalWrite(_scl_pin, HIGH);
//        delayMicroseconds(5);
    }
    
    digitalWrite(_scl_pin, LOW);
    pinMode(_sda_pin, INPUT_PULLUP);
    delayMicroseconds(5);
    digitalWrite(_scl_pin, HIGH);
    
    if (digitalRead(_sda_pin) == 1){    // Received NACK flag
//        return 2;
    }
    
    delayMicroseconds(5);
    digitalWrite(_scl_pin, LOW);
    delayMicroseconds(5);
    pinMode(_sda_pin, OUTPUT);
    
    digitalWrite(_sda_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(_scl_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_sda_pin, HIGH);
    
    return 0;
}
