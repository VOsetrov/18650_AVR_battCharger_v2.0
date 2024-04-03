#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lic328p_gpio.h"
#include "lic_menuio.h"
#include "lic_uart.h"
#include "lic_adc.h"
#include "lic_18650h.h"

ISR(ADC_vect) {
  while(!(ADCSRA & (1<<ADIF))) {        // Waiting for conversion
  };
  uint16_t regdata = adc();             // Data from ADC register

  ADCSRA |= (1<<ADIF);                  // Clearing the flag for the next 
                                        // interrupt.
}

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);                 // Selecting the Menu Mode
  UCSR0A |= (1<<RXC0);                  // we are ready to receive new data
}

int main(void) {
  
  port_init();
  uart_init(MYUBRR); 
  timer_init();
  adc_init();

  sei();

  while(1) {
  }
  return 0;
}
