#pragma once

#include <common/stdint.h>
#include <common/stddef.h>

void uart_init();
void uart_send_byte(uint8_t byte);
void uart_recv_byte(uint8_t *byte);
void uart_print_str(char *str);