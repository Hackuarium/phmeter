// #include <NilRTOS.h>
#include <ChNil.h>
//#include<WireMaster.h>

#include"config.h"

#ifdef THR_WIRE_MASTER
#ifdef THR_WIRE_M

// NIL_WORKING_AREA(waThreadWireMaster, 200);
// NIL_THREAD(ThreadWireMaster, arg);
THD_WORKING_AREA(waThreadWireMaster, 200);
THD_FUNCTION(ThreadWireMaster, arg);

#endif
#endif