#include <Arduino.h>
#include <ChNil.h>

#include "params.h"

//#include "monitoring.h"
#ifdef THR_SERIAL
#include "serialThread.h"
#endif

#include "I2C.h"

#ifdef THR_PH
#include "phThread.h"
#endif

#ifdef THR_WIRE_MASTER
//16/09/2020
//#include "WireMaster.h"
#include"WireM.h"

#endif

#ifdef THR_LCD

#include "lcd.h"

#endif
//#include "hack/Serial.h"

//#include <SerialSpecific.h>


/*******************************************************************************
                          NilRTOS Multithreading Table
      The higher in the Table The higher the priority
*******************************************************************************/
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
#ifdef THR_PH
      THD_TABLE_ENTRY(waThreadPh, NULL, ThreadPh, NULL)
#endif
#ifdef THR_LCD
      THD_TABLE_ENTRY(waThreadLCD, NULL, ThreadLCD, NULL)
#endif
//   THD_TABLE_ENTRY(waThread2, "thread2", Thread2, NULL)
THD_TABLE_END
//------------------------------------------------------------------------------