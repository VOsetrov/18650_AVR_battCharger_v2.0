#ifndef LIC_MENUIO_H
#define LIC_MENUIO_H

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

Menu menu;

void setMode(Menu* menu, uint8_t udr);
void exitHandler();
void chargHandler();
void capHandler();
void inResHandler();

#endif
