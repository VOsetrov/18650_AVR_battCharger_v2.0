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

void resetTransmitStatus
    (battTxStatus* structure) {

  for(uint8_t i = 1; i <= MAX_PARAMS; i++) {
    structure->fieldsstatus[i].status =
      false;
  };

  structure->currentstatus =
    &structure->fieldsstatus[0];
}

battID updateBatteryTransmitStatus
    (batlist* structure) {
  battID name = structure->currbat->id;

  if(name == BATT1) {
    return BATT2;
  } else return BATT1;
}

bool checkTransmit(battTxStatus* structure) {
  for(uint8_t i = MAX_PARAMS - 1; i >= 0; i--) {
    if(!(structure->fieldsstatus[i].status)) {
      return false;
    };
  };
  return true;
}

