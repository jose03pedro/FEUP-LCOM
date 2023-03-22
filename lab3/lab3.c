#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include "i8042.h"
#include "kbc.h"
#include "../lab2/timer.c"
#include <stdbool.h>
#include <stdint.h>

extern int counter, keyboard_counter;
extern uint8_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int kbd_test_scan() {
  
  int ipc_status,r;
  uint8_t keyboard_hook_id;
  message msg;
  uint8_t bytes[2];

  if (kbc_subscribe_int(&keyboard_hook_id) != 0)
    return 1;

  while(scancode != BREAK_ESC) {
    if (r=driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if (msg.m_notify.interrupts & keyboard_hook_id) {
            kbc_ih();
            if (scan_code == TWO_BYTES) {
              bytes[i]=scancode;
              i++;
              continue;
            }
            bytes[i]=scancode;
            kbd_print_scancode(ih_flag, (i+1), bytes);
            i = 0;

          }
          break;
        }
        default: break;
    }
  }

  kbc_unsubscribe_int();
  kbc_print_no_sysinb(keyboard_counter);
  return 0;
}

int kbd_test_poll() {
  
  int i=0;
  uint8_t bytes[2];

  while(scancode != BREAK_ESC){
    if(read_kbc_output(&scancode) != 0){
      tickdelay(20000);
      continue;
    }
    if(scancode == TWO_BYTES){
      bytes[i] = scancode;
      i++;
      continue;
    }
    bytes[i] = scancode;
    kbd_print_scancode(!(scancode & BIT(7)),i+1,bytes);
    i=0;

  }

  kbc_restore();
  kbd_print_no_sysinb(keyboard_counter);

  return 0;
}

int kbd_test_timed_scan(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}