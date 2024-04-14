#ifndef LIC_18650H_H
#define LIC_18650_H

#include <stdbool.h>
#include "lic_adc.h"

typedef enum {
  BATT1,
  BATT2,
} lion;

typedef enum {
  battname,
  voltage,
  capacitance,
  resistance,
} parameters;

#define MAX_PARAMS 4

typedef struct {
  lion batnum;
  uint16_t voltage;
  uint8_t capacitance;
  uint8_t resistance;
} battery;

#define MAX_BATTERIES 2

typedef struct {
  volatile battery* currbat;
  battery list[MAX_BATTERIES];
} batlist;

typedef struct {
  parameters field;
  bool status;
} fieldTxStatus;

typedef struct {
  bool sendstatus;
  fieldTxStatus* currentstatus;
  fieldTxStatus fieldsstatus[MAX_PARAMS];
} battTxStatus;

void voltageHandling(uint16_t adcData, 
    batlist* batstat, adcchan channel);
void updateTransmitStatus
    (battTxStatus* structure);
void updateBatteryStatus(batlist* structure);
bool checkTransmit(battTxStatus* structure);    // Check transfer status, if it
                                                // complete return true.
#endif
