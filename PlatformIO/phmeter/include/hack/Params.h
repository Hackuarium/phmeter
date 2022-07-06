/*********************************************
   This file is used to declare the parameters
   table used by the program.

   We use the EEPROM for saving the parameters
   changed by the user during the functionment
   of the Bioreactor.

   The parameter are loaded during the boot.

   All change to important parameters are saved
   to the EEPROM
 *********************************************/
#include <Arduino.h>
#include <ChNil.h>

#define SOFTWARE_VERSION "v1.0.0-b"

/******************************
  THREADS
*******************************/

#define THR_LCD
// #define THR_PH
// #define THR_EC
// #define THR_WIRE_MASTER 1
#define THR_SST_LOGGER 1
#define THR_SERIAL 1
#define THR_ONEWIRE 1
#define THR_ERROR 1
#define THR_STEPS 1
#define THR_OUTPUTS 1

#define NB_PARAMETERS_LINEAR_LOGS 26

// Definition of all events to be logged
#define EVENT_ARDUINO_BOOT 1
#define EVENT_ARDUINO_SET_SAFE 2

#define EVENT_STATUS_ENABLE 3
#define EVENT_STATUS_DISABLE 4

#define EVENT_ERROR_FAILED 6
#define EVENT_ERROR_RECOVER 7

#define EVENT_ERROR_NOT_FOUND_ENTRY_N 150

#define EVENT_SAVE_ALL_PARAMETER 255
// extern const uint8_t EVENT_SAVE_ALL_PARAMETER;
// When parameters are set (and saved) an event is recorded (256-281 : A-Z +
// .... (if more parameters than 262 ...)
#define EVENT_PARAMETER_SET 256

// OUTPUT Thread
#define OUT_1 11
#define OUT_2 12
#define OUT_3 A2
#define OUT_4 A3

// LCD Thread
#define LCD_E  6
#define LCD_RS 4
#define LCD_D4 8
#define LCD_D5 9
#define LCD_D6 10
#define LCD_D7 5
#define LCD_BL 13    // back light
#define LCD_VO 13    // contrast (on / off to spare energy)
#define LCD_ON 13  // power on LCD
#define LCD_NB_ROWS 2
#define LCD_NB_COLUMNS 16

#define PARAM_MENU 25  // current menu
#define PARAM_NEXT_EXP 14  // next experiment, 0 blank and then for kinetic
#define STATUS_ONE_SPECTRUM 1
#define STATUS_KINETIC 2
#define STATUS_SEQUENCE 3
#define PARAM_BEFORE_DELAY 10  // delay before taking blank
#define PARAM_FIRST_DELAY 11
#define PARAM_INTER_DELAY 12
#define PARAM_NUMPER_EXP 13
#define PARAM_COLOR 23  // color used to display the results
#define PARAM_ACTIVE_PROBES 21
#define PH_DOUT  A0
#define EC       A5
#define TEMP_1   PIN_SPI_SS
#define TEMP_2   30
#define BATTERY_LEVEL 128   // not available in version A
#define TEMPERATURE   129   // not available in version A
#define PARAM_WAIT 15      // current time to wait
#define STATUS_TEST_LEDS 4

#define ROT_A 0
#define ROT_B 1
#define ROT_PUSH 7


#define PARAM_FLAGS 17
#define PARAM_FLAG_INVERT_ROTARY 0  // invert rotary direction
#define PARAM_FLAG_RAW_VALUES 1     // invert rotary direction

// Adquire Thread
#define TOTAL_NUMBER_PROBES 2
#define TOTAL_PARAMETERS 5
// Declared in lcd.cpp
extern uint8_t nbProbes;              // number of active leds
extern uint8_t nbParameters;        // number of parameters to record
extern uint8_t dataRowSize;         // size of a data row (number of entries in data)
extern uint8_t maxNbRows;           // calculate value depending the size of EEPROM dedicated to logs
extern uint8_t ALL_PARAMETERS[TOTAL_PARAMETERS];  // all possible reading values
extern uint8_t ACTIVE_PARAMETERS[TOTAL_PARAMETERS];


// ERROR Thread
#define OUT_ERROR A4

// ONE WIRE Thread
#define TEMP_EXT1 7
#define TEMP_EXT2 A5
#define TEMP_PCB A2

// EEPROM || SST Thread
#define EVENT_LOGGING 1


// PH Thread
#define PH_DATA        A0
#define PH_CLK         A1

// Acquire Thread
#define TARGET_INTENSITY_PH 45000
#define TARGET_INTENSITY_EC 45000
#define DATA_SIZE 240
#define PARAM_BATTERY 18      // battery voltage (hundredths of volt)
#define PARAM_NUMBER_ACQ \
  16  // number of acquisition of 100ms that will be taken


/******************************
  SERIAL, LOGGER AND DEBUGGERS
*******************************/

#define MAX_PARAM 68

