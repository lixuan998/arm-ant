#include "plic.h"

void plic_interrupt_enable()
{
    for(int i = 1; i < PLIC_INTERRUPT_MAX; ++ i)
    {
        write32(PLIC_PRIO_REG(i), PLIC_ENABLE);
    }
    for(int i = 0; i < 10; ++ i)
    {
        write32(PLIC_SIE_REG(i), 0xFFFFFFFF);
    }
}

void plic_interrupt_disable()
{
    for(int i = 1; i < PLIC_INTERRUPT_MAX; ++ i)
    {
        write32(PLIC_PRIO_REG(i), PLIC_DISABLE);
    }
    for(int i = 0; i < 10; ++ i)
    {
        write32(PLIC_SIE_REG(i), PLIC_DISABLE);
    }
}

int plic_interrupt_source()
{
    return read32(PLIC_SCLAIM_REG);
}

void plic_interrupt_handled(int source)
{
    write32(PLIC_SCLAIM_REG, source);
}