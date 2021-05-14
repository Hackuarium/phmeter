#include <Arduino.h>
// Arduino.h can be changing by:
//#include <inttypes.h>
//#ifndef __AVR__
//#include <sys/types.h> // for __time_t_defined, but avr libc lacks sys/types.h
//#endif
#include "config.h"

#include "toHex.h"
#include <TimeLib.h>

#include "params.h"
#include "eeprom.h" // getQualifier()


int parameters[MAX_PARAM];

boolean getParameterBit(byte number, byte bitToRead) {
  return (parameters[number] >> bitToRead) & 1;
}

boolean setParameterBit(byte number, byte bitToSet) {
  if (getParameterBit(number, bitToSet))
    return false;
  parameters[number] |= 1 << bitToSet;
  return true;
}

boolean clearParameterBit(byte number, byte bitToClear) {
  if (!getParameterBit(number, bitToClear))
    return false;
  parameters[number] &= ~(1 << bitToClear);
  return true;
}

void toggleParameterBit(byte number, byte bitToToggle) {
  parameters[number] ^= 1 << bitToToggle;
}

void setupParameters() {
  // We copy all the values in the parameters table
  eeprom_read_block((void*)parameters, (const void*)EE_START_PARAM,
                    MAX_PARAM * 2);
}

int getParameter(byte number) {
  return parameters[number];
}

void setParameter(byte number, int value) {
  parameters[number] = value;
}

void incrementParameter(byte number) {
  parameters[number]++;
}

void saveParameters() {
  for (byte i = 0; i < MAX_PARAM; i++) {
    eeprom_write_word((uint16_t*)EE_START_PARAM + i, parameters[i]);
  }
}

/*
  This will take time, around 4 ms
  This will also use the EEPROM that is limited to 100000 writes
*/
void setAndSaveParameter(byte number, int value) {
  parameters[number] = value;
  // The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*)EE_START_PARAM + number, value);
#ifdef EVENT_LOGGING
  writeLog(EVENT_PARAMETER_SET + number, value);
#endif
}

// this method will check if there was a change in the error status and log it
// in this case
boolean saveAndLogError(boolean isError, byte errorFlag) {
  if (isError) {
    if (setParameterBit(PARAM_ERROR, errorFlag)) {  // the status has changed
#ifdef EVENT_LOGGING
      writeLog(EVENT_ERROR_FAILED, errorFlag);
#endif
      return true;
    }
  } else {
    if (clearParameterBit(PARAM_ERROR, errorFlag)) {  // the status has changed
#ifdef EVENT_LOGGING
      writeLog(EVENT_ERROR_RECOVER, errorFlag);
#endif
      return true;
    }
  }
  return false;
}

void printParameter(Print* output, byte number) {
  output->print(number);
  output->print("-");
  if (number > 25) {
    output->print((char)(floor(number / 26) + 64));
  } else {
    output->print(" ");
  }
  output->print((char)(number - floor(number / 26) * 26 + 65));
  output->print(": ");
  output->println(parameters[number]);
}

void printParameters(Print* output) {
  setupParameters();
  for (int i = 0; i < MAX_PARAM; i++) {
    printParameter(output, i);
  }
}

void printCompactParameters(Print* output, byte number) {
  if (number > MAX_PARAM) {
    number = MAX_PARAM;
  }
  byte checkDigit = 0;

  // we first add epoch (32 bits)
  long nowVal = (long)now();
  checkDigit ^= toHex(output, nowVal);

  // Now, we print every 16 bits parameters
  for (int i = 0; i < number; i++) {
    int value = getParameter(i);
    checkDigit ^= toHex(output, value);
  }
  checkDigit ^= toHex(output, (int)getQualifier());
  toHex(output, checkDigit);
  output->println("");
}

void printCompactParameters(Print* output) {
  printCompactParameters(output, MAX_PARAM);
}
