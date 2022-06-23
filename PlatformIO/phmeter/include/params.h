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



// config.h
/**
 * @file config.h
 * @brief Define macros for run threads and configurations.
 * @version 0.1
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define MONITORING_LED 13 /**< Indication LED or test */

#define MAX_PARAM 52 /**< Maximum parameters to save in EEPROM */
#define PARAM_ERROR 24

//#define THR_MONITORING 1
// #define THR_SERIAL 1

// 08/21/2020
// #define THR_I2C 1

// 06/01/2021
// #define THR_PH_AND_CONDUCTIVITY
#define THR_PH

//#define THR_LCD


// 08/24/2020
// Enable Thread into WireMaster[.h,.cpp] into hack folder
//#define THR_WIRE_MASTER 1
// Enable Thread into WireM[.h,.cpp] src folder
//#define THR_WIRE_M 1