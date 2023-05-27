#include "timer.h"
#include <lcom/lcf.h>
#include <stdint.h>

int timer_hook_id = 0;
int counter = 0;

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq > TIMER_FREQ || freq < 19)
    return 1;

  uint8_t controlWord;
  timer_get_conf(timer, &controlWord);

  controlWord = (controlWord & 0x0F) | TIMER_LSB_MSB;

  uint32_t initialValue = TIMER_FREQ / freq;
  uint8_t MSB, LSB;
  util_get_MSB(initialValue, &MSB);
  util_get_LSB(initialValue, &LSB);

  uint8_t selectedTimer;
  switch (timer) {
    case 0:
      controlWord |= TIMER_SEL0;
      selectedTimer = TIMER_0;
      break;
    case 1:
      controlWord |= TIMER_SEL1;
      selectedTimer = TIMER_1;
      break;
    case 2:
      controlWord |= TIMER_SEL2;
      selectedTimer = TIMER_2;
      break;
    default:
      return 1;
  }

  sys_outb(TIMER_CTRL, controlWord);
  sys_outb(selectedTimer, LSB);
  sys_outb(selectedTimer, MSB);

  return 0;
}

int(timer_subscribe_interrupts)() {
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int(timer_unsubscribe_interrupts)() {
  if (sys_irqrmpolicy(&timer_hook_id) != 0)
    return 1; // desligar as interrupções
  return 0;
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL || timer > 2 || timer < 0)
    return 1;
  uint8_t RBC = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));
  sys_outb(TIMER_CTRL, RBC);
  return util_sys_inb(TIMER_0 + timer, st);
}
