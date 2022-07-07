#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

//#include "monitoring.h"
#ifdef THR_SERIAL
#include "SerialThread.h"
#endif

#ifdef THR_ONEWIRE
#include "OneWireThread.h"
#endif

#ifdef THR_ACQUIRE
#include "AcquireThread.h"
#endif

#ifdef THR_PH
#include "phThread.h"
#endif


#ifdef THR_LCD
#include "LCDThread.h"
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

#ifdef THR_ACQUIRE
      THD_TABLE_ENTRY(waThreadAcquisition, NULL, ThreadAcquisition, NULL)
#endif

#ifdef THR_PH
      THD_TABLE_ENTRY(waThreadPh, NULL, ThreadPh, NULL)
#endif

#ifdef THR_ONEWIRE
THD_TABLE_ENTRY(waThreadOneWire, NULL, ThreadOneWire, NULL)
#endif

#ifdef THR_LCD
      THD_TABLE_ENTRY(waThreadLCD, NULL, ThreadLCD, NULL)
#endif

#ifdef THR_SERIAL
      THD_TABLE_ENTRY(waThreadSerial, NULL, ThreadSerial, NULL)
#endif
//   THD_TABLE_ENTRY(waThread2, "thread2", Thread2, NULL)
THD_TABLE_END
//------------------------------------------------------------------------------