#ifndef LIC_18650H_H
#define LIC_18650_H

typedef enum {
  BATT1,
  BATT2,
} lion;

typedef struct {
  lion batnum;
  uint8_t voltage;
  uint8_t capacitance;
  uint8_t resistance;
} battery;

typedef struct {
  battery* currbat;
  battery list[];
} batlist;

void voltageHandling(lion battnum);

#endif
