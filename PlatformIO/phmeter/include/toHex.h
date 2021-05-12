#include "Arduino.h"

/* Functions to convert a number to hexadecimal */

//const char hex[] = "0123456789ABCDEF";

uint8_t toHex(Print* output, byte value);

uint8_t toHex(Print* output, int value);

uint8_t toHex(Print* output, long value);