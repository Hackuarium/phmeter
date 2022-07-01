#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_LCD

#include <LiquidCrystal.h>
#include "lcd.h"

extern LiquidCrystal lcd;

THD_FUNCTION(ThreadLCD, arg) {
  // initialize the library with the numbers of the interface pins
  setupRotary();
  wakeUpScreen();
/*
  setParameter(PARAM_MENU, 0);
  setParameter(PARAM_STATUS, 0);
  */

  while (true) {
    //lcdMenu();
    lcd.setCursor(0, 0);
    lcd.print("pH"); lcd.print(2022);
    lcd.setCursor(0, 1);
    lcd.print("pHMeter v1.0");
    chThdSleep(40);
  }
}

#endif
