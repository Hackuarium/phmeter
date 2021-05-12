#include <Arduino.h>

uint16_t getQualifier();

void setQualifier(uint16_t value);

void setDataLong(int index, long value);

long getDataLong(int index);

// code from http://www.arduino.cc/playground/Code/EepromUtil
void getStatusEEPROM(Print* output);