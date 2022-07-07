// part of the EEPROM is for the log
// we should be able to save and reload the log

// log is saved in the format ID / in1 / out1 / ... / in8 / out8
// ID is a sequential number
// We expect to add an entry every hour

#include <Arduino.h>
#include <ChNil.h>
#include "Funcs.h"

#ifdef THR_EEPROM_LOGGER

#include "HackEEPROM.h"

#ifdef LOG_INTERVAL

THD_FUNCTION(ThreadLogger, arg) {
  chThdSleep(5000);

  // Find last address entry ID
  loggerInit();

  // Set first run
  writeLog(EVENT_ARDUINO_BOOT, 0);

  chThdSleepSeconds((long)LOG_INTERVAL - (long)(millis() / 1000UL) + 5UL);
  
  while (true) {
    chThdSleep(1000);
    // avoids logging during the second x+1, ensure x+LOG_INTERVAL
    // because epoch is only precise to the second so the logging is evenly
    // spaced
    // unsigned long waiting = (unsigned long)LOG_INTERVAL - (millis() % 1000UL);
    // chThdSleep((long)LOG_INTERVAL * 1000UL - millis() % 1000UL + 100UL);

    int delayBetweenLog = LOG_INTERVAL;
    if (delayBetweenLog < 300)
      delayBetweenLog = 300;

    writeLog(0, 0);
    chThdSleepSeconds(delayBetweenLog);
  }
}

#endif

#endif
