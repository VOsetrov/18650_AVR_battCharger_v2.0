#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "lic328p_gpio.h"
#include "lic_menuio.h"
#include "battery.h"
#include "lic_18650h.h"
#include "lic_uart.h"
#include "lic_adc.h"

static transmit_data packet_tx = {0};

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

static battTxStatus transmitStatus = {
  .currentstatus = &transmitStatus
    .fieldsstatus[deviceID],
  .fieldsstatus = {
    { deviceID, false },
    { voltage, false },
    { capacitance, false },
    { resistance, false },
  }
};

void battTransmitChecking
  (battTxStatus* array);

void battTransmitChecking
  (battTxStatus* array) {

  parameters battnamevalue = array->
     currentstatus->field;

  switch(battnamevalue) {
   case deviceID:
     break;
   case voltage:
     break;
   case resistance:
     break;
   case capacitance:
     break;
  };
}

ISR(ADC_vect) {

  battery mybattery = {0};

  while(!(ADCSRA & (1<<ADIF))) {        // Waiting for conversion
  };
  mybattery.voltage = adc();            // Saving ADC data
  mybattery.id = returnBattID
    (channel.currentChan->name);        // Saving current Battery ID
  packet_tx.ready = 
    fillTransmitPackage(&mybattery,
      &packet_tx);                      // Fill out the package and set status
  adc_setMux(adc_switchChannel
      (&channel));                      // Set the next ADC Channel for meas.
  ADCSRA |= (1<<ADIF);                  // Clearing the flag for the next 
                                        // interrupt.
  reti();                               // Returns from an interrupt routine
}

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);                 // Selecting the Menu Mode
  UCSR0A |= (1<<RXC0);                  // We are ready to receive new data
  
  reti();
}

ISR(USART_UDRE_vect) {

  reti();
}

ISR(USART_TX_vect) {

  reti();
}


int main(void) {

  port_init();
  uart_init(MYUBRR); 
  timer_init();
  adc_init();

  sei();

  while(1) {

    if(UCSR0B & (1<<TXCIE0)) {
      if(checkTransmit(&transmitStatus)) {
        resetTransmitStatus(&transmitStatus);
        batstat.currbat = &batstat.list[
          updateBatteryTransmitStatus(&batstat)];
      };

    };

  return 0;
  }
}
