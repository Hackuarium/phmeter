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

  long pH = 0;

  static bool check = TRUE;

  pHADC.begin(PH_DATA, PH_CLK, 32);
  pHADC.set_gain(32);

  // Set scale and tare for first reading
  if(check) {
    pHADC.set_scale();
    pHADC.tare(); //Reset the scale to 0
    check = FALSE;
  }

  /**
   * @brief Using oversampling to reduce noise and increase resolution:
   * f_oversampling = 4^n * f_sampling; n: number of bits to increase resolution
   * f_sampling >= 2 * f_signal; in this case:
   * f_sampling = 2 * f_signal = f_nyquist. PH is similar to DC signal, so:
   * f_sampling = f_ADC = 80 SPS (10 SPS).
   * Choose 10 SPS we reduce signal noise directly from the ADC.
   * After adquire samples, we need to right shift the register in n times.
   */

  long readingPH = 0;
  // Define oversampling
  uint8_t times_oversampling = 16;  // times_oversampling = 4^2
  do
  {
    chSemWait(&lockADCReading);
		readingPH = pHADC.read();
    chSemSignal(&lockADCReading);
    if ((readingPH & 0xFF) == 1)
    {
      // There is a problem with the reading pH
      saveAndLogError(true, FLAG_PH_RANGE_ERROR);
      return ERROR_VALUE;
    }
    pH += readingPH;
    
  } while (--times_oversampling);
  // Right shift n times
  pH >>= 2;

  // Remove flag for pH error   
  saveAndLogError(false, FLAG_PH_RANGE_ERROR);
  return (pH >> 8) & 0x0000FFFF;
}

void setPH(int16_t *pPHRaw) {
    setParameter(PARAM_PH, *pPHRaw);
    // setParameter(PARAM_PH_H, convertPHToH(pHRaw));
}

#endif