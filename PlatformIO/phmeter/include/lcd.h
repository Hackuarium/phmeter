#include <ChNil.h>
#include "config.h"

#ifdef THR_LCD

// NIL_WORKING_AREA(waThreadI2C, 20);  // minimum 20
// NIL_THREAD(ThreadI2C, arg);
THD_WORKING_AREA(waThreadLCD, 250);  // minimum 20
THD_FUNCTION(ThreadLCD, arg);

#endif