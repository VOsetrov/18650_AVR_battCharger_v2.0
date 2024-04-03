#include <avr/io.h>
#include "lic_18650h.h"

batlist batstat = {
  .currbat = &batstat.list[BATT1],
  .list = {
    { BATT1, 0, 0, 0 },
    { BATT2, 0, 0, 0 },
  }
};
