#ifndef STARTIO_H
#define STARTIO_H

typedef enum LedList {
  GREEN,                              // The battery is full of charge
  RED,                                // The battry is low of charge
} Led;

enum state {
  OFF,
  ON,
};

typedef enum {
  EXIT,
  CHARGING,
  INTERN_RES,
  CAPACITANCE,
} MenuList;

typedef struct MenuMode {
  uint8_t signal;
  void (*handler)();
} MenuMode;

typedef struct Menu { 
  MenuMode* currentMode;
  MenuMode modes[];
} Menu;

void setMode(Menu* menu, uint8_t udr);
void exitHandler();
void chargHandler();
void capHandler();
void inResHandler();

#endif
