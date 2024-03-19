#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "startio.h"

enum {
  BAUD          = 9600,
  FOSC          = 16000000,
  MYUBRR        = 103,                // (FOSC/(16*BAUD))-1,
  MAX_I         = 60,                 // Number of measurments (2^16 bit/1024)
  LOW_LVL       = 535,                // ADC parameter equal to 2.7V
  HIGH_LVL      = 831,                // ADC parameter equal to 4.2V

};

static inline void portInit();
static inline void UART_init
  (unsigned int ubrr);

static Menu menu = {
  .currentMode = &menu.modes[EXIT], 
  .modes = {
    { 0x30, exitHandler },
    { 0x31, chargHandler},
    { 0x32, capHandler  },
    { 0x33, inResHandler},
  }
};

inline void portInit() {
  DDRB |= (1<<GREEN);                 // Set the LED ports to write
  DDRB |= (1<<RED);                   // ...
  PORTB &= ~(1<<GREEN);               // Set the RedLED port to 0V (off)
  PORTB &= ~(1<<RED);                 // Set the GreenLED port to 0V (off)
}

inline void UART_init
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

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);
  UCSR0A |= (1<<RXC0);                // we are ready to receive new data
}

int main(void) {
  
  portInit();
  UART_init(MYUBRR); 
  sei();

  while(1) {
  }
  return 0;
}
