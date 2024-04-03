#ifndef LIC328p_GPIO_H
#define LIC328p_GPIO_H

enum {
  BAUD          = 9600,
  FOSC          = 16000000,
  MYUBRR        = 103,                // (FOSC/(16*BAUD))-1,
  MAX_I         = 60,                 // Number of measurments (2^16 bit/1024)
  LOW_LVL       = 535,                // ADC parameter equal to 2.7V
  HIGH_LVL      = 831,                // ADC parameter equal to 4.2V
};

typedef enum LedList {
  GREEN,                              // The battery is full of charge
  RED,                                // The battry is low of charge
} Led;

enum state {
  OFF,
  ON,
};

typedef enum {
  ADC0,
  ADC1,
  ADC2,
  ADC3,
  ADC4,
  ADC5,
  ADC6,
  ADC7,
  ADC8,
} adcchan;

void port_init();
void timer_init();
void led_control(enum state state);

#endif
