#include <Arduino.h>
#include <ChNil.h>

extern unsigned long lastLog;

int getFirstAddress(uint16_t);
void writeLog();
/***********************************************************************************
  Save logs in the Flash memory.
  event_number: If there is a command, then this parameter should be set with
the corresponding command/event number. Should be found in the define list of
  commands/errors
************************************************************************************/
void writeLog(uint16_t, int);

void loggerInit();
int16_t getParameterFromLog(uint16_t, byte);
void readLog(uint16_t);
void formatLog();
uint16_t getFirstLogEntryID();
uint16_t getNextLogEntryID();
void printLog(Print*);
void printLoggerHelp(Print*);
void processLoggerCommand(char, char*, Print*);



void setQualifier(uint16_t);
void setDataLong(int, long);
void getStatusEEPROM(Print*);

uint16_t getQualifier();

long getDataLong(int);