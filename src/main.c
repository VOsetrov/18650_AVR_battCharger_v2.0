#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lic328p_gpio.h"
#include "lic_menuio.h"
#include "lic_uart.h"
#include "lic_adc.h"
#include "lic_18650h.h"

static adcChannel channel = {
  .currentChan = &channel
    .config[ADC0],
  .config = {
    { ADC0, 0x00 },
    { ADC1, 0x01 },
  }
};

static batlist batstat = {
  .currbat = &batstat.list[BATT1],
  .list = {
    { BATT1, 0, 0, 0 },
    { BATT2, 0, 0, 0 },
  }
};

static void voltage_saveData
  (uint16_t adcData, batlist* batstat,
    adcchan channel);

ISR(ADC_vect) {

  while(!(ADCSRA & (1<<ADIF))) {        // Waiting for conversion
  };

  voltage_saveData(adc(), &batstat,
      channel.currentChan->name);
  adc_setMux(adc_switchChannel
      (&channel));                      // Set the next ADC Channel for meas.
  ADCSRA |= (1<<ADIF);                  // Clearing the flag for the next 
                                        // interrupt.
  reti();                               // Returns from an interrupt routine
}

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);                 // Selecting the Menu Mode
  UCSR0A |= (1<<RXC0);                  // we are ready to receive new data
}

void voltage_saveData(uint16_t adcData,
    batlist* batstat, adcchan channel) {

  switch(channel) {
    case ADC0:
      batstat->list[BATT1].voltage = 
        adcData;
      batstat->currbat = 
        &batstat->list[BATT1];
      break;
    case ADC1:
      batstat->list[BATT2].voltage =
        adcData;
      batstat->currbat =
        &batstat->list[BATT2];
      break;
    default:
      break;
  }
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
