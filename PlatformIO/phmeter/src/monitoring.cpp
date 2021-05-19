// #include <NilRTOS.h>
#include <ChNil.h>
#include <avr/wdt.h>
#include "config.h"

#ifdef THR_MONITORING

//NIL_WORKING_AREA(waThreadMonitoring, 0);
// NIL_THREAD(ThreadMonitoring, arg) {
THD_FUNCTION(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(8000);  // Do not start the watchdog too quickly
  wdt_enable(WDTO_8S);            // activate the watchdog
#ifdef MONITORING_LED
  pinMode(MONITORING_LED, OUTPUT);  // diode pin out
#endif

  while (true) {
#ifdef MONITORING_LED
    digitalWrite(MONITORING_LED, HIGH);
    nilThdSleepMilliseconds(500);
    digitalWrite(MONITORING_LED, LOW);
    nilThdSleepMilliseconds(500);
#endif
    wdt_reset();  // resed avoid the automatic reboot
  }
}

#endif