#ifdef THR_SST_LOGGER
#define FLASH_SELECT 1   // Flash SS_SPI
#define LOG_INTERVAL 300  // Interval in (s) between logs logger
#define EVENT_LOGGING 1
#endif

/******************************
  PARAMETERS
*******************************/
#define PARAM_TEMP_EXT1 0  // A - temperature of the solution
#define PARAM_TEMP_EXT2 1  // B - temperature of the solution

#define PARAM_PH        2  // C - pH in unit of bits
#define PARAM_PH_H      3  // D - pH in unit of potential of hydrogen
#define PARAM_PH_TARGET 4  // E - Desired pH

#define PARAM_EC    5     // F - Electrolytic Conductivity in unit of bits
#define PARAM_EC_US 6     // G - Electrolytic Conductivity in unit of micro Siemens

#define PARAM_PH_FACTOR 26  // AD - PH calibration: conversion factor digital -> H (ph=FACTOR*dig_unit)
#define PARAM_PH_NEUTRAL \
  27  // AE - PH calibration: digital offset value when bioreactor is full of pure water

#define PARAM_EC_FACTOR \
  28  // AF - EC calibration: conversion factor digital -> uS
      // (ec=FACTOR*dig_unit)
#define PARAM_EC_NEUTRAL \
  29  // AG - EC calibration: digital offset value when bioreactor is full of pure water

#define PARAM_CURRENT_STEP 22
#define PARAM_CURRENT_WAIT_TIME 23
// 36-51 is used by the 16 allowed step
#define FIRST_STEP_PARAMETER 52  // BA
#define LAST_STEP_PARAMETER 67   // BP
#define NB_STEP_PARAMETERS LAST_STEP_PARAMETER - FIRST_STEP_PARAMETER + 1

/******************
   FLAG DEFINITION
 ******************/
#define PARAM_ERROR 24  // Y - errors
// extern const int PARAM_ERROR;
#define FLAG_TEMP_EXT1_PROBE_ERROR \
  0  // external temperature 1 probe failed (one wire not answering)
#define FLAG_TEMP_EXT2_PROBE_ERROR \
  1  // external temperature 2 probe failed (one wire not answering)
#define FLAG_TEMP_EXT1_RANGE_ERROR 2  // temperature of liquid is outside range
#define FLAG_TEMP_EXT2_RANGE_ERROR 3  // temperature of liquid is outside range
#define MASK_TEMP_ERROR 0b00001111  // where are the bit for temperature error

#define FLAG_PH_RANGE_ERROR 4     // the pH is outside range
#define MASK_PH_ERROR 0b00010000  // where are the bit for weight error

#define FLAG_EC_RANGE_ERROR 5     // the EC is outside range
#define MASK_EC_ERROR 0b00100000  // where are the bit for EC error

#define PARAM_ENABLED 25  // Z - enabled service (set by user)
#define PARAM_STATUS 51   // AZ - currently active service

// the following flags are defined for PARAM_STATUS and PARAM_ENABLED
#define FLAG_OUTPUT_1 0
#define FLAG_OUTPUT_2 1
#define FLAG_OUTPUT_3 2
#define FLAG_OUTPUT_4 3

// PARAM_STATUS
#define FLAG_PH_CONTROL   4 // Enable/disable pH control
#define FLAG_PH_CALIBRATE 5 // Enable/disable pH calibration
#define FLAG_RELAY_ACID   6 // Enable/disable acid addition
#define FLAG_RELAY_BASE   7 // Enable/disable base addition

// value that should not be taken into account
// in case of error the parameter is set to this value
#define ERROR_VALUE -32768

/*******************************************************************************
      Funcs.h
*******************************************************************************/

#define INT_MAX_VALUE 32767
#define INT_MIN_VALUE -32768
#define LONG_MAX_VALUE 2147483647

#define EE_START_PARAM 0  // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM \
  (MAX_PARAM * 2 - 1)  // The last parameter is stored at byte 50-51

#define EE_QUALIFIER (MAX_PARAM * 2)

#define EEPROM_MIN_ADDR 0
#define EEPROM_MAX_ADDR 1023

/*******************************************************************************
      Serial.h
*******************************************************************************/

#define SERIAL_BUFFER_LENGTH 32
#define SERIAL_MAX_PARAM_VALUE_LENGTH 32

// setting ATmega32U4 as I2C slave.
#ifndef I2C_HARDWARE
#define I2C_HARDWARE 1
#endif

/*******************************************************************************
      WireMaster.h
*******************************************************************************/

#define I2C_TIMEOUT 10
#define I2C_SLOWMODE 1
#define WIRE_MAX_DEVICES 8

/*******************************************************************************
      EEPROMLogger.h
*******************************************************************************/
//#define LOG_INTERVAL      10  //Interval in (s) between logs logger

#define LOG_ENTRY_LENGTH (NB_PARAMETERS_LINEAR_LOGS + 2) * 2
#define NUMBER_LOGS 960 / LOG_ENTRY_LENGTH

#define FIRST_ADDRESS 64
#define LAST_ADDRESS 1023