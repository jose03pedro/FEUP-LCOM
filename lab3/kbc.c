#include "kbc.h"

int keyboard_hook_id=1; 
uint8_t scancode = 0; 
int keyboard_counter=0;

int kbc_subscribe_int(uint8_t *bit_no){
    if(bit_no==NULL) return 1;
    *bit_no=BIT(keyboard_hook_id);
    return (sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE|IRQ_EXCLUSIVE, &keyboard_hook_id))
}

int kbc_unsubscribe_int(){
    return sys_irqrmpolicy(&keyboard_hook_id);
}

int kbc_get_status(uint8_t *st) {
  return util_sys_inb(KBC_STATUS_REG, st);
}

int read_kbc_command(int port, uint8_t *data){
    return util_sys_inb(port, data);
}

int write_kbc_command(uint8_t port, uint8_t commandByte){
  
  uint8_t status;
  uint8_t attemps = 10;

  while (attemps) {
    if (read_kbc_status(&status) != 0) { // ler o status
      printf("Error: Status not available!\n");
      return 1;
    }

    if ((status & BIT(1)) == 0) {
      // o input buffer não está cheio, pode-se escrever
      if (sys_outb(port, commandByte) != 0) {
        // tentativa de escrita
        printf("Error: Could not write commandByte!\n");
        return 1;
      }
      
      return 0; // sucesso: comando inserido no i8042
    }
    
    tickdelay(micros_to_ticks(20000));              
    attemps--;
  }
  
  return 1; // se ultrapassar o número de tentativas lança um erro
}

int read_kbc_output(uint8_t port, uint8_t *output){
  
  uint8_t status;
  uint8_t attemps = 10;
    
  while (attemps) {
    if (read_kbc_status(&status) != 0) { // ler o status
      printf("Error: Status not available!\n");
      return 1;
    }

    if ((status & BIT(0)) != 0) {
      // o output buffer está cheio, pode-se ler
      if (util_sys_inb(port, output) != 0) {
        // leitura do buffer de saída
        printf("Error: Could not read output!\n");
        return 1;
      }
      
      if((status & BIT(7)) != 0) {
        // verifica erro de paridade
        printf("Error: Parity error!\n");
        return 1;
      }
      
      if ((status & BIT(6)) != 0) {
        // verifica erro de timeout
        printf("Error: Timeout error!\n");
        return 1;
      }
      
      return 0;
    }
   
    tickdelay(micros_to_ticks(20000));
    attemps--;
  }
 
  return 1; // se ultrapassar o número de tentativas lança um erro
}

int kbc_restore(){
  
  uint8_t commandWord;

  // Leitura da configuração atual
  if (write_kbc_command(0x64, 0x20) != 0)
    return 1;  // notificar o i8042 da leitura
    
  if (read_kbc_command(0x60, &commandWord) != 0)
    return 1;  // ler a configuração

  // Activar o bit das interrupções
  commandWord = commandWord | BIT(0);

  // Escrita da nova configuração
  if (write_kbc_command(0x64, 0x60) != 0)
    return 1;  // notificar o i8042 da escrita
    
  if (write_kbc_command(0x60, commandWord) != 0)
    return 1;  // escrever a configuração
    
  return 0;
}

void kbc_ih(void) {
  if (kbc_read_data(&scancode) != 0)
    printf("Unable to read scancode!");
}