#ifndef LIC_MENUIO_C
#define LIC_MENUIO_C

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include "lic_menuio.h"
#include "lic_adc.h"
#include "lic328p_gpio.h"

void exitHandler() {
  PORTB &= ~(1<<GREEN);
  ADCSRA &= ~(1<<ADEN);                         // Turn the ADC off  
  UCSR0B &= ~(1<<TXCIE0);                       // TX Complete Interrupt 
                                                // disable 
}

void chargHandler() {
  PORTB |= (1<<GREEN);
  ADCSRA |= (1<<ADEN);                          // Turn the ADC on  
  UCSR0B |= (1<<TXCIE0);                        // TX Complete Interrupt enable 
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
