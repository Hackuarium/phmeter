#include <Arduino.h>
// Arduino.h can be changing by:
//#include <inttypes.h>
//#ifndef __AVR__
//#include <sys/types.h> // for __time_t_defined, but avr libc lacks sys/types.h
//#endif
//#include "config.h"

#define INT_MAX_VALUE 32767
#define INT_MIN_VALUE -32768
#define LONG_MAX_VALUE 2147483647

// value that should not be taken into account
// in case of error the parameter is set to this value
#define ERROR_VALUE -32768

//From config.h:
#define MAX_PARAM 52

#define EE_START_PARAM 0  // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM \
  (MAX_PARAM * 2 - 1)  // The last parameter is stored at byte 50-51

#define EE_QUALIFIER (MAX_PARAM * 2)

#define EEPROM_MIN_ADDR 0
#define EEPROM_MAX_ADDR 1023

extern int parameters[MAX_PARAM];

boolean setParameterBit(byte number, byte bitToSet);
boolean getParameterBit(byte number, byte bitToRead);
boolean clearParameterBit(byte number, byte bitToClear);
void toggleParameterBit(byte number, byte bitToToggle);

void writeLog(uint16_t event_number, int parameter_value);
boolean saveAndLogError(boolean isError, byte errorFlag);

void setupParameters();
void saveParameters();
void printParameters(Print* output);
void printCompactParameters(Print* output);
void printCompactParameters(Print* output, byte number);

void setAndSaveParameter(byte number, int value);
void incrementParameter(byte number);

void setParameter(byte number, int value);
int getParameter(byte number);
void printParameter(Print* output, byte number);
