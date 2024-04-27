#ifndef LIC_UART_H
#define LIC_UART_H

#include <stdbool.h>
#include "battery.h"

typedef struct {
  uint8_t data[PACKET_SIZE];
  bool inprocess;
  bool ready;
} transmit_data;

void uart_init();
void uart_transmit(uint8_t data);
bool fillTransmitPackage(const volatile battery*
    currbat, transmit_data* packet_tx);

#endif
