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

static transmit_data packet_tx;

static adcChannel channel = {
  .currentChan = &channel
    .config[ADC0],
  .config = {
    { ADC0, 0x00 },
    { ADC1, 0x01 },
  }
};

static batlist batstat = {
  .plist = &batstat.list[BATT1],
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

  while(!(ADCSRA & (1<<ADIF))) {        // Waiting for conversion
  };
  uint16_t data = adc();
  battID id = returnBattID(channel.
      currentChan->name);

  if(batstat.plist->id != id) {
    batstat.plist = &batstat.list[id];
  };

  batstat.plist->voltage = data;        // Saving ADC data
  packet_tx.ready = 
    fillTransmitPackage(batstat.plist,
    &packet_tx);                        // Fill out the package and set status

  adcchan cname = next_adcChannel(
    MAX_ADC_CHANNELS, channel.
    currentChan->name);
  channel.currentChan = &channel.
    config[cname];
  adc_setMux(cname);                    // Set the next ADC Channel for meas.

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
  if(packet_tx.ready){
    packet_tx.inprocess = true;
    packet_tx.ready = false;
  } else if(packet_tx.inprocess) { 
    UDR0 = *packet_tx.pdata;
  };
  reti();
}

ISR(USART_TX_vect) {
  if(packet_tx.inprocess) {
    packet_tx.pdata++;
  };
  if(packet_tx.pdata >= packet_tx.end) {
    init_transmitData(&packet_tx); 
  };

  reti();
}


int main(void) {

  port_init();
  uart_init(MYUBRR); 
  timer_init();
  adc_init();

  init_transmitData(&packet_tx);

  sei();

  while(1) {

    if(UCSR0B & (1<<TXCIE0)) {
      if(checkTransmit(&transmitStatus)) {
        resetTransmitStatus(&transmitStatus);
        batstat.plist = &batstat.list[
          updateBatteryTransmitStatus(&batstat)];
      };

    };

  return 0;
  }
}
