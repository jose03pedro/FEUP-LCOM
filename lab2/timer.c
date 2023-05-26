#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook_id = 0;

int(timer_set_frequency)(uint8_t timer, uint32_t freq)
{

  if (!((timer == 0) || (timer == 1) || (timer == 2)))
    return 1;
  if (freq < 19 || freq > TIMER_FREQ)
    return 1;
  uint16_t div = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  util_get_LSB(div, &lsb);
  util_get_MSB(div, &msb);
  uint8_t conf;
  if (timer_get_conf(timer, &conf) != 0)
    return 1;
  conf = conf & 0x0F;
  conf = conf | BIT(4) | BIT(5);

  if (timer == 0)
    conf = conf | 0x00;
  else if (timer == 1)
    conf = conf | BIT(6);
  else
    conf = conf | BIT(7);
  sys_outb(TIMER_CTRL, conf);
  sys_outb(TIMER_0 + timer, lsb);
  sys_outb(TIMER_0 + timer, msb);
  return 0;
}

int(timer_subscribe_int)(uint8_t *bit_no)
{
  if(bit_no==NULL) return 1;
  *bit_no = BIT(hook_id);
  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
  return 0;
}

int(timer_unsubscribe_int)()
{
  sys_irqrmpolicy(&hook_id);
  return 0;
}

void(timer_int_handler)()
{
  counter++;
}

int(timer_get_conf)(uint8_t timer, uint8_t *st)
{
  uint8_t controlworld = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1);
  // read back(6 e 7); ler config, não ler contador(5); selecionar o timer escolhido;
  sys_outb(TIMER_CTRL, controlworld);
  util_sys_inb(TIMER_0 + timer, st);
  return 0;
}

int(timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field)
{
  union timer_status_field_val status;

  switch (field)
  {
  case tsf_all:
    status.byte = st;
    break;
  case tsf_initial:
    status.in_mode = (st >> 4) & 3;
    break;
  case tsf_mode:
    status.count_mode = (st >> 1) & 7;
    break;
  case tsf_base:
    status.bcd = st & 0x01;
    break;
  }

  return timer_print_config(timer, field, status);
}
