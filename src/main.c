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

static volatile tx_data tx_package;
static volatile adc_channel channel;
static volatile batlist batstat;

ISR(ADC_vect) {

  uint16_t data = adc();
	batt_data_handling(data, &batstat);
	fill_tx_package(&batstat, 
		&tx_package); 
	UCSR0B |= (1 << UDRIE0);	

/*
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
                                        // interrupt.
*/
	
}

ISR(USART_RX_vect) {

  setMode(&menu, UDR0);                 // Selecting the Menu Mode
}

ISR(USART_UDRE_vect) {

	if(tx_package.index < tx_package.length) {
		UDR0 = tx_package.data[tx_package.index];
		tx_package.index++;
	} else {
		tx_package.inprocess = false;
		UCSR0B &= ~(1 << UDRIE0);
	};
/*
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
*/
}

ISR(USART_TX_vect) {
/*
  if(packet_tx.inprocess) {
    packet_tx.pdata++;
  };
  if(packet_tx.pdata >= packet_tx.end) {
    packet_tx.inprocess = false;
		UCSR0B &= ~(1 << TXCIE0);
  };
*/
}

int main(void) {

  port_init();
  uart_init(MYUBRR);
  timer_init();
  adc_init();

  init_adcChan(&channel);
  init_battData(&batstat);
  init_tx_data(&tx_package);

  sei();

  while(1) {
		if(!tx_package.inprocess) {
		};
  };

  return 0;
}
