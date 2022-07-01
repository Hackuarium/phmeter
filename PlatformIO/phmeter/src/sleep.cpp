#include <Arduino.h>
#include <ChNil.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include "Params.h"

#include <LiquidCrystal.h>
#include "lcd.h"

extern LiquidCrystal lcd;

byte lcdPins[] = {LCD_E,  LCD_RS, LCD_D4, LCD_D5, LCD_D6,
                  LCD_D7, LCD_VO, LCD_BL, LCD_ON};

void sleepScreen() {
  for (byte i = 0; i < sizeof(lcdPins); i++) {
    pinMode(lcdPins[i], INPUT);
  }
}

void wakeUpScreen() {
  for (byte i = 0; i < sizeof(lcdPins); i++) {
    pinMode(lcdPins[i], OUTPUT);
  }
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // LCD on

  chThdSleepMilliseconds(200);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}


void sleepNow () {
  // more information about sleep: https://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html

  noInterrupts();          // make sure we don't get interrupted before we sleep
  wdt_disable();
  sleep_enable ();          // enables the sleep bit in the mcucr register
  sleepScreen();
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);

  chThdSleepMilliseconds(2);  // smll debouncing
 // attachInterrupt (digitalPinToInterrupt (ROT_B), empty, CHANGE);

  interrupts ();           // interrupts allowed now, next instruction WILL be executed
  sleep_cpu ();            // here the device is put to sleep

  sleep_disable ();         // first thing after waking from sleep:
 // detachInterrupt (digitalPinToInterrupt (ROT_B));      // stop LOW interrupt on D2
  wdt_enable(WDTO_8S);  //reactivate the watchdog
  wakeUpScreen();
}

void empty() {}