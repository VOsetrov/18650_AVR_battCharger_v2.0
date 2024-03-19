#ifndef STARTIO_C
#define STARTIO_C

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include "startio.h"


void exitHandler() {
  PORTB &= ~(1<<GREEN);
}
void chargHandler() {
  PORTB |= (1<<GREEN);
}
void capHandler() {
}

void inResHandler() {
}

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
