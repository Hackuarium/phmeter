#include <Arduino.h>
#include <ChNil.h>

#include "Funcs.h"

#ifdef THR_LCD

#include <LiquidCrystal.h>
#include "lcd.h"
#include "sleep.h"

extern LiquidCrystal lcd;

THD_FUNCTION(ThreadLCD, arg) {
  // initialize the library with the numbers of the interface pins
  setupRotary();
  wakeUpScreen();

  setParameter(PARAM_MENU, 0);
  setParameter(PARAM_STATUS, 0);

  while (true) {
    lcdMenu();
    chThdSleep(40);
  }
}

#endif
