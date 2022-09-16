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
        // Check this code, calibration pH & EC, reading pH & EC
        case FLAG_EC_READING:
          runExperiment(numberExperiments);
          break;
        case FLAG_EC_CALIBRATION:
          calibrate(0);
          break;
        case FLAG_PH_CONTROL:
          runExperiment(numberExperiments);
          break;
        case FLAG_PH_CALIBRATE:
          calibrate(1);
          break;
        case STATUS_SEQUENCE:
          runSequence(numberExperiments);
          break;
      }
    }
    if (getParameter(PARAM_STATUS) == STATUS_TEST_PROBES) {
      testProbe();
    }
    chThdSleepMilliseconds(100);
  }
}
