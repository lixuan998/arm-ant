#include "arch/riscv/include/riscv_interrupt.h"

extern volatile int tick_cnt;

void riscv_interrupt_init()
{
    // riscv_interrupt_disable();
    k_printf("stvec1: %x\n\r", r_stvec());
    w_stvec((uint64)k_interrupt_vector);
    k_printf("stvec2: %x\n\r", r_stvec());
    plic_interrupt_enable();
    riscv_interrupt_enable();
}

void riscv_interrupt_enable()
{
    k_printf("sstatus1: %x\n\r", r_sstatus());
    turn_on_s_interrupt();
    k_printf("sstatus2: %x\n\r", r_sstatus());
}

void riscv_interrupt_disable()
{
    turn_off_s_interrupt();
}
uint32 riscv_get_interrupt_source()
{
    return read_reg32(PLIC_SCLAIM_REG);
}

void riscv_interrupt_handler()
{
    uint64 scause = r_scause();
    uint64 scause_code = r_scause() & SCAUSE_EXCEPTION_CODE_MASK;
    // k_printf("AAA\n\r");
    k_printf("scause: %x code: %d\n\r", scause, scause_code);
    if(scause & SCAUSE_INTERRUPT)
    {
        switch(scause_code)
        {
            case SCAUSE_SOFTWARE_INTERRUPT:
            {
                break;
            }
            case SCAUSE_TIMER_INTERRUPT:
            {
                break;
            } 
            case SCAUSE_EXTERNAL_INTERRUPT:
            {
                riscv_external_interrupt_handler();
                break;
            }
            default:
                break;
        }
        
    }
}

void riscv_external_interrupt_handler()
{
    enum PLIC_INTERRUPT_SOURCE plic_interrupt_source;
    plic_interrupt_source = riscv_get_interrupt_source();
    switch (plic_interrupt_source)
    {
        case 44:
        {
            char c;
            int ret = k_getc(&c);
            while(ret >= 0)
            {
                console_get_char(c);
                ret = k_getc(&c);
            }
            break;
        }
        case TIMER0:
        {
            // k_printf("timer0 init\n\r");
            k_time_stamp_update();
            timer_pending_clear(0);
            break;
        }
        
        default:
            break;
        }
    riscv_external_interrupt_source_done(plic_interrupt_source);
}


void riscv_external_interrupt_source_done(int source)
{
    write_reg32(PLIC_SCLAIM_REG, source);
}