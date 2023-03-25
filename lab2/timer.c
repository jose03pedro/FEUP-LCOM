#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer < 0 || timer > 2 || freq < 19 || freq > TIMER_FREQ)
    return 1;
  uint8_t config;
  timer_get_conf(timer, &config);
  config &= 0x0F;
  config |= TIMER_LSB_MSB;
  switch (timer) {
    case 0: config |= TIMER_SEL0; break;
    case 1: config |= TIMER_SEL1; break;
    case 2: config |= TIMER_SEL2; break;
    default: return 1;
  }
  sys_outb(0x43, config);
  //====================================================
  uint16_t new_counter = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  util_get_LSB(new_counter, &lsb);
  util_get_MSB(new_counter, &msb);
  sys_outb(0x40 + timer, lsb);
  sys_outb(0x40 + timer, msb);
  return 0;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void(timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer < 0 || timer > 2)
    return 1;
  uint8_t read_back = BIT(7) | BIT(6) | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(0x43, read_back);
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
      return timer_print_config(timer, field, val);
    case tsf_initial:
      st = st >> 4;
      st &= 0x3;
      if (st == 0x3)
        val.in_mode = MSB_after_LSB;
      else if (st == 0x1)
        val.in_mode = LSB_only;
      else if (st == 0x2)
        val.in_mode = MSB_only;
      else
        val.in_mode = INVAL_val;
      return timer_print_config(timer, field, val);
    case tsf_mode:
      st = st >> 1;
      st &= 0x7;
      val.count_mode = st;
      return timer_print_config(timer, field, val);
    case tsf_base:
      st = st & 0x1;
      val.bcd = (st & BIT(0));
      return timer_print_config(timer, field, val);
    default: return 1;
  }
}
