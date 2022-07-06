#include <ChNil.h>

#include "Funcs.h"
#include "acquire.h"

#define DATA_SIZE 240

extern uint8_t nbParameters;        // number of parameters to record
extern uint8_t dataRowSize;         // size of a data row (number of entries in data)
extern uint8_t maxNbRows;           // calculate value depending the size of EEPROM dedicated to logs

THD_FUNCTION(ThreadAcquisition, arg) {
  setParameter(PARAM_NEXT_EXP, -1);
  while (true) {
    if (getParameter(PARAM_NEXT_EXP) == 0) {
      setActiveProbes();
      uint8_t numberExperiments = min(maxNbRows, getParameter(PARAM_NUMPER_EXP));
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
      testProbe();
    }
    chThdSleepMilliseconds(100);
  }
}
