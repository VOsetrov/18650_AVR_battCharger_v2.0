#ifndef LIC_ADC_H
#define LIC_ADC_H

#include "lic328p_gpio.h"
#include "lic_adc.h"
#include "ATmega328p.h"
#include <stdint.h>


typedef volatile struct {
  enum adc_chan name;
  uint8_t mux;
} adcConfig;

#define MAX_ADC_CHANNELS 2

typedef volatile struct {
  adcConfig config[MAX_ADC_CHANNELS];
  adcConfig* currentChan;
} adcChannel; 

void adc_init();
void init_adcChan(adcChannel* chn);   // Init a struct adcChannel
enum adc_chan next_adcChannel
	(uint8_t size, enum adc_chan cname); 
uint8_t adc_switchChannel             // Init control of current ADC channel
  (adcChannel* channel);

#endif
