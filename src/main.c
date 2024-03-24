#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lic_menuio.h"
#include "serial.h"
#include "lic328p_gpio.h"



static Menu menu = {
  .currentMode = &menu.modes[EXIT], 
  .modes = {
    { 0x30, exitHandler },
    { 0x31, chargHandler},
    { 0x32, capHandler  },
    { 0x33, inResHandler},
  }
};


ISR(TIMER1_OVF_vect) {

}

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);
  UCSR0A |= (1<<RXC0);                // we are ready to receive new data
}


int main(void) {
  
  port_init();
  uart_init(MYUBRR); 
  timer_init();
  sei();

  while(1) {
  }
  return 0;
}
