#ifndef __HW_DEFS_H__
#define __HW_DEFS_H__

/* UART related definitions. */
#define UART_BASE 0x02500000
#define UARTn_BASE(n) (UART ## n ## _BASE)
#define UART_THR 0x0000
#define UART_RBR 0x0000
#define UART_USR 0x007C
#define UART_IER 0x0004
#define UART_FCR 0x0008
#define UART_LCR 0x000C
#define UART_LSR 0x0014
#define UART_IIR 0x0008

#endif /* __HW_DEFS_H__ */