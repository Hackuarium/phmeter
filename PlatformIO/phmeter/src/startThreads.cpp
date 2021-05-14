#include "config.h"
//#include "monitoring.h"
#include "serial.h"
#include "I2C.h"

#ifdef THR_WIRE_MASTER
//16/09/2020
//#include "WireMaster.h"
#include"WireM.h"

#endif
//#include "hack/Serial.h"

//#include <SerialSpecific.h>

/****************************************************************
                NilRTOS Multithreading Table
      The higher in the Table The higher the priority
*****************************************************************/
NIL_THREADS_TABLE_BEGIN()

// logger should have priority to prevent any corruption of flash memory

#ifdef THR_MONITORING
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadMonitoring,
                        NULL,
                        waThreadMonitoring,
                        sizeof(waThreadMonitoring))
#endif

#ifdef THR_SERIAL
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadSerial,
                        NULL,
                        waThreadSerial,
                        sizeof(waThreadSerial))
#endif

#ifdef THR_I2C
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadI2C,
                        NULL,
                        waThreadI2C,
                        sizeof(waThreadI2C))
#endif


/*ifdef THR_WIRE_MASTER 
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadWireMaster,
                        NULL,
                        waThreadWireMaster,
                        sizeof(waThreadWireMaster))
#endif*/

NIL_THREADS_TABLE_END()