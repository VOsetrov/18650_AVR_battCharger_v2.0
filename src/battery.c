#include "battery.h"

void init_battData(batlist* batt) {
  batt->list[0] = (battery) {
    .id = BATT1,
    .voltage      = 0,
    .capacitance  = 0,
    .resistance   = 0,
  };
  batt->list[1] = (battery) {
    .id = BATT2,
    .voltage      = 0,
    .capacitance  = 0,
    .resistance   = 0,
  };
  batt->plist = &batt->list[0];
}

battID returnBattID
	(enum adc_chan channel) {

  battID id = 0;
  switch(channel) {
    case ADC0:
      id = BATT1;
      break;
    case ADC1:
      id = BATT2;
      break;
    default:
      break;
  };
  return id;
}

