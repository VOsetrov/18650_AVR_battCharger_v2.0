#ifndef LIC_18650H_H
#define LIC_18650_H

typedef enum {
  BATT1,
  BATT2,
} lion;

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

void voltageHandling(lion battnum);

#endif
