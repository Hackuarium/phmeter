#include <ChNil.h>

#include "Funcs.h"
#include "HX711.h"
#include "Sem.h"

HX711 pHADC;

int pH;

int16_t getPH() { // we can not avoid to have some errors measuring the pH
  // and currently we don't know where it is coming from
  // so we need to find out what are the correct values and what are the wrong one
  // if there is an error it always end with 00000001
  // we will also need 4 consecutive values that differ less than 10%
  byte counter = 0;
  long weight = 0;

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
    long currentWeight = pHADC.read();
    chSemSignal(&lockADCReading);

    if ((currentWeight & 0b11111111) != 1) {
      if (weight == 0) {
        weight += currentWeight;
        counter++;
      } else {
        int difference = abs(100 - (weight * 100 / counter) / currentWeight);
        if (difference < 10) {
          weight += currentWeight;
          counter++;
        } else {
          weight = 0;
          counter = 0;
        }
      }
      chThdSleepMilliseconds(10);
    }
  }
  return weight / counter / 100;
}

void setPH(uint16_t *pPHRaw) {
    // setParameter(PARAM_PH, *pHRaw);
    // setParameter(PARAM_PH_H, convertPHToH(pHRaw));
}




