#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  
  uint8_t st=0;

  return (timer_get_conf(timer, &st) || timer_display_conf(timer, st, field));
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {

  return timer_set_frequency(timer, freq);
}

int(timer_test_int)(uint8_t time) {
  
  //ipc_status and msg are used to receive messages from the kerne
  int ipc_status;
  message msg;

  //r is used to store the return value of driver_receive
  int r;

  uint8_t hook_id;
  if(timer_subscribe_int(&hook_id)!=0) {
    printf("Error subscribing timer\n");
    return 1;
  }

  //runs until the specified number of seconds (time) has passed
  while (time) {

    //is called to receive a message from the kernel
    //endpoint: the identifier of the process that is waiting for the message. It can be a specific endpoint (task identifier) or the constant value ANY, meaning that the call will return the first message from any endpoint
    //message_ptr: A pointer to a message structure, which will hold the received message
    //ipc_status: A pointer to a variable that will hold the status of the IPC (Inter-Process Communication) operation
    //when driver_receive is called, it will block the calling process until a message is received or an error occurs
    
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    //the ipc_status variable will hold the status of the IPC operation, indicating whether the message was a notification or a standard message
    if (is_ipc_notify(ipc_status)) {

      //msg.m_source contains the identifier of the sender of the message.
      //the _ENDPOINT_P macro is used to extract the process endpoint number from the sender identifier
      //this endpoint number is used to determine the type of message received, and the switch statement is used to handle the different types of messages
      switch (_ENDPOINT_P(msg.m_source)) {
        
        //the only type of message being handled is a hardware interrupt notification
        case HARDWARE:

          //checks if the message was sent by the hardware interrupt that the timer is hooked to
          if (msg.m_notify.interrupts & BIT(hook_id)) {
            
            //if so, timer_int_handler is called to handle the interrupt
            timer_int_handler();
            if (counter % 60 == 0) {
              timer_print_elapsed_time();
              time--;
            }
          }
          break;
        default:
          break;
      }
    } 
  }

  timer_unsubscribe_int();
  return 0;
 
}


