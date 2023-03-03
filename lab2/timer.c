#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint16_t counter = TIMER_FREQ / freq;
  uint8_t conf;
  uint8_t lsb, msb;
  if (freq < 19 || freq > TIMER_FREQ)
    return 1;

  if (timer_get_conf(timer, &conf))
    return 1;

  conf &= 0x0F;
  conf = conf | TIMER_LSB_MSB; // ativar bits do timer

  util_get_LSB(counter, &lsb);
  util_get_MSB(counter, &msb);

  sys_outb(TIMER_CTRL, conf);

  switch (timer) {
    case 0:
      conf = conf | TIMER_SEL0;
      break;
    case 1:
      conf = conf | TIMER_SEL1;
      break;
    case 2:
      conf = conf | TIMER_SEL2;
      break;
    default:
      return 1;
  }
  return 0;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == NULL)
    return 1;
  *bit_no = BIT(timer);
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer))
    return 1;
  return 0;
}

int(timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer))
    return 1;
  return 0;
}

void(timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer < 0 || timer > 2)
    return 1;

  uint8_t controlword = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  sys_outb(TIMER_CTRL, controlword);
  util_sys_inb(0x40 + timer, st);
  return 0;
}

int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  if (timer < 0 || timer > 2)
    return 1;
  union timer_status_field_val val;
  switch (field) {
    case tsf_all:
      val.byte = st;
      break;
    case tsf_initial:
      if (st & TIMER_LSB)
        val.in_mode = LSB_only;
      else if (st & TIMER_MSB)
        val.in_mode = MSB_only;
      else if (st & TIMER_LSB_MSB)
        val.in_mode = MSB_after_LSB;
      else
        val.in_mode = INVAL_val;
      break;
    case tsf_mode:
      val.count_mode = st & 0x0E;
      break;
    case tsf_base:
      val.bcd = st & 0x0E;
      break;
    default: return 1;
  }
  return timer_print_config(timer, field, val);
}
