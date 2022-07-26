#include <Arduino.h>
#include <ChNil.h>

#include "Funcs.h"
#include "HackEEPROM.h"

#include "pH.h"
#include "eC.h"

int PROBES[TOTAL_NUMBER_PROBES];

long acquireOne(uint8_t probe) {
    volatile int rawMeasurement;
    switch (probe)
    {
    case 0: // pH reading
        rawMeasurement = getPH();
        // setPH(&rawMeasurement);
        break;
    case 1: // EC reading
        // rawMeasurement = getEC();
        // setEC(&rawMeasurement);
        break; 
    default:
        break;
    }
  return rawMeasurement;
}

void acquire(bool testMode) {
  if (!testMode) setParameter(PARAM_MENU, 32);
  byte target = getParameter(PARAM_NEXT_EXP) * dataRowSize;
  if (target < 0) return;

  setDataLong(target, millis());
  for (byte i = 0; i < nbParameters; i++) {
    long newValue = 0;
    if (ALL_PARAMETERS[ACTIVE_PARAMETERS[i]] < 128) {
      for (byte j = 0; j <  getParameter(PARAM_NUMBER_ACQ); j++) {
        long currentCount = acquireOne(ACTIVE_PARAMETERS[i]);
        newValue += currentCount;
        if (currentCount > 50000) {
          // there is an error, the frequency was too high for the detector
          // this means we should either work in a darker environnement (at least close the box)
          // or that the LED is too strong !
          setDataLong(target + i + 1, LONG_MAX_VALUE);
          break;
        }
        // FreqCount.begin(100);
        chThdSleepMilliseconds(105);
        // currentCount = FreqCount.read();
        if (currentCount > 10000) {
          // there is an error, the frequency was too high without led on
          // this means we should work in a darker environnement (at least close the box)
          setDataLong(target + i + 1, LONG_MAX_VALUE);
          break;
        }
        newValue -= currentCount;
        if (getParameter(PARAM_NEXT_EXP) < 0) return;
      }
    } else {
      switch (ALL_PARAMETERS[ACTIVE_PARAMETERS[i]]) {
        case BATTERY_LEVEL:
          newValue = getParameter(PARAM_BATTERY);
          break;
        case TEMP_EXT1:
          newValue = getParameter(PARAM_TEMP_EXT1);
          break;
        case TEMP_EXT2:
          newValue = getParameter(PARAM_TEMP_EXT2);
          break;
      }
    }
    setDataLong(target + i + 1, newValue);
  }
}

/**
 * The function calibrate() takes a boolean value as an argument. If the boolean
 * value is true, the function will calibrate the pH probe. If the boolean 
 * value is false, the function will calibrate the EC probe.
 * 
 * @param probePH true if calibrating the pH probe, false if calibrating the EC
 * probe
 */
void calibrate(bool probePH) {
  int lowPHNeutral = 0;
  int highPHNeutral = 4091;
  int lowECWater = 0;
  int highECWater = 4091;
  if (probePH)
  {
    while ((highPHNeutral - lowPHNeutral) >= 2) {
      PROBES[0] = (lowPHNeutral + highPHNeutral) / 2;
      long one = acquireOne(0);
      if (one > TARGET_INTENSITY_PH) {
        highPHNeutral = PROBES[0];
      } else {
        lowPHNeutral = PROBES[0];
      }
    }
  }
  else
  {
    while ((highECWater - lowECWater) >= 2) {
      PROBES[0] = (lowECWater + highECWater) / 2;
      long one = acquireOne(1);
      if (one > TARGET_INTENSITY_EC) {
        highECWater = PROBES[1];
      } else {
        lowECWater = PROBES[1];
      }
    }
  }
  
}

/**
 * It reads the pH, EC, and temperature sensors, and prints the results to the
 * serial port
 * 
 * @return The pH, EC, and temperature of the probes.
 */
void testProbe() {
#if VERSION>=5
  calibrate();
#endif
  while (true) {
    setParameter(PARAM_NEXT_EXP, 0);
    // acquire(true);

    int16_t pH = getPH();
    setPH(&pH);

    int16_t eC = getEC();
    setEC(&eC);

    Serial.print(getParameter(PARAM_PH));
    Serial.print(",");
    Serial.print(getParameter(PARAM_EC));
    Serial.print(",");
    Serial.print(getParameter(PARAM_TEMP_EXT1));
    Serial.print(",");
    Serial.print(getParameter(PARAM_TEMP_EXT2));
    Serial.print(",");
    // Serial.print(getParameter(PARAM_BATTERY));
    // Serial.print(" ");
    Serial.println("");

    if (getParameter(PARAM_STATUS) != STATUS_TEST_PROBES) {
      return;
    }
    chThdSleepSeconds(1);
  }
}

/**
 * It takes a bitmask of active probes and sets the number of active probes, the
 * number of active parameters, the number of LEDs, the size of a data row, and the
 * maximum number of rows in the data buffer
 */
