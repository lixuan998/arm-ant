#pragma once

#include <arch/mm/arch_mmu.h>
#include <mm/mem_defs.h>
#include <common/error.h>

error_t pgtbl_insert(pgtbl_t* pgtbl, mmu_map_tbl map_tbl[],
                     uint32_t tbl_entry, mem_type type);

pgtbl_t* pgtbl_create(mmu_map_tbl map_tbl[], uint32_t tbl_entrys,
                      mem_type type);
void pgtbl_destroy(pgtbl_t* pagetable, mem_type type);
void kernel_mmu_enable();
void mmu_enable(pgtbl_t *pagetable);
void mmu_disable();