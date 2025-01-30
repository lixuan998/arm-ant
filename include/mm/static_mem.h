#pragma once

#include <common/stddef.h>
#include <common/stdint.h>
#include <common/operation.h>
#include <arch/arch_defs.h>

void static_mem_init();
addr_t static_mem_alloc();
void static_mem_free(addr_t addr);