#ifndef DISABLE_LCD

#define N_PAGES 29
//const int page_time_s[N_PAGES] = {10, 60, 40, 45, 60, 70, 80, 30, 60, 30, 15, 15, 20, 70, 70, 30, 10,  5, 30, 15, 30, 45, 60, 25, 60, 70, 10, 45, 120}
const int page_time_s[N_PAGES] = { 5, 45, 30, 35, 45, 65, 70, 25, 50, 25, 10, 10, 10, 60, 60, 20,  5,  1, 25,  5, 25, 35, 55, 20, 55, 60, 115, 40, 30};
//                                 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26   27  28  29
#include <LiquidCrystal_Software_I2C.h>     // https://github.com/francesco-scar/LiquidCrystal_Software_I2C
#include <EEPROM.h>


#define SDA_PIN 26
#define SCL_PIN 25

#define EEPROM_SIZE 12
#define SAVE_TIME_INTERVAL 15
#define SAVE_TIME_ADDRESS 0

// Usage: LiquidCrystal_I2C lcd(ADDRESS, COLUMNS, ROWS, SDA_PIN, SCL_PIN);
LiquidCrystal_I2C lcd(0x3f, 16, 2, SDA_PIN, SCL_PIN);   // Set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t last_saved_timer;

void init_display() {
  EEPROM.begin(EEPROM_SIZE);
  lcd.init();                               // LCD initialization
  lcd.backlight();                          // Turn on backlight
  lcd.clear();
}

void clear_LCD() {
  lcd.clear();
}

void print_LCD(String string) {
  lcd.print(string);
}

void print_IP_LCD() {
  lcd.clear();
  lcd.print(WiFi.localIP());
  timer_offset = millis() - EEPROM.read(SAVE_TIME_ADDRESS)*SAVE_TIME_INTERVAL*1000;
}

void updateLCD() {
  unsigned long t = millis() - timer_offset;
  
  lcd.setCursor(0, 1);
  
  if (t/1000/60 < 10) {
    lcd.print('0');
  }
  lcd.print(t/1000/60);
  lcd.print(':');
  if ((t/1000)%60 < 10) {
    lcd.print('0');
  }
  lcd.print((t/1000)%60);

  lcd.print("   ");

  int page = 0;
  unsigned long t_sums = 0;
  for (page = 0; t_sums < t/1000 && page < N_PAGES; page++) {
    t_sums += page_time_s[page];
  }

  lcd.print(page);
  lcd.print("   ");
  if (page != N_PAGES) {
    lcd.print(t_sums - t/1000);
  }
  lcd.print("     ");            // Clear the end of the line

  if ((t/1000)%SAVE_TIME_INTERVAL == 0 && last_saved_timer != t/1000/SAVE_TIME_INTERVAL) {
    EEPROM.write(SAVE_TIME_ADDRESS, t/1000/SAVE_TIME_INTERVAL);
    last_saved_timer = t/1000/SAVE_TIME_INTERVAL;
    EEPROM.commit();
  }
}

#endif
