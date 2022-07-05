#include <ChNil.h>

#include "Params.h"
#include "HX711.h"
#include "Sem.h"

HX711 pHADC;

int pH;

// wait for slot
chSemWait(&lockADCReading);

pHADC.begin(PH_DATA, PH_CLK, 32);
pHADC.set_gain(32);
pHADC.set_scale();
pHADC.tare(); //Reset the scale to 0

int16_t getPH() { // we can not avoid to have some errors measuring the weight
  // and currently we don't know where it is coming from
  // so we need to find out what are the correct values and what are the wrong one
  // if there is an error it always end with 00000001
  // we will also need 4 consecutive values that differ less than 10%
  byte counter = 0;
  long weight = 0;
  while (counter < 4) {
    while (!scale.is_ready()) {
      nilThdSleepMilliseconds(10);
    }
    nilSemWait(&lockTimeCriticalZone);
    long currentWeight = scale.read();
    nilSemSignal(&lockTimeCriticalZone);

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
      nilThdSleepMilliseconds(10);
    }
  }
  return weight / counter / 100;
}

void setPH(uint16_t *pPHRaw) {
    setParameter(PARAM_PH, &pHRaw);
    setParameter(PARAM_PH_H, convertPHToH(pHRaw));
}




