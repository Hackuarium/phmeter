#include <Arduino.h>
#include <ChNil.h>
#include <avr/eeprom.h>
//#include <EEPROM.h>

#include "Funcs.h"
#include "Sem.h"
#include "libraries/time/TimeLib.h"

// Types of logs
#define ENTRY_SIZE_LINEAR_LOGS 64
#define SIZE_TIMESTAMPS 4
#define SIZE_COUNTER_ENTRY 4

// Definition of the log sectors in the flash for the logs
// 960 bytes (EEPROM 1k - 64 parameters)
#define ADDRESS_MAX 0x3BF
#define ADDRESS_BEG 0x000
#define ADDRESS_LAST (ADDRESS_MAX - ENTRY_SIZE_LINEAR_LOGS)
#define SECTOR_SIZE 0x3C0
#define NB_ENTRIES_PER_SECTOR (SECTOR_SIZE / ENTRY_SIZE_LINEAR_LOGS)
#define ADDRESS_SIZE (ADDRESS_MAX - ADDRESS_BEG)
// The number of entires by types of logs (seconds, minutes, hours,
// commands/events)
#define MAX_NB_ENTRIES (ADDRESS_SIZE / ENTRY_SIZE_LINEAR_LOGS)

#define MAX_MULTI_LOG 64  // Allows to display long log on serial

unsigned long lastLog = millis();

volatile uint16_t nextEntryID = 0;
// Deactivate safeguard to store log into EEPROM
bool logActive = true;

int getFirstAddress(uint16_t entryID) {
  return FIRST_ADDRESS + LOG_ENTRY_LENGTH * (entryID % NUMBER_LOGS);
}

void writeLog() {
  int16_t firstAddress = getFirstAddress(nextEntryID);
  // Write entryID (add 4 bytes for compatibility with Hackuarium projects)
  eeprom_write_dword((uint32_t*)firstAddress, (uint32_t)nextEntryID);
  firstAddress += 4;
  // Write time
  uint32_t timenow = now();
  eeprom_write_dword((uint32_t*)firstAddress, timenow);
  firstAddress += 4;
  for (uint8_t i = 0; i < NB_PARAMETERS_LINEAR_LOGS; i++) {
    eeprom_write_word((uint16_t*)(firstAddress + i * 2), getParameter(i));
  }
  ++nextEntryID;
}

/******************************************************************************
  Returns the address corresponding to one log ID nilThdSleepMilliseconds(5);
nilThdSleepMilliseconds(5); entryNb:     Log ID return:      Address of the
first byte where the corresponding log is located
*******************************************************************************/
uint32_t findAddressOfEntryN(uint32_t entryN) {
  uint32_t address =
      ((entryN % MAX_NB_ENTRIES) * ENTRY_SIZE_LINEAR_LOGS) % ADDRESS_SIZE +
      ADDRESS_BEG;
  return address;
}

void writeLog(uint16_t event_number, int parameter_value) {
  /********************************
             Safeguards
  ********************************/
  if (!logActive)
    return;
  /*****************************
            Slave Select
  ******************************/

  chSemWait(&lockTimeCriticalZone);

  uint16_t param = 0;
  uint32_t timenow = now();
  uint32_t startAddress = getFirstAddress(nextEntryID);

  /*****************************
          Writing Sequence
  ******************************/
  // Write entryID (add 4 bytes for compatibility with Hackuarium projects)
  eeprom_write_dword((uint32_t*)startAddress, (uint32_t)nextEntryID);
  startAddress += 4;
  // Write time
  eeprom_write_dword((uint32_t*)startAddress, timenow);
  startAddress += 4;
  for (uint8_t i = 0; i < NB_PARAMETERS_LINEAR_LOGS; i++) {
    eeprom_write_word((uint16_t*)(startAddress + i * 2), getParameter(i));
  }
  startAddress += (NB_PARAMETERS_LINEAR_LOGS * 2);
  eeprom_write_word((uint16_t*)startAddress, event_number);
  startAddress += 2;
  eeprom_write_word((uint16_t*)startAddress, parameter_value);

  /*****************************
          Check saved information
          We assume that the logger is high priority
          And no other thread will change any of the values !!!!!!
  ******************************/
  bool isLogValid = true;
  startAddress = getFirstAddress(nextEntryID);
  // sst.flashReadInit(findAddressOfEntryN(nextEntryID));
  if (eeprom_read_word((const uint16_t *)startAddress) != nextEntryID) {
    isLogValid = false;
  }
  startAddress += 4;
  if (eeprom_read_dword((const uint32_t *)startAddress) != timenow) {
    isLogValid = false;
  }
  startAddress += 4;
  for (uint8_t i = 0; i < NB_PARAMETERS_LINEAR_LOGS; i++) {
    if (eeprom_read_word((const uint16_t *)(startAddress + i*2)) != getParameter(i))
      isLogValid = false;
  }
  startAddress += (NB_PARAMETERS_LINEAR_LOGS * 2);
  if (eeprom_read_word((const uint16_t *)startAddress) != event_number) {
    isLogValid = false;
  }
  startAddress += 4;
  if (eeprom_read_word((const uint16_t *)startAddress) != parameter_value) {
    isLogValid = false;
  }

  if (isLogValid) {
    // Update the value of the next event log position in the memory
    nextEntryID++;
  } else {
    Serial.print(F("Log fail "));
    Serial.println(nextEntryID);
    // if logger fails it is better to go back and erase the full sector
    // we can anyway not try to write if it was not erased !
    // and if we don't do this ... we will destroy the memory !
    nextEntryID -= nextEntryID % NB_ENTRIES_PER_SECTOR;
  }

  /*****************************
         Out and Deselect
  ******************************/
  chSemSignal(&lockTimeCriticalZone);
  chThdSleep(5);
}

