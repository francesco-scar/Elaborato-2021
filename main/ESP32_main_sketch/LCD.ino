#ifndef DISABLE_LCD

#define N_PAGES 29
const int page_time_s[N_PAGES] = {15, 30, 45, 45, 45, 20, 50, 50, 15, 15, 30, 45, 45, 45, 20, 50, 50, 15, 15, 30, 45, 45, 45, 20, 50, 50, 15, 30, 60}
#include <LiquidCrystal_Software_I2C.h>     // https://github.com/francesco-scar/LiquidCrystal_Software_I2C

#define SDA_PIN 26
#define SCL_PIN 25

// Usage: LiquidCrystal_I2C lcd(ADDRESS, COLUMNS, ROWS, SDA_PIN, SCL_PIN);
LiquidCrystal_I2C lcd(0x3f, 16, 2, SDA_PIN, SCL_PIN);   // Set the LCD address to 0x27 for a 16 chars and 2 line display

void init_display() {

  lcd.init();                               // LCD initialization
  lcd.backlight();                          // Turn on backlight
  lcd.clear();
  lcd.print(WiFi.localIP());
}

void updateLCD() {
  unsigned long t = millis();
  
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
}

#endif
