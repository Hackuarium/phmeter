#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_LCD

THD_WORKING_AREA(waThreadLCD, 250);  // minimum 20
THD_FUNCTION(ThreadLCD, arg);

#endif