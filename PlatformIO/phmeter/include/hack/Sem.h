#include <ChNil.h>

// only one process in some specific zones
extern semaphore_t lockTimeCriticalZone;

// only one process in some specific zones
extern semaphore_t lockADCReading;  // ADC reading for pH and EC
