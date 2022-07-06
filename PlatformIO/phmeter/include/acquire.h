#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

void calibrate(bool);
void testProbe();
void setActiveProbes();
void setAcquisitionMenu();
void waitExperiment();
void runExperiment(uint8_t);
void runExperiment();
void runSequence(uint8_t);
void calculateResult(uint8_t);
long acquireOne(uint8_t);
void acquire(bool);
void printColor(Print*, uint8_t);
void printColorOne(Print*, uint8_t);
void printData(Print*);
void clearData();