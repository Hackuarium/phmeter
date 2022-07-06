#include <ChNil.h>

#include "Funcs.h"
#include "acquire.h"

#define DATA_SIZE 240

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
