#include <ChNil.h>

SEMAPHORE_DECL(lockTimeCriticalZone,
               1);  // only one process in some specific zones

// ADC reading for pH and EC
SEMAPHORE_DECL(lockADCReading,
               1);  // only one process in some specific zones