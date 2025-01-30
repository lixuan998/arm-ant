#pragma once

#define PAGE_SIZE                             (4096UL)
#define SQRT_PAGE_SIZE                        (64UL)

#define STATIC_MEM_PAGES                      (1024)

#define HEAP_MEM_SIZE                         (100 * 1024 * 1024)
#define KERNEL_TEXT_SEG_MEM_SIZE              (100 * 1024)
#define KERNEL_DATA_SEG_MEM_SIZE              (10 * 1024 * 1024)
#define KERNEL_MEM_SIZE                       (KERNEL_TEXT_SEG_MEM_SIZE + KERNEL_DATA_SEG_MEM_SIZE)

#define KERNEL_BASE_ADDR                      (0x40000000UL)
#define HEAP_MEM_BASE_ADDR                    (KERNEL_BASE_ADDR + KERNEL_MEM_SIZE)
#define MEM_TOP_ADDR                          (KERNEL_BASE_ADDR + KERNEL_MEM_SIZE + HEAP_MEM_SIZE)

#define VM_ADDR_MAX_VAL                       (0x90000000)

#define VM_TRAMPOLINE_ADDR                    (VM_ADDR_MAX_VAL - PAGE_SIZE)
#define VM_TRAPFRAME_ADDR                     (VM_TRAMPOLINE_ADDR - PAGE_SIZE)

#ifndef __TRAMPOLINE__
extern char                                 __kernel_start[];
extern char                                 __kernel_end[];
extern char                                 __kernel_text_start[];
extern char                                 __kernel_text_end[];
extern char                                 rodata_end_addr[];
extern char                                 data_end_addr[];
extern char                                 bss_start_addr[];
extern char                                 bss_end_addr[];
extern char                                 trampoline_start_addr[];
extern char                                 trampoline_end_addr[];
extern char                                 trampoline[];
#endif /* __TRAMPOLINE__ */