void setActiveProbes() {
  int active = getParameter(PARAM_ACTIVE_PROBES);
  nbProbes = 0;
  nbParameters = 0;
  for (byte i = 0; i < sizeof(ALL_PARAMETERS); i++) {
    if (active & (1 << i)) {
      ACTIVE_PARAMETERS[nbParameters] = i;
      if (ALL_PARAMETERS[i] < 128) {
        (nbProbes)++;
      }
      (nbParameters)++;
    }
  }
  dataRowSize = (nbParameters) + 1;
  maxNbRows = DATA_SIZE / dataRowSize;
}


void setAcquisitionMenu() {
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    setParameter(PARAM_MENU, 30);
  } else {
    setParameter(PARAM_MENU, 31);
  }
}

void waitExperiment() {
  long wait = 0;
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    wait = getParameter(PARAM_BEFORE_DELAY);
  } else if (getParameter(PARAM_NEXT_EXP) == 1) {
    wait = getParameter(PARAM_FIRST_DELAY);
  } else if (getParameter(PARAM_NEXT_EXP) > 1) {
    wait = getParameter(PARAM_INTER_DELAY);
  }

  long timeEnd = millis() + wait * 1000;
  while (millis() < timeEnd && getParameter(PARAM_NEXT_EXP) >= 0) {
    setParameter(PARAM_WAIT, (timeEnd - millis()) / 1000);
    chThdSleepMilliseconds(1000);
  }
}


void clearData() {
  for (byte i = 0; i < DATA_SIZE; i++) {
    if (getDataLong(i) != 0) {
      setDataLong(i, 0);
    }
  }
}

// Check with HackEEPROM - 20220706
void calculateResult(uint8_t experimentNumber) {
  // we calculate the difference with blank
  for (byte i = 0; i < nbProbes; i++) {
    if (getDataLong(experimentNumber * dataRowSize + i + 1) == LONG_MAX_VALUE) {
      setParameter(i, INT_MAX_VALUE); // current experiment
    } else {
      setParameter(i, getDataLong(experimentNumber * dataRowSize + i + 1) / 16); // current experiment
    }
    if (getDataLong(i + 1) == LONG_MAX_VALUE) {
      setParameter(i + 5, INT_MAX_VALUE); // blank saturation
    } else {
      setParameter(i + 5, getDataLong(i + 1) / 16); // blank value
    }
  }
}


void runExperiment(uint8_t nbExperiments) {
#if VERSION>=5
  calibrate();
#endif
  for (byte i = 0; i <= nbExperiments; i++) {
    setParameter(PARAM_NEXT_EXP, i);
    setAcquisitionMenu();
    waitExperiment();
    if (i == 0) {
      clearData();
    }
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    acquire(false);
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    if (i > 0) calculateResult(i);
  }
  setParameter(PARAM_MENU, 20);// status menu
  setParameter(PARAM_STATUS, 0);
  setParameter(PARAM_NEXT_EXP, -1);
}

void runExperiment() {
  runExperiment(1);
}

void runSequence(uint8_t nbExperiments) { // TODO update this code
#if VERSION>=5
  calibrate();
#endif
  for (byte i = 0; i <= nbExperiments; i++) {
    setParameter(PARAM_NEXT_EXP, i);
    setAcquisitionMenu();
    setParameter(PARAM_WAIT, INT_MAX_VALUE);
    // Need to wait for a validation
    while (getParameter(PARAM_WAIT) != 0 && getParameter(PARAM_NEXT_EXP) >= 0) {
      chThdSleepMilliseconds(100);
    }
    if (i == 0) {
      clearData();
    }
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    acquire(false);
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    if (i > 0) calculateResult(i);
  }
  setParameter(PARAM_MENU, 20); // status menu
  setParameter(PARAM_STATUS, 0);
  setParameter(PARAM_NEXT_EXP, -1);
}


/******************************
  Copy from UtilitiesSpecific
*******************************/
void printColor(Print* output, uint8_t parameter) {
  switch (parameter) {
    case 0:
      output->print(F("pH"));
      break;
    case 1:
      output->print(F("EC"));
      break;
    case 2:
      output->print(F("Temp. 1"));
      break;
    case 3:
      output->print(F("Temp. 1"));
      break;
    case 4:
      output->print(F("Battery level"));
      break;
  }
}

void printColorOne(Print* output, uint8_t parameter) {
  switch (parameter) {
    case 0:
      output->print("pH");
      break;
    case 1:
      output->print("EC");
      break;
    case 2:
      output->print("T 1");
      break;
    case 3:
      output->print("T 2");
      break;
    case 4:
      output->print("BAT");
      break;
    case 5:
      output->print("");
      break;
  }
}

void printData(Print* output) {
  output->print("E ");
  for (byte i = 0; i < nbParameters; i++) {
    printColorOne(output, ACTIVE_PARAMETERS[i]);
    output->print(" ");
  }
  output->println("");
  for (byte i = 0; i < maxNbRows; i++) {
    for (byte j = 0; j < dataRowSize; j++) {
      if (getDataLong(i * dataRowSize + j) == LONG_MAX_VALUE) {
        output->print("OVER");
      } else {
        output->print(getDataLong(i * dataRowSize + j));
      }
      output->print(" ");
    }
    output->println("");
  }
}
