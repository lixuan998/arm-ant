#include <mm/mmu.h>
#include <mm/mem_paging.h>
#include <common/operation.h>
#include <mm/static_mem.h>

error_t pgtbl_insert(pgtbl_t* pgtbl, mmu_map_tbl map_tbl[],
                     uint32_t tbl_entrys, mem_type type)
{
    if(pgtbl == NULL) panic("In func pgtbl_insert, pgtbl is empty!");
    for(uint32_t i = 0; i < tbl_entrys; ++ i)
    {
        error_t ret = arch_mmu_mapping(pgtbl, map_tbl[i].virt_addr_start,
                                       map_tbl[i].phys_addr_start, map_tbl[i].size,
                                       map_tbl[i].permisson, type);
        if(ret != AA_ERROR_SUCCESS) // TODO: maybe need some recycles?
            return ret;
    }
    return AA_ERROR_SUCCESS;
}

pgtbl_t* pgtbl_create(mmu_map_tbl map_tbl[], uint32_t tbl_entrys,
                      mem_type type)
{
    pgtbl_t* pgtbl;
    if(type == MEM_TYPE_DYN)
        pgtbl = (pgtbl_t*)mem_page_alloc();
    else if(type == MEM_TYPE_STATIC)
        pgtbl = (pgtbl_t*)static_mem_alloc();
    else
        panic("mem type is invalid");
    error_t ret = pgtbl_insert(pgtbl, map_tbl,
                               tbl_entrys, type);
    if(ret != AA_ERROR_SUCCESS)
    {
        mem_page_free((addr_t)pgtbl);
        return NULL;
    }
    return pgtbl;
}

void kernel_mmu_enable()
{
    arch_kernel_mmu_enable();
}
void pgtbl_destroy(pgtbl_t* pgtbl, mem_type type)
{
    for(int i = 0; i < 512; ++ i)
    {
        pte_t pte = pgtbl[i];
        if((pte & PTE_PERMISSION_V) && ((pte & PTE_PERMISSION_R) == 0))
        {
            addr_t pgtbl_child = PTE_TO_PHY_ADDR(pte);
            pgtbl_destroy((pgtbl_t*)pgtbl_child, type);
            pgtbl[i] = (pgtbl_t)NULL;
        }
    }
    if(type == MEM_TYPE_DYN)
        mem_page_free((addr_t)pgtbl);
    else if(type == MEM_TYPE_STATIC)
        static_mem_free((addr_t)pgtbl);
    pgtbl = (pgtbl_t *)NULL;
}

void mmu_enable(pgtbl_t *pgtbl)
{
    arch_mmu_enable(pgtbl);
}