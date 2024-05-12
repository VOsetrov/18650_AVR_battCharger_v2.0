#include <avr/io.h>
#include "lic328p_gpio.h"
#include "lic_adc.h"

void port_init() {
  DDRC &= ~(1<<DDC0);                 // Set the ADC0 port to read
  DDRC &= ~(1<<DDC1);                 // Set the ADC1 port to read
  DDRB |= (1<<GREEN);                 // Set the LED ports to write
  DDRB |= (1<<RED);                   // ...
  PORTB &= ~(1<<GREEN);               // Set the RedLED port to 0V (off)
  PORTB &= ~(1<<RED);                 // Set the GreenLED port to 0V (off)
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
