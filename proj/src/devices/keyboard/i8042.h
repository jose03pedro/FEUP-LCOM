#ifndef _SRC_I8042_KEYBOARD_H_
#define _SRC_I8042_KEYBOARD_H_

#define IRQ_KEYBOARD 1

#define MAKE_CODE BIT(7)
#define TWO_BYTES 0xE0
#define ENABLE_INT BIT(0)

#define TIMEOUT_ERROR BIT(6)
#define PARITY_ERROR BIT(7)
#define FULL_OUT_BUFFER BIT(0)
#define FULL_IN_BUFFER BIT(1)

#define KBC_STATUS_REG 0x64
#define KBC_IN_CMD 0x64
#define KBC_OUT_CMD 0x60
#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60

#define WAIT_KBC 20000
#define MAX_ATTEMPS 10

#define Q 16
#define W 17
#define E 18
#define A 30
#define S 31
#define D 32
#define G 34
#define H 35

#endif
