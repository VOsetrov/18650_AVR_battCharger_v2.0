#include "battery.h"

battID returnBattID(adcchan channel) {
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

