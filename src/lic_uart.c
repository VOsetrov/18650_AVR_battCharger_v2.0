#include <avr/io.h>
#include <string.h>
#include "lic_uart.h"
#include "lic328p_gpio.h"

void uart_init(uint16_t ubrr) {
  UBRR0H = (uint8_t)(ubrr>>8);        // Set the BAUD rate in UART baud Rate
  UBRR0L = (uint8_t)ubrr;             // registers (to low & high)
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
  UCSR0B |= (1<<RXCIE0);              // Rx Complete Interrupt enable
  UCSR0B &= ~(1<<TXCIE0);             // Tx Complete Interrupt enable OFF
}

void init_tx_data(tx_data* td) {
  memset((void *)(td->data), 0, PACKET_SIZE);
  td->inprocess = false;
  td->index = 0;
  td->length = PACKET_SIZE;
}

void uart_transmit(uint8_t data) {
  while(!(UCSR0A & (1<<UDRE0))) {
  };
  UDR0 = data;
}

void batt_data_handling
	(uint16_t data, batlist *pdata) {
	pdata->plist->id 					= BATT1;
	pdata->plist->voltage 		= data;
	pdata->plist->capacitance	= 0;
	pdata->plist->resistance	= 0;
}

bool fill_tx_package
  (const volatile batlist *currbatt, 
   tx_data* tpack) {

	const volatile battery *pbatt = 
		currbatt->plist;

	if(!tpack->inprocess) {
		memcpy((void *) tpack->data, 
			(const void *) pbatt,
			PACKET_SIZE);
		tpack->index = 0;
		tpack->inprocess = true;
  	return true;
	};

	return false;
}
