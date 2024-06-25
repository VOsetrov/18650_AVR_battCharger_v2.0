#ifndef ATMEGA328P_H_SENTRY
#define ATMEGA328P_H_SENTRY

#include <stdint.h>

/*=========================ANALOG_TO_DIGITAL_CONVERTER========================*/

enum adc_chan {												// Input Channel Selection
  ADC0,
  ADC1,
  ADC2,
  ADC3,
  ADC4,
  ADC5,
  ADC6,
  ADC7,
  ADC8,																// (1) For Temperature Sensor
};

enum adc_auto_trigger {								// ADC Auto Trigger Source Selection
	FREE_RUN,
	ANALOG_COMP,
	EXT_INTERRUPT,
	TC0_COMP,
	TC0_OVERFLOW,
	TC1_COMP,
	TC1_OVERFLOW,
	TC1_CAPTURE,
}; 

enum v_ref {
	V_REF_OFF,
	AVCC,
	V_INT,
};

void adc_fPrsc(uint8_t freq);					// Set the ADC Frequency Prescaler Bits
void adc_triggerSrc
	(enum adc_auto_trigger mode);				// Set the ADC Auto Trigger Source Bits
void adc_voltRef(enum v_ref mode);		// Set the ADC Voltage Reference Bits
uint16_t adc();                       // Returns the ADC data register value
void adc_setMux(uint8_t muxset);      // Init a selected ADC channel

#endif
