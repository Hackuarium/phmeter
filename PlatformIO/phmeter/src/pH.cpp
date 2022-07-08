#include <ChNil.h>

#include "Funcs.h"

#ifdef THR_ACQUIRE

#include "HX711.h"
#include "Sem.h"

HX711 pHADC;

int16_t getPH() { // we can not avoid to have some errors measuring the pH
  // and currently we don't know where it is coming from
  // so we need to find out what are the correct values and what are the wrong one
  // if there is an error it always end with 00000001
  // we will also need 4 consecutive values that differ less than 10%
  uint8_t counter = 0;

  uint8_t op = 10;
  long pH = 0;

  pHADC.begin(PH_DATA, PH_CLK, 32);
  pHADC.set_gain(32);
  pHADC.set_scale();
  pHADC.tare(); //Reset the scale to 0

  while (counter < 4) {
    while (!pHADC.is_ready()) {
      chThdSleepMilliseconds(10);
    }
    // wait for slot
    chSemWait(&lockADCReading);
    long readingPH = pHADC.read();
    chSemSignal(&lockADCReading);
    
    // int16_t currentpH = (static_cast<long>(readingPH) >> 8) & 0x0000FFFF;

    // if ((readingPH & 0xFF) != 1) {
    if (((readingPH & 0xFF) != 1) && (op > 0)) {
    // if (op > 0) {
      if (pH == 0) {
        pH += readingPH;
        counter++;
      } else {
        int difference = abs(100L - (pH * 100L / (long)counter) / readingPH);
        if (difference < 10) {
          pH += readingPH;
          counter++;
        } else {
          pH = 0;
          counter = 0;
          --op;
          chThdSleepSeconds(1);
        }
      }
      chThdSleepMilliseconds(10);
    }
    else
    {
      saveAndLogError(true, FLAG_PH_RANGE_ERROR);
      return ERROR_VALUE;
    }
  }
  saveAndLogError(false, FLAG_PH_RANGE_ERROR);
  return (pH >> 8) & 0x0000FFFF;
  // return (pH >> 2);
  // return (pH / (long)counter) >> 6;
  // return pH / (long)counter / 100;
}

void setPH(int16_t *pPHRaw) {
    setParameter(PARAM_PH, *pPHRaw);
    // setParameter(PARAM_PH_H, convertPHToH(pHRaw));
}

#endif