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
// NIL_THREADS_TABLE_BEGIN()


// // logger should have priority to prevent any corruption of flash memory

// #ifdef THR_MONITORING
// NIL_THREADS_TABLE_ENTRY(NULL,
//                         ThreadMonitoring,
//                         NULL,
//                         waThreadMonitoring,
//                         sizeof(waThreadMonitoring))
// #endif

// #ifdef THR_SERIAL
// NIL_THREADS_TABLE_ENTRY(NULL,
//                         ThreadSerial,
//                         NULL,
//                         waThreadSerial,
//                         sizeof(waThreadSerial))
// #endif

// #ifdef THR_I2C
// NIL_THREADS_TABLE_ENTRY(NULL,
//                         ThreadI2C,
//                         NULL,
//                         waThreadI2C,
//                         sizeof(waThreadI2C))
// #endif


// /*ifdef THR_WIRE_MASTER 
// NIL_THREADS_TABLE_ENTRY(NULL,
//                         ThreadWireMaster,
//                         NULL,
//                         waThreadWireMaster,
//                         sizeof(waThreadWireMaster))
// #endif*/

// NIL_THREADS_TABLE_END()

//------------------------------------------------------------------------------
/*
 * Threads static table, one entry per thread.  A thread's priority is
 * determined by its position in the table with highest priority first.
 *
 * These threads start with a null argument.  A thread's name may also
 * be null to save RAM since the name is currently not used.
 */
THD_TABLE_BEGIN

// logger should have priority to prevent any corruption of flash memory

#ifdef THR_MONITORING
      THD_TABLE_ENTRY(waThreadMonitoring, NULL, ThreadMonitoring, NULL)
#endif
#ifdef THR_SERIAL
      THD_TABLE_ENTRY(waThreadSerial, NULL, ThreadSerial, NULL)
#endif
#ifdef THR_I2C
      THD_TABLE_ENTRY(waThreadI2C, NULL, ThreadI2C, NULL)
#endif
//   THD_TABLE_ENTRY(waThread2, "thread2", Thread2, NULL)
THD_TABLE_END
//------------------------------------------------------------------------------