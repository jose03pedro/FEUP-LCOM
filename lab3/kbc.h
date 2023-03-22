#include <lcom/lcf.h>
#include "i8042.h"
#include "../lab2/utils.c"
#include "../lab2/i8254.h"
#include <minix/sysutil.h>

int kbc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes KBC interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_unsubscribe_int();

/**
 * @brief Reads the KBC configuration (status)
 *
 * @param st    Address of memory position to be filled with the kbc config
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_get_status(uint8_t *st);

/**
 * @brief Reads the output buffer of KBC
 *
 * @param port  Buffer to read
 * @param data    Address of memory position to be filled with the output buffer byte
 * @return Return 0 upon success and non-zero otherwise
 */
int read_kbc_command(int port, uint8_t *data);

/**
 * @brief Writes (issues) a command to the KBC
 *
 * @param port Buffer to write
 * @param cmd The command to output to the KBC
 * @return Return 0 upon success and non-zero otherwise
 */
int write_kbc_command(int port, uint8_t cmd);

/**
 * @brief Reads the value of the OBF of the KBC
 *
 * @param data The variable to store the read data
 * @return Return 0 upon success and non-zero otherwise
 */
int read_kbc_output(uint8_t* data);

/**
 * @brief Restores the Minix Interrupt Handler for KBC
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_restore();
