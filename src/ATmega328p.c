#include <avr/io.h>
#include "ATmega328p.h"


void adc_fPrsc(uint8_t freq) {
	switch(freq) {
		case 0:														// Set the prescaler of frequency to 0
			ADCSRA &= ~(1<<ADPS0);
			ADCSRA &= ~(1<<ADPS1);
			ADCSRA &= ~(1<<ADPS2);
			break;
		case 2:														// Set the prescaler of frequency to 2
			ADCSRA |= (1<<ADPS0);
			ADCSRA &= ~(1<<ADPS1);
			ADCSRA &= ~(1<<ADPS2);
			break;
		case 4:														// Set the prescaler of frequency to 4
			ADCSRA &= ~(1<<ADPS0);
			ADCSRA |= (1<<ADPS1);
			ADCSRA &= ~(1<<ADPS2);
			break;
		case 8:														// Set the prescaler of frequency to 8
			ADCSRA |= (1<<ADPS0);
			ADCSRA |= (1<<ADPS1);
			ADCSRA &= ~(1<<ADPS2);
			break;
		case 16:													// Set the prescaler of frequency to 16
			ADCSRA &= ~(1<<ADPS0);
			ADCSRA &= ~(1<<ADPS1);
			ADCSRA |= (1<<ADPS2);
			break;
		case 32:													// Set the prescaler of frequency to 32
			ADCSRA |= (1<<ADPS0);
			ADCSRA &= ~(1<<ADPS1);
			ADCSRA |= (1<<ADPS2);
			break;
		case 64:													// Set the prescaler of frequency to 64
			ADCSRA &= ~(1<<ADPS0);
			ADCSRA |= (1<<ADPS1);
			ADCSRA |= (1<<ADPS2);
			break;
		case 128:													// Set the prescaler of frequency to 128
			ADCSRA |= (1<<ADPS0);						
			ADCSRA |= (1<<ADPS1);
			ADCSRA |= (1<<ADPS2);
			break;
	};
}

void adc_triggerSrc
	(enum adc_auto_trigger mode) {
	switch (mode) {
		case FREE_RUN:										// Free Running mode
			ADCSRB &= ~(1<<ADTS0);
			ADCSRB &= ~(1<<ADTS1);
			ADCSRB &= ~(1<<ADTS2);
			break;
		case ANALOG_COMP:									// Analog Comparator interrupt
			ADCSRB |= (1<<ADTS0);
			ADCSRB &= ~(1<<ADTS1);
			ADCSRB &= ~(1<<ADTS2);
			break;
		case EXT_INTERRUPT:								// External Interrupt Request 0
			ADCSRB &= ~(1<<ADTS0);
			ADCSRB |= (1<<ADTS1);
			ADCSRB &= ~(1<<ADTS2);
			break;
		case TC0_COMP:										// Timer/Counter0 Compare Match A
			ADCSRB |= (1<<ADTS0);
			ADCSRB |= (1<<ADTS1);
			ADCSRB &= ~(1<<ADTS2);
			break;
		case TC0_OVERFLOW:								// Timer/Counter0 Overflow
			ADCSRB &= ~(1<<ADTS0);
			ADCSRB &= ~(1<<ADTS1);
			ADCSRB |= (1<<ADTS2);
			break;
		case TC1_COMP:										// Timer/Counter1 Compare Match B
			ADCSRB |= (1<<ADTS0);
			ADCSRB &= ~(1<<ADTS1);
			ADCSRB |= (1<<ADTS2);
			break;
		case TC1_OVERFLOW:								// Timer/Counter1 Overflow Interrupt
			ADCSRB &= ~(1<<ADTS0);
			ADCSRB |= (1<<ADTS1);
			ADCSRB |= (1<<ADTS2);
			break;
		case TC1_CAPTURE:									// Timer/Counter1 Capture Event
			ADCSRB |= (1<<ADTS0);
			ADCSRB |= (1<<ADTS1);
			ADCSRB |= (1<<ADTS2);
			break;
	};
}

void adc_voltRef(enum v_ref mode) {
	switch (mode) {
		case V_REF_OFF:										// Internal Vref turned off
			ADMUX &= ~(1<<REFS0);
			ADMUX &= ~(1<<REFS1);
			break;
		case AVCC:												// AVcc selection 
			ADMUX |= (1<<REFS0);
			ADMUX &= ~(1<<REFS1);
			break;
		case V_INT:												// Internal 1.1V Voltage Reference
			ADMUX |= (1<<REFS0);
			ADMUX |= (1<<REFS1);
			break;
	};
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

