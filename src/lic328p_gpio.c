#include <avr/io.h>
#include "lic328p_gpio.h"

void port_init() {
  DDRB |= (1<<GREEN);                 // Set the LED ports to write
  DDRB |= (1<<RED);                   // ...
  PORTB &= ~(1<<GREEN);               // Set the RedLED port to 0V (off)
  PORTB &= ~(1<<RED);                 // Set the GreenLED port to 0V (off)
}

void uart_init
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

void timer_init() {
  TCCR1A &= ~(1<<COM1A1);             // OC1A/OC1B disconnected 
  TCCR1A &= ~(1<<COM1A0);
  TCCR1A &= ~(1<<WGM10);              // Set the Normal bit mode 
  TCCR1A &= ~(1<<WGM11);
  TCCR1B &= ~(1<<WGM12);
  TCCR1B &= ~(1<<WGM13);
  TCCR1B &= ~(1<<CS10);               // Set the prescaler CLKi/o/256
  TCCR1B &= ~(1<<CS11);
  TCCR1B |= (1<<CS12);
  TIMSK1 = 0b00000001;                // Overflow interrupt Enable
  TCNT1 = 0;                          // Reset register value to zero
}

void led_control(enum state state) {
  switch (state) {
    case ON:
      PORTB |= (1<<GREEN);
      break;
    case OFF:
      PORTB &= ~(1<<GREEN);
      break;
  }
}
