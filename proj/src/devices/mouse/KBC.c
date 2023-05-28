#include "KBC.h"

int(read_KBC_status)(uint8_t *status) {
  return util_sys_inb(KBC_STATUS_REG, status);
}

int read_KBC_output(uint8_t port, uint8_t *output, uint8_t mouse) {
  uint8_t status;
  uint8_t attemps = 10;

  while (attemps) {
    read_KBC_status(&status);

    if ((status & BIT(0)) != 0) {
      util_sys_inb(port, output);

      if ((!mouse && (status & BIT(5))) || (mouse && !(status & BIT(5))) || ((status & BIT(7)) != 0) || ((status & BIT(6)) != 0)) {
        return 1;
      }

      return 0;
    }
    tickdelay(micros_to_ticks(20000));
    attemps--;
  }
  return 1;
}

int(write_KBC_command)(uint8_t port, uint8_t control) {

  uint8_t status;
  uint8_t attemps = MAX_ATTEMPS;

  while (attemps) {
    read_KBC_status(&status);

    if ((status & FULL_IN_BUFFER) == 0) {
      sys_outb(port, control);
      return 0;
    }

    tickdelay(micros_to_ticks(WAIT_KBC));
    attemps--;
  }

  return 1;
}
