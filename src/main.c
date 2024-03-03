#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart_handler.h"
#include "adc_handler.h"

enum {
  BAUD          = 9600,
  FOSC          = 16000000,
  MYUBRR        = 103,                // (FOSC/(16*BAUD))-1,
  MAX_I         = 60,                 // Number of measurments (2^16 bit/1024)
  LOW_LVL       = 535,                // ADC parameter equal to 2.7V
  HIGH_LVL      = 831,                // ADC parameter equal to 4.2V

};

enum tx_app MENU_SIG = exit;

void portInit() {
}

ISR(USART_RX_vect) {
  
  MENU_SIG = UART_menuHandler(UDR0);                                    
  UCSR0A |= (1<<RXC0);                // we are ready to receive new data
}

int main(void) {

  sei();

  UART_init(MYUBRR); 

  switch(MENU_SIG) {
    case charging:
      break;
    case checkCap:
      break;
    case interRes:
      break;
    case exit:
      break;
  };
  return 0;
}
