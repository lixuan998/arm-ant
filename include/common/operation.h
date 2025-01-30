#pragma once

#include <lib/printk.h>
#include <common/stdint.h>
#include <common/stddef.h>
#include <arch/arch_operation.h>

#define ALIGN_FLOOR(addr)                     (((addr)) & ~(PAGE_SIZE - 1))
#define ALIGN_CEIL(addr)                      (((addr) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

#define IOMEM(addr) ((volatile void __iomem *)((long)(addr)))

inline void write32(volatile uint32_t reg, uint32_t val)
{
    volatile uint32_t *reg_ptr = (uint32_t *)((long)reg);
    *reg_ptr = val;
}

inline uint32_t read32(volatile uint32_t reg)
{
    uint32_t val = *((uint32_t *)((long)reg));
    return val;
}

inline void write64(volatile uint64_t reg, uint64_t val)
{
    volatile uint64_t *reg_ptr = (uint64_t *)((long)reg);
    *reg_ptr = val;
}

inline uint64_t read64(volatile uint64_t reg)
{
    volatile uint64_t val = *((uint64_t *)((long)reg));
    return val;
}

// extern void context_switch(CONTEXT *old_context, CONTEXT *new_context);

#define panic(msg, ...) \
        do { \
            printk("KERNEL PANIC[%s]:%d " msg "\n\r",__func__, __LINE__, ##__VA_ARGS__); \
            while(1); \
        } while(0)
