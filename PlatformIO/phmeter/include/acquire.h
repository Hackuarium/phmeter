#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_EC

THD_WORKING_AREA(waThreadAcquisition, 56);
THD_FUNCTION(ThreadAcquisition, arg);

#endif