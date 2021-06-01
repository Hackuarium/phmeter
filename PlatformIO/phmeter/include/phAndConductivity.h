#include <ChNil.h>
#include "config.h"

#ifdef THR_PH_AND_CONDUCTIVITY

#include <HX711.h>

//#define PH_AND_CONDUCTIVITY_DATA        A1
//#define PH_AND_CONDUCTIVITY_CLK         A0     //need to redefine the calibration parameters and process (see "HX711")

THD_WORKING_AREA(waThreadPhAndConductivity, 56);
THD_FUNCTION(ThreadPhAndConductivity, arg);

#endif