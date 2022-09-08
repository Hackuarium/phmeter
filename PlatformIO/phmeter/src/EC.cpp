#include <ChNil.h>

#include "Funcs.h"
#include "Sem.h"

#ifdef THR_ACQUIRE

CH_NIL_ADC_IRQ

int16_t getEC() {
  // Define counter for oversampling
  uint8_t counter = 0;

  int16_t eC = 0;
  uint8_t op = 10;

  while (counter < 4) {
    // wait for slot
    int16_t readingEC = chAnalogRead(5);

    if (op > 0) {
      if (eC == 0) {
        eC += readingEC;
        counter++;
      } else {
        int difference = abs(100L - ((long)eC * 100L / (long)counter) / (long)readingEC);
        if (difference < 10) {
          eC += readingEC;
          counter++;
        } else {
          eC = 0;
          counter = 0;
          --op;
          chThdSleepSeconds(1);
        }
      }
      chThdSleepMilliseconds(10);
    }
    else
    {
      saveAndLogError(true, FLAG_EC_RANGE_ERROR);
      return ERROR_VALUE;
    }
  }
  saveAndLogError(false, FLAG_EC_RANGE_ERROR);
  return static_cast<int16_t>(eC >> 2);
  // return (eC >> 2);
}

void setEC(volatile int16_t *pPHRaw) {
    setParameter(PARAM_EC, *pPHRaw);
    // setParameter(PARAM_PH_H, convertPHToH(pHRaw));
}

#endif