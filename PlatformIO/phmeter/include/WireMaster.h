// setting ATmega32U4 as I2C slave.

#ifdef THR_WIRE_MASTER

#define WIRE_MAX_DEVICES 8

extern byte numberI2CDevices;
extern byte wireDeviceID[WIRE_MAX_DEVICES];

int wireReadInt(uint8_t address);
void wireWakeup(uint8_t address);
void wireSetRegister(uint8_t address, uint8_t registerAddress);
int wireReadIntRegister(uint8_t address, uint8_t registerAddress);
int wireCopyParameter(uint8_t address, uint8_t registerAddress,
  uint8_t parameterID);
void wireWriteIntRegister(uint8_t address, uint8_t registerAddress, 
  int value);
void printWireInfo(Print *output);
void printWireDeviceParameter(Print *output, uint8_t wireID);
void wireRemoveDevice(byte id);
void wireInsertDevice(byte id, byte newDevice);
boolean wireDeviceExists(byte id);
//void wireUpdateList();
void wireUpdateList(Print* output);
void printWireHelp(Print *output);
void processWireCommand(char command, char *paramValue,
  Print *output);

#ifndef THR_WIRE_M
NIL_WORKING_AREA(waThreadWireMaster, 200);
NIL_THREAD(ThreadWireMaster, arg);
#endif

#endif
