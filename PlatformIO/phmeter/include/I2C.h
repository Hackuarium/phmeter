// #include <NilRTOS.h>
#include <ChNil.h>
#include "config.h"

// code taken from
// https://github.com/Hackuarium/simple-spectro/tree/master/arduino/SimpleSpectro.
// Thread allowing serial over usb communication.

#ifdef THR_I2C

// NIL_WORKING_AREA(waThreadI2C, 20);  // minimum 20
// NIL_THREAD(ThreadI2C, arg);
THD_WORKING_AREA(waThreadI2C, 20);  // minimum 20
THD_FUNCTION(ThreadI2C, arg);

#endif