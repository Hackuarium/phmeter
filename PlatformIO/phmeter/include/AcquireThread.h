#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#if (THR_EC || THR_PH)

THD_WORKING_AREA(waThreadAcquisition, 56);
THD_FUNCTION(ThreadAcquisition, arg);

#endif