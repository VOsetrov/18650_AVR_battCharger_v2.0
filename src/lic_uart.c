#include <avr/io.h>
#include "lic_uart.h"
#include "lic328p_gpio.h"

void uart_init() {
  UBRR0H = (uint8_t)(MYUBRR>>8);      // Set the BAUD rate in UART baud Rate
  UBRR0L = (uint8_t)MYUBRR;           // registers (to low & high)
  UCSR0B |= (1<<RXCIE0);              // Rx Complete Interrupt enable
  UCSR0B &= ~(1<<TXCIE0);             // Tx Complete Interrupt enable OFF
  UCSR0B &= ~(1<<UDRIE0);             // Data Reg. Empty Interrupt Enable OFF
  UCSR0B |= (1<<RXEN0);               // Receiver Enable ON
  UCSR0B |= (1<<TXEN0);               // Transmitter Enable ON
  UCSR0B &= ~(1<<UCSZ02);
  UCSR0B &= ~(1<<RXB80);
  UCSR0B &= ~(1<<TXB80);
  UCSR0C &= ~(1<<UMSEL01);            // Set the Asynchronus UART mode
  UCSR0C &= ~(1<<UMSEL00);            // ...
  UCSR0C &= ~(1<<USBS0);              // Set the 1 stop bit
  UCSR0B &= ~(1<<UCSZ02);             // Set the 8 bit package settings
  UCSR0C |= (1<<UCSZ01);              // ...
  UCSR0C |= (1<<UCSZ00);              // ...
}

void uart_transmit(uint8_t data) {
  while(!(UCSR0A & (1<<UDRE0))) {
  };
  UDR0 = data;
}

bool fillTransmitPackage(const volatile battery*
    currbat, transmit_data* packet_tx) {

  uint8_t* dataPtr = (uint8_t*)currbat;

  for(uint8_t i = 0; i < sizeof(battery); i++) {
    packet_tx->data[i] = *dataPtr;
    dataPtr++;
  };
  return true;
}
