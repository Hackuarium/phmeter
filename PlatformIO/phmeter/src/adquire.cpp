#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#include "libino/FreqCount/FreqCount.cpp"

// Check - 20220705
#define TARGET_INTENSITY_PH 45000
#define TARGET_INTENSITY_EC 45000
int PROBES[TOTAL_NUMBER_PROBES];
void calibrate() {
  for (byte i = 0; i < 2; i++) {
    int lowIntensity = 0;
    int highIntensity = 4091;
    while ((highIntensity - lowIntensity) >= 2) {
      PROBES[i] = (lowIntensity + highIntensity) / 2;
      long one = acquireOne(i);
      if (one > TARGET_INTENSITY) {
        highIntensity = PROBES[i];
      } else {
        lowIntensity = PROBES[i];
      }
    }
  }
}

void testRGB() {
#if VERSION>=5
  calibrate();
#endif
  while (true) {
    setParameter(PARAM_NEXT_EXP, 0);
    acquire(true);

    for (byte i = 1; i < 5; i++) {
      Serial.print(getDataLong(i));
      Serial.print(" ");
    }
    Serial.println("");

    if (getParameter(PARAM_STATUS) != STATUS_TEST_LEDS) {
      return;
    }
  }
}

void setActiveLeds() {
  int active = getParameter(PARAM_ACTIVE_LEDS);
  nbLeds = 0;
  nbParameters = 0;
  for (byte i = 0; i < sizeof(ALL_PARAMETERS); i++) {
    if (active & (1 << i)) {
      ACTIVE_PARAMETERS[nbParameters] = i;
      if (ALL_PARAMETERS[i] < 128) {
        nbLeds++;
      }
      nbParameters++;
    }
  }
  dataRowSize = nbParameters + 1;
  maxNbRows = DATA_SIZE / dataRowSize;
}

THD_FUNCTION(ThreadAcquisition, arg) {
  setParameter(PARAM_NEXT_EXP, -1);
  while (true) {
    if (getParameter(PARAM_NEXT_EXP) == 0) {
      setActiveLeds();
      byte numberExperiments = min(maxNbRows, getParameter(PARAM_NUMPER_EXP));
      switch (getParameter(PARAM_STATUS)) {
        case STATUS_ONE_SPECTRUM:
          runExperiment();
          break;
        case STATUS_KINETIC:
          runExperiment(numberExperiments);
          break;
        case STATUS_SEQUENCE:
          runSequence(numberExperiments);
          break;
      }
    }
    if (getParameter(PARAM_STATUS) == STATUS_TEST_LEDS) {
      testRGB();
    }
    chThdSleepMilliseconds(100);
  }
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

void runExperiment() {
  runExperiment(1);
}

void runExperiment(byte nbExperiments) {
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

void runSequence(byte nbExperiments) { // TODO update this code
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

void calculateResult(byte experimentNumber) {
  // we calculate the difference with blank
  for (byte i = 0; i < nbLeds; i++) {
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

long acquireOne(byte led) {

  chThdSleepMilliseconds(5);
  FreqCount.begin(100);
  chThdSleepMilliseconds(105);
  long count = FreqCount.read();
  ledOff(led);

  return count;
}

void acquire(boolean testMode) {
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
        FreqCount.begin(100);
        nilThdSleepMilliseconds(105);
        currentCount = FreqCount.read();
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
        case TEMPERATURE:
          newValue = getParameter(PARAM_TEMPERATURE);
          break;
      }
    }
    setDataLong(target + i + 1, newValue);
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

void clearData() {
  for (byte i = 0; i < DATA_SIZE; i++) {
    if (getDataLong(i) != 0) {
      setDataLong(i, 0);
    }
  }
}