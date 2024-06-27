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

typedef volatile struct {
  battID id;
  uint16_t voltage;
  uint8_t capacitance;
  uint8_t resistance;
} battery;

#define MAX_BATTERIES 1
#define PACKET_SIZE sizeof(battery)

typedef volatile struct {
  battery list[MAX_BATTERIES];
  battery* plist;
} batlist;

void init_battData(batlist* batt);
battID returnBattID
	(enum adc_chan channel);
void batt_data_handling
	(uint16_t data, batlist *plist);

#endif
