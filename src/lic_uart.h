#ifndef LIC_UART_H
#define LIC_UART_H

#include <stdbool.h>
#include "battery.h"

typedef struct {
  uint8_t data[PACKET_SIZE];                    // Sending package
  bool inprocess;                               // State of sending
  bool ready;                                   // Package is ready to send
  uint8_t* pdata;                               // Pointer to data[PACKET_SIZE]
  uint8_t* end;                                 // The end of data[PACKET_SIZE]
} transmit_data;

void uart_init();
void init_transmitData(transmit_data* td);
void uart_transmit(uint8_t data);
bool fillTransmitPackage
  (const volatile battery* currbat, 
    transmit_data* packet_tx);

#endif
