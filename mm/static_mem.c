#include <mm/static_mem.h>
#include <common/lock.h>
#include <arch/arch_mem_layout.h>
#include <lib/memops.h>
#include <lib/bitmap.h>

static spinlock splock;
static char static_mem_pool[STATIC_MEM_PAGES][PAGE_SIZE] __attribute__((aligned(PAGE_SIZE)));
static bitmap static_mem_bitmap;
void static_mem_init()
{
    spinlock_init(&splock);
    error_t ret = bitmap_init(&static_mem_bitmap, STATIC_MEM_PAGES);
    if(ret != AA_ERROR_SUCCESS)
    {
        panic("static memory bitmap init failed");
    }
}
addr_t static_mem_alloc()
{
    spinlock_lock(&splock);
    addr_t ret = 0;
    uint32_t bitmap_val;
    for(int i = 0; i < STATIC_MEM_PAGES; ++ i)
    {
        error_t err = bitmap_read(&static_mem_bitmap, i,
                                  &bitmap_val);
        if(err != AA_ERROR_SUCCESS)
        {
            printk("bitmap read failed\n\r");
            goto err;
        }
        if(bitmap_val == 0)
        {
            bitmap_set(&static_mem_bitmap, i);
            ret = (addr_t)(static_mem_pool + i);
            break;
        }
    }
err:
    spinlock_unlock(&splock);
    return ret;
}

void static_mem_free(addr_t addr)
{
    spinlock_lock(&splock);
    bitmap_clear(&static_mem_bitmap, (addr - (addr_t)static_mem_pool) / PAGE_SIZE);
    memset(static_mem_pool[(addr - (addr_t)static_mem_pool) / PAGE_SIZE], 0, PAGE_SIZE);
    spinlock_unlock(&splock);
}