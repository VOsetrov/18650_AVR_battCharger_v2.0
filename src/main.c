#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>
#include "lic328p_gpio.h"
#include "lic_menuio.h"
#include "battery.h"
#include "lic_18650h.h"
#include "lic_uart.h"
#include "lic_adc.h"

static volatile transmit_data packet_tx;
static volatile adcChannel channel;
static volatile batlist batstat;

ISR(ADC_vect) {

  uint16_t data = adc();
  battID id = returnBattID(channel.
      currentChan->name);

  if(batstat.plist->id != id) {
    batstat.plist = 
      &batstat.list[id];
  };

  batstat.plist->voltage = data;        // Saving ADC data
  packet_tx.ready = 
    fillTransmitPackage(batstat.plist,
    &packet_tx);                        // Fill out the package and set status

  enum adc_chan cname = next_adcChannel(
    MAX_ADC_CHANNELS, channel.
    currentChan->name);
  channel.currentChan = &channel.
    config[cname];
  adc_setMux(cname);                    // Set the next ADC Channel for meas.

	UCSR0B |= (1 << UDRIE0);							// Data Reg. Empty Interrupt Enable
//  ADCSRA |= (1<<ADIF);                  // Clearing the flag for the next 
//                                        // interrupt.
}

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);                 // Selecting the Menu Mode

/*
  UCSR0A |= (1<<RXC0);                  // We are ready to receive new data
*/

}

ISR(USART_UDRE_vect) {
  if(packet_tx.ready && !packet_tx.
      inprocess) {
    memcpy((void *)(packet_tx.data),
      (const void *)(batstat.plist),
      sizeof(battery));
    packet_tx.pdata = (uint8_t *)
      (packet_tx.data);
    packet_tx.inprocess = true;
    packet_tx.ready = false;
		UCSR0B |= (1 << TXCIE0);
  } else if(packet_tx.inprocess) {
    UDR0 = *packet_tx.pdata;
  };
}

ISR(USART_TX_vect) {
  if(packet_tx.inprocess) {
    packet_tx.pdata++;
  };
  if(packet_tx.pdata >= packet_tx.end) {
    packet_tx.inprocess = false;
		UCSR0B &= ~(1 << TXCIE0);
  };

}

int main(void) {

  port_init();
  uart_init(MYUBRR);
  timer_init();
  adc_init();

  init_adcChan(&channel);
  init_battData(&batstat);
  init_transmitData(&packet_tx);

  sei();

  while(true) {
  };

  return 0;
}
