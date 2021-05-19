// #include <NilRTOS.h>
#include <ChNil.h>
//#include <avr/wdt.h>
#include "config.h"

#ifdef THR_MONITORING

// NIL_WORKING_AREA(waThreadMonitoring, 0);
// NIL_THREAD(ThreadMonitoring, arg);
THD_WORKING_AREA(waThreadMonitoring, 0);
THD_FUNCTION(ThreadMonitoring, arg);

#endif