#ifndef LIC_18650H_H
#define LIC_18650_H

#include <stdbool.h>
#include "lic_adc.h"
#include "battery.h"


void voltageHandling(uint16_t adcData, 
    batlist* batstat, adcchan channel);

#endif
