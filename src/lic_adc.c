#include <avr/io.h>
#include <stdint.h>
#include "lic_adc.h"
#include "lic328p_gpio.h"

void adc_init() {
  ADCSRA |= (1<<ADPS2);               // Set the prescaler of freqency to 128 
  ADCSRA |= (1<<ADPS1);               // it will be 125 kHz for ATmega328P
  ADCSRA |= (1<<ADPS0);               // ...
  ADCSRA |= (1<<ADATE);               // Auto trigger enable
  ADMUX |= (1<<REFS1);                // Set the internal 1.1V voltage reference
  ADMUX |= (1<<REFS0);                // ...
  ADMUX &= ~(1<<ADLAR);               // Right adjusten of the data presentation
  ADCSRB &= ~(1<<ADTS0);              // Timer/Counter1 overflow interrups
  ADCSRB |= (1<<ADTS1);               // ...
  ADCSRB |= (1<<ADTS2);               // ...

  adc_setMux(ADC0);                   // First channel initialization

  ADCSRA |= (1<<ADEN);                // Turn the ADC on  
}

uint16_t adc() {
  uint8_t adcLow = ADCL;
  return ADCH << 8 | adcLow;          // Returns the current conversion value
}

void adc_setMux 
  (uint8_t muxset) {                  // Current ADC channel setup

  uint8_t reg = ADMUX;
  reg &= 0xF0;                        // Seting MUX bits to the 0
  reg |= muxset;                      // MUX bits setup to the current value
  ADMUX = reg;                        // Register configuration assignment
}

adcchan next_adcChannel(uint8_t size,
    adcchan cname) {
  adcchan ch = cname++;

  if(ch >= (size)) {
    ch = ADC0;
  };
  return ch;
}

uint8_t adc_switchChannel
  (adcChannel* config) {

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
