#ifndef LIC_18650H_H
#define LIC_18650_H

#include <stdbool.h>
#include "lic_adc.h"
#include "battery.h"

typedef struct {
  parameters field;
  bool status;
} fieldTxStatus;

typedef struct {
  fieldTxStatus* currentstatus;
  fieldTxStatus fieldsstatus[MAX_PARAMS];
} battTxStatus;

void voltageHandling(uint16_t adcData, 
    batlist* batstat, adcchan channel);
void resetTransmitStatus
    (battTxStatus* structure);                  // Init the transmit status of 
                                                // all fields to false.
battID updateBatteryTransmitStatus
    (batlist* structure);                       // Returns the name of the next
                                                // battery for data transmition.
bool checkTransmit(battTxStatus* structure);    // Check transfer status, if
                                                // completed return true.

#endif
