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

void updateTransmitStatus
    (battTxStatus* structure) {
  int i;

  for(i = 1; i <= MAX_PARAMS; i++) {
    structure->fieldsstatus[i].status =
      false;
  };

  structure->currentstatus++;

  if(structure->currentstatus >= &structure->
      fieldsstatus[MAX_PARAMS]) {
    structure->currentstatus = 
      &structure->fieldsstatus[0];
  };
}

bool checkTransmit(battTxStatus* structure) {
  int i;
  for(i = MAX_PARAMS - 1; i >= 0; i--) {
    if(!(structure->fieldsstatus[i].status)) {
      return false;
    };
  };
  return true;
}
