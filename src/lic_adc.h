#ifndef LIC_ADC_H
#define LIC_ADC_H

#include "lic328p_gpio.h"
#include "lic_adc.h"
#include <stdint.h>

typedef struct {
  adcchan name;
  uint8_t mux;
} adcConfig;

typedef struct {
  adcConfig* currentChan;
  adcConfig config[];
} adcChannel; 

adcChannel channel;

void adc_init();
uint16_t adc();                       // Returns the ADC data register value
void adc_setMux(uint8_t muxset);      // Init a selected ADC channel
uint8_t adc_switchChannel             // Init control of current ADC channel
  (adcChannel* channel);

#endif
