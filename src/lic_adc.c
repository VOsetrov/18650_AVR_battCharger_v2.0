#include <avr/io.h>
#include <stdint.h>
#include "lic_adc.h"
#include "lic328p_gpio.h"


void adc_init() {
	adc_fPrsc(128);											// It will be 125 kHz for 16 MHz Crystal
	adc_voltRef(V_INT);									// Set the internal 1.1 Voltage Reference

  ADMUX &= ~(1<<ADLAR);               // Right adjusten of the data presentation

	adc_triggerSrc(TC1_OVERFLOW);				// Set the T/C 1 to overflow interrupt
  adc_setMux(ADC0);                   // First channel initialization

  ADCSRA |= (1<<ADATE);               // Auto trigger enable
  ADCSRA |= (1<<ADIE);                // ADC conversion complete interrupt 
                                      // enable
}

void init_adcChan
       (adc_channel* chn) {
  chn->config[0] = (adc_config) {
      .name = ADC0, 
      .mux  = 0x00,
  };
  chn->config[1] = (adc_config) {
      .name = ADC1, 
      .mux  = 0x01 
  };
  chn->currentChan = &chn->config[0];
}


enum adc_chan next_adcChannel
	(uint8_t size, 
	 enum adc_chan cname) {

  enum adc_chan ch = cname++;

  if(ch >= (size)) {
    ch = ADC0;
  };
  return ch;
}

uint8_t adc_switchChannel
  (adc_channel* config) {

  uint8_t size = 
    MAX_ADC_CHANNELS - 1;             // Getting number of channels in array

  if(config->currentChan->name >= 
      (size)) {                       // If the current channel is last
    config->currentChan = 
      &config->config[ADC0];          // switch to the first channel in array
  } else {
    config->currentChan++;            // If not, switch to the next channel
  };

  return config->currentChan->mux;    // Return MUX bit configuration for the 
                                      // currently selected channel
}
