// Until pin 7 it's port D, from 8 to 13 it's port B; and analog pins from 14 to 19 (A0 to A5) are in port C
#define GET_DDR(pin) ((pin < 8) ? (DDRD) : ((pin < 14) ? (DDRB) : (DDRC)))
#define GET_PORT(pin) ((pin < 8) ? (PORTD) : ((pin < 14) ? (PORTB) : (PORTC)))
#define GET_PIN(pin) ((pin < 8) ? (PIND) : ((pin < 14) ? (PINB) : (PINC)))

// Get a bit mask for each port pin (refer to pinout below)
#define GET_BIT_MASK(pin) ((pin < 8) ? (1 << pin) : ((pin < 14) ? (1 << (pin-8)) : (1 << (pin-14))))
