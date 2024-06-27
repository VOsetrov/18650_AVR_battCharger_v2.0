#ifndef LIC_UART_H
#define LIC_UART_H

#include <stdbool.h>
#include "battery.h"

typedef volatile struct {
  uint8_t data[PACKET_SIZE];                    // Sending package
  bool inprocess;                               // State of sending
  uint8_t index;                       	        // Number of a current sByte
  uint8_t length;                               // Packet length[PACKET_SIZE]
} tx_data;

void uart_init(uint16_t ubrr);
void init_tx_data(tx_data* td);
void uart_transmit(uint8_t data);
void uart_transmit_package();
bool fill_tx_package
  (const volatile batlist *currbatt, 
    tx_data* tpack);

#endif
