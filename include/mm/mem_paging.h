#pragma once

#include <arch/arch_defs.h>

#define FREE_PAGE_VALUE      0xFF
#define ALLOCATED_PAGE_VALUE 0x00

typedef struct _MEM_PAGE{
    struct _MEM_PAGE *next;
} MEM_PAGE;

void mem_paging_init();
addr_t mem_page_alloc();
void mem_page_free(addr_t page);
void mem_page_range_free(addr_t start, addr_t end);