void loggerInit() {
  // we need to reload the last ID
  for (uint8_t i = 0; i < NUMBER_LOGS; i++) {
    uint16_t entryID = eeprom_read_word((uint16_t*)(getFirstAddress(i)));
    if (entryID > nextEntryID && entryID < 65535) {
      nextEntryID = entryID;
    }
  }
  nextEntryID++;
}

int16_t getParameterFromLog(uint16_t entryID, byte parameter) {
  int address = getFirstAddress(entryID) + 4 + parameter * 2;
  return eeprom_read_word((uint16_t*)(address));
}

void readLog(uint16_t entryID) {
  int firstAddress = getFirstAddress(entryID) + 4;
  for (byte i = 0; i < NB_PARAMETERS_LINEAR_LOGS; i++) {
    setParameter(i, eeprom_read_word((uint16_t*)(firstAddress + i * 2)));
  }
}

void formatLog() {
  for (int i = FIRST_ADDRESS; i <= LAST_ADDRESS; i++) {
    eeprom_write_byte((uint8_t*)i, 0xFFFF);
  }
  nextEntryID = 0;
  writeLog();
}

uint16_t getFirstLogEntryID() {
  return NUMBER_LOGS > nextEntryID ? 0 : nextEntryID - NUMBER_LOGS;
}

uint16_t getNextLogEntryID() {
  return nextEntryID;
}

void printLog(Print* output) {
  int16_t first = getFirstLogEntryID();
  for (int16_t i = first; i < nextEntryID; i++) {
    int firstAddress = getFirstAddress(i);
    output->print(eeprom_read_word((uint16_t*)(firstAddress)));
    output->print(" ");
    firstAddress += 2;
    output->print(eeprom_read_word((uint16_t*)(firstAddress)));
    firstAddress += 2;
    for (byte j = 0; j < NB_PARAMETERS_LINEAR_LOGS; j++) {
      output->print(" ");
      output->print((int)eeprom_read_word((uint16_t*)(firstAddress + j * 2)));
    }
    output->println("");
  }
}

void printLoggerHelp(Print* output) {
  output->println(F("Logger help"));
  output->println(F("(ld) Dump"));
  output->println(F("(lf) Format"));
  output->println(F("(lw) Write log"));
}

void processLoggerCommand(char command, char* data, Print* output) {
  switch (command) {
    case 'd':
      printLog(output);
      break;
    case 'f':
      if (data[0] == '\0' || atoi(data) != 1234) {
        output->println(F("Format enter lf1234"));
      } else {
        output->println(F("Formatting"));
        formatLog();
        output->println("Done");
      }
      break;
    case 'l':
      break;
    case 'm':
      break;
    case 'w':
      writeLog();
      output->println(F("Log written"));
      break;
    default:
      printLoggerHelp(output);
  }
}



/* The qualifier represents the card ID and is stored just after the last
 * parameter */
uint16_t getQualifier() {
  return eeprom_read_word((uint16_t*)(EE_QUALIFIER));
}

void setQualifier(uint16_t value) {
  eeprom_write_word((uint16_t*)(EE_QUALIFIER), value);
}

void setDataLong(int index, long value) {
  eeprom_write_dword((uint32_t*)(EEPROM_MAX_ADDR - 4 * index - 3), value);
}

long getDataLong(int index) {
  return eeprom_read_dword((uint32_t*)(EEPROM_MAX_ADDR - 4 * index - 3));
}

// code from http://www.arduino.cc/playground/Code/EepromUtil
void getStatusEEPROM(Print* output) {
  int bytesPerRow = 16;
  int i;
  int j;
  byte b;
  char buf[4];

  j = 0;

  // go from first to last eeprom address
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    if (j == 0) {
      sprintf(buf, "%03X", i);
      output->print(buf);
      output->print(F(": "));
    }

    // read current byte from eeprom
    b = eeprom_read_byte((uint8_t*)i);
    sprintf(buf, "%02X ", b);
    j++;
    if (j == bytesPerRow) {
      j = 0;
      output->println(buf);
      chThdSleep(25);
    } else {
      output->print(buf);
    }
  }
}
