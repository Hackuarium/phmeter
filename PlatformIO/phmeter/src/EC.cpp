#include <ChNil.h>

#include "Funcs.h"
#include "Sem.h"

#ifdef THR_ACQUIRE

int16_t getEC() { // we can not avoid to have some errors measuring the eC
  // and currently we don't know where it is coming from
  // so we need to find out what are the correct values and what are the wrong one
  // if there is an error it always end with 00000001
  // we will also need 4 consecutive values that differ less than 10%
  uint8_t counter = 0;

  uint8_t op = 10;
  long eC = 0;

  while (counter < 4) {
    // wait for slot
    long readingEC = 0;
    chSemWait(&lockADCReading);
    // long readingEC = pHADC.read();
    chSemSignal(&lockADCReading);
    
    // int16_t currentpH = (static_cast<long>(readingEC) >> 8) & 0x0000FFFF;

    // if ((readingEC & 0xFF) != 1) {
    if (op > 0) {
    // if (op > 0) {
      if (eC == 0) {
        eC += readingEC;
        counter++;
      } else {
        int difference = abs(100L - (eC * 100L / (long)counter) / readingEC);
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
  return eC;
  // return (eC >> 2);
  // return (eC / (long)counter) >> 6;
  // return eC / (long)counter / 100;
}

void setEC(int16_t *pPHRaw) {
    setParameter(PARAM_EC, *pPHRaw);
    // setParameter(PARAM_PH_H, convertPHToH(pHRaw));
}

#endif