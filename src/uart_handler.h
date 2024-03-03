#include <avr/io.h>
#include <avr/interrupt.h>

enum tx_app {
  charging,
  checkCap,
  interRes,
  exit,
};

static inline void UART_init
  (unsigned int ubrr);

enum tx_app UART_menuHandler(
    uint8_t udr);

static inline void UART_init
  (unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr>>8);  // Set the BAUD rate in UART baud Rate
  UBRR0L = (unsigned char)ubrr;       // Registers (to low & high)
  UCSR0B = 0b11011000;                // Set the RX&TX&Interrupt Rx enable
  UCSR0C &= ~(1<<UMSEL01);            // Set the Asynchronus UART mode
  UCSR0C &= ~(1<<UMSEL00);            // ...
  UCSR0C &= ~(1<<USBS0);              // Set the 1 stop bit
  UCSR0B &= ~(1<<UCSZ02);             // Set the 8 bit package settings
  UCSR0C |= (1<<UCSZ01);              // ...
  UCSR0C |= (1<<UCSZ00);              // ...
}

enum tx_app UART_menuHandler(
    uint8_t udr) {

  enum tx_app retVal = exit;
                                        
    switch(udr) {
      case charging:
        retVal = charging;
        break;
      case checkCap:
        retVal = checkCap;
        break;
      case interRes:
        retVal = interRes;
        break;
      case exit:
        retVal = exit;
        break;
    };

  return retVal;
}
