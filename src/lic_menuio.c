#ifndef LIC_MENUIO_C
#define LIC_MENUIO_C

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include "lic_menuio.h"
#include "lic_adc.h"
#include "lic328p_gpio.h"

void exitHandler() {
//  PORTB &= ~(1<<GREEN);
  ADCSRA &= ~(1<<ADEN);                         // ADC disable 
//  UCSR0B &= ~(1<<TXCIE0);                       // TX Complete Interrupt
                                                // disable
  UCSR0B &= ~(1<<UDRIE0);                       // Data Reg. Empty Interrupt 
                                                // disable
	ADCSRA &= ~(1<<ADEN);
}

void chargHandler() {
//  PORTB |= (1<<GREEN);
//  UCSR0B |= (1<<TXCIE0);                        // TX Complete Interrupt enable 
//  UCSR0B |= (1<<UDRIE0);                        // Data Reg. Empty Interrupt 
//                                                // enable
  ADCSRA |= (1<<ADEN);                          // ADC Enable
	ADCSRA |= (1<<ADSC);													// ADC Start Conversion
}

void capHandler() {
}

void inResHandler() {
}

Menu menu = {
  .currentMode = &menu.modes[EXIT], 
  .modes = {
    { 0x30, exitHandler },
    { 0x31, chargHandler},
    { 0x32, capHandler  },
    { 0x33, inResHandler},
  }
};

void setMode 
  (Menu* menu, uint8_t udr) {
  if((udr >= menu->modes[EXIT].signal)          // Signal compliance check
     && (udr <= menu->modes[CAPACITANCE].
      signal)) {
    for(int i = EXIT; i <= CAPACITANCE; i++) {  // Iterate over array elements
      if(udr == menu->modes[i].signal) {        // If the compliance is TRUE
        menu->currentMode = &menu->modes[i];    // setting the current mode
        break;
      }
    }
  }
  if(menu->currentMode != NULL) {
    menu->currentMode->handler();
  }
}

#endif
