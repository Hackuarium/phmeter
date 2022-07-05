#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_EC

THD_WORKING_AREA(waThreadEC, 56);
THD_FUNCTION(ThreadEC, arg);

#endif