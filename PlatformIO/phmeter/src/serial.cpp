// #include <NilRTOS.h>
#include <ChNil.h>
#include "config.h"

#include "serialUtilities.h"
#include "params.h"

// 08/24/2020
//#include "WireMaster.h"

// code taken from
// https://github.com/Hackuarium/simple-spectro.
// Thread allowing serial over usb communication.

#define SERIAL_BUFFER_LENGTH 32  // 32 - 1 (\0) space available
/** EEPROM store 16 bits values:
 * [-65536,...,0,...,+65535] */
#define SERIAL_MAX_PARAM_VALUE_LENGTH 6 

char serialBuffer[SERIAL_BUFFER_LENGTH];
uint8_t serialBufferPosition = 0;


/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.

  This method will mainly set/read the parameters:
  Uppercase + number + CR ('-' and 1 to 5 digit) store a parameter
  (0 to 25 depending the letter, starting 26 using to letter like 'AA')
  example: A100, A-1
  -> Many parameters may be set at once
  example: C10,20,30,40,50
  Uppercase + CR read the parameter
  example: A
  -> Many parameters may be read at once
  example: A,B,C,D

  It is also possible to write some data to a specific I2C device using
  nnnRRxxx where
  * nnn : the I2C device number
  * RR : the register to write as a letter: A for 0, B for 1, etc.
  * xxx : a number

  s : read all the parameters
  h : help
  l : show the log file
*/
void printSpecificHelp(Print* output) { }

void printHelp(Print* output) {
  output->println(F("(h)elp"));
  // 08/24/2020
  /*
#ifdef THR_WIRE_MASTER
  output->println(F("(i)2c"));
#endif
*/
#ifdef THR_EEPROM_LOGGER
  output->println(F("(l)og"));
#endif
  output->println(F("(s)ettings"));

  output->println(F("(u)tilities"));
  printSpecificHelp(output);
}

void noThread(Print* output) {
  output->println(F("No Thread"));
}

void printResult(char* data, Print* output) {
  bool theEnd = false;  /**< Check if serial read have finished. */
  uint8_t paramCurrent = 0;  /**< Which parameter are we defining (A..Z,AA..AZ) */
  char paramValue[SERIAL_MAX_PARAM_VALUE_LENGTH];
  paramValue[0] = '\0';
  uint8_t paramValuePosition = 0;
  uint8_t i = 0;
  bool inValue = false;
  uint8_t wireTargetAddress = 0;  // used for the command like '55D123'

  while (!theEnd) {
    byte inChar = data[i];
    ++i;
    if (i == SERIAL_BUFFER_LENGTH) {  // Maximum length is reached
      theEnd = true;
    }
    if (inChar == '\0') { // NULL character is found
      theEnd = true;
    }
    else if ((inChar > 47 && inChar < 58) || inChar == '-' ||
               inValue) {  // A number (could be negative)
      if ( paramValuePosition < SERIAL_MAX_PARAM_VALUE_LENGTH ) {
        paramValue[ paramValuePosition ] = inChar;
        paramValue[ ++paramValuePosition ] = '\0';
      }
    }
    /*
     * An UPPERCASE character so we define the field. We extend however 
     * the code to allow 2 letters fields !!!
     */
    else if (inChar > 64 && inChar < 91) {
      if (paramCurrent > 0) {
        paramCurrent *= 26;
      } else {  // do we have a number before the uppercase ????
        if (paramValuePosition > 0) {
          // we have a target I2C device
          wireTargetAddress = atoi(paramValue);
          paramValuePosition = 0;
          paramValue[paramValuePosition] = '\0';
        }
      }
      paramCurrent += inChar - 64;
      if (paramCurrent > MAX_PARAM && wireTargetAddress == 0) {
        paramCurrent = 0;
      }
    }

    if (inChar == ',' || theEnd) {  // store value and increment
      if (paramCurrent > 0) {
        if (paramValuePosition > 0) {
          if (wireTargetAddress > 0) {
            // 08/24/2020
            /*
#ifdef THR_WIRE_MASTER
            wireWriteIntRegister(wireTargetAddress, paramCurrent - 1,
                                 atoi(paramValue));
#endif
*/
          } else {
            // Check this (params.h)
            setAndSaveParameter(paramCurrent - 1, atoi(paramValue));
          }
        }
        if (wireTargetAddress > 0) {
          // 08/24/2020
          /*
#ifdef THR_WIRE_MASTER
          output->println(
              wireReadIntRegister(wireTargetAddress, paramCurrent - 1));
#endif
*/
        } else {
          // Check this (params.h)
          output->println(parameters[paramCurrent - 1]);
        }
        // Reset current parameter and value position.
        paramCurrent = 0;
        paramValuePosition = 0;
        paramValue[0] = '\0';
      }
    }
    // It is not used.
    // we may have one or 2 lowercasee
    // if (data[0] > 96 && data[0] < 123 &&
    //     (i > 1 || data[1] < 97 || data[1] > 122)) {
    //   inValue = true;
    // }
  }

  // we will process the commands, it means it starts with lowercase
  switch (data[0]) {
    case 'h':
      printHelp(output);
      break;
      // 08/24/2020
      /*
#ifdef THR_WIRE_MASTER
    case 'i':
      processWireCommand(data[1], paramValue, output);
      break;
#endif
*/
#ifdef THR_EEPROM_LOGGER
    case 'l':
      processLoggerCommand(data[1], paramValue, output);
      break;
#endif
    case 's':
      printParameters(output);
      break;
    case 'u':
      // Check this (SerialUtilities.h)
      processUtilitiesCommand(data[1], paramValue, output);
      break;
    default:
    // Check this
      //processSpecificCommand(data, paramValue, output);
      // output->println(F("Command not found. Please use 'h' for help."));
      break;
  }
  output->println("");
}

#ifdef THR_SERIAL

//NIL_WORKING_AREA(waThreadSerial, 96);  // minimum 96
// NIL_THREAD(ThreadSerial, arg) {
THD_FUNCTION(ThreadSerial, arg) {
  Serial.begin(9600);
  while (true) {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == 10 || inChar == 13) { // 0x0A (LF) 0x0D (CR)
        // this is a carriage return;
        if (serialBufferPosition > 0) {
          printResult(serialBuffer, &Serial);
        }
        serialBufferPosition = 0;
        serialBuffer[0] = '\0'; // Null
      }
      else { // Save char
        if ( serialBufferPosition != SERIAL_BUFFER_LENGTH ) {
          serialBuffer[ serialBufferPosition ] = inChar;
          serialBuffer[ ++serialBufferPosition ] = '\0';
        }
        else {
          Serial.println("ERR - buffer overflowed ");
        }
      }
    }
    nilThdSleepMilliseconds(1);
  }
}

#endif
