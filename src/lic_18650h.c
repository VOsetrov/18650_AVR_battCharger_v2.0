#include <avr/io.h>
#include "lic_18650h.h"

void voltageHandling(uint16_t adcData,
    batlist* batstat, adcchan channel) {

  switch(channel) {
    case ADC0:
      batstat->list[BATT1].voltage = 
        adcData;
      break;
    case ADC1:
      batstat->list[BATT2].voltage =
        adcData;
      break;
    default:
      break;
  }
}
