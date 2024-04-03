#include <avr/io.h>
#include <stdint.h>
#include "lic_adc.h"
#include "lic328p_gpio.h"

adcChannel channel = {
  .currentChan = &channel
    .config[ADC0],
  .config = {
    { ADC0, 0x00 },
    { ADC1, 0x01 },
  }
};

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

  adc_setMux(channel.config[ADC0]
    .mux);

  ADCSRA |= (1<<ADEN);                // Turn the ADC on  
}

uint16_t adc() {
  uint8_t adcLow = ADCL;
  return ADCH << 8 | adcLow; 
}

void adc_setMux 
  (uint8_t muxset) {

  uint8_t reg = ADMUX;
  reg &= 0xF0;                        // Set the MUX bits to the 0
  reg |= muxset;                      // Set MUX bits to input channel 
  ADMUX = reg;
}

uint8_t adc_switchChannel
  (adcChannel* config) {

  uint8_t size = (sizeof(config)) /
    (sizeof(config[ADC0]));

  if(config->currentChan->name == 
      (size-1)) {
    config->currentChan = 
      &config->config[ADC0];
  } else {
    config->currentChan++;
  };

  return config->currentChan->mux;

}
