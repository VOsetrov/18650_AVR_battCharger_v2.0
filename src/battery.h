#ifndef BATTERY_H
#define BATTERY_H

#include "stdbool.h"
#include "lic_adc.h"

typedef enum {
  BATT1,
  BATT2,
} battID;

typedef enum {
  deviceID,
  voltage,
  capacitance,
  resistance,
} parameters;

#define MAX_PARAMS 4

typedef struct {
  battID id;
  uint16_t voltage;
  uint8_t capacitance;
  uint8_t resistance;
} battery;

#define MAX_BATTERIES 2
#define PACKET_SIZE sizeof(battery)

typedef struct {
  volatile battery* plist;
  battery list[MAX_BATTERIES];
} batlist;

void init_battData(batlist* batt);
battID returnBattID(adcchan channel);

#endif
