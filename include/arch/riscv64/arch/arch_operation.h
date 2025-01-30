#pragma once
#include <common/stdint.h>
#include <arch/arch_defs.h>
/****************************************************************************************************************************************************
 *
 *
 * mstatus Bitmap in RV64:
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |   Bit   | Abbr Name |                       Full Name                        |                    Description                      |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    0    |    WPRI   |   Reserved Writes Preserve Values, Reads Ignore Values |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    1    |    SIE    |               Supervisor Interrupt Enable              |      Turn on/off interrupt in Supervisor mode       |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    2    |    WPRI   |   Reserved Writes Preserve Values, Reads Ignore Values |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    3    |    MIE    |               Machine Interrupt Enable                 |        Turn on/off interrupt in Machine mode        |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    4    |    WPRI   |                     Write Privilege                    |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    5    |    SPIE   |          Supervisor Previous Interrupt Enable          | Previously Turn on/off interrupt in Supervisor mode |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    6    |    UBE    |                   User Mode Big-Endian                 |             Use Big-Endian in User mode             |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    7    |    MPIE   |            Machine Previous Interrupt Enable           |   Previously Turn on/off interrupt in Machine mode  |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    8    |    SPP    |             Supervisor Previous Privilege              |             Save previous privilege mode            |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |   9~10  |    VS     |                    Virtual Supervisor                  |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  11~12  |    MPP    |               Machine Privious Privilege               |             Save previous privilege mode            |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  13~14  |    FS     |                  Floating-Point Status                 |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  15~16  |    XS     |                    Extension Status                    |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    17   |    MPRV   |                    Modify Privilege                    |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    18   |    SUM    |              Supervisor User Memory Access             |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    19   |    MXR    |                 Make Excutable Readable                |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    20   |    TVM    |                  Trap Virtual Memory                   |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    21   |    TW     |                     Timeout Wait                       |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    22   |    TSR    |                        Trap SRET                       |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  23~31  |    WPRI   |   Reserved Writes Preserve Values, Reads Ignore Values |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  32~33  |    UXL    |                    User-mode Extension Level           |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  34~35  |    SXL    |            Supervisr-mode Extension Level              |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    36   |    SBE    |                  Store Barrier Enable                  |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    37   |    MBE    |                Machine Breakpoint Enable               |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |  38~62  |    WPRI   |   Reserved Writes Preserve Values, Reads Ignore Values |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 * |    63   |     SD    |                      State Dirty                       |                       NONE                          |
 * +---------+-----------+--------------------------------------------------------+-----------------------------------------------------+
 *
 *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * @brief This function's purpose is to read the Machine Status Register, which  keeps track of and controls the hart’s current
 * operating state. This register is in the Machine Mode.
 ****************************************************************************************************************************************************/
static inline uint64_t  r_mstatus()
{
    uint64_t mstatus;
    asm volatile("csrr %0, mstatus" : "=r"(mstatus));
    return mstatus;
}

/****************************************************************************************************************************************************
 * @brief This function's purpose is to write the Machine Status Register, which  keeps track of and controls the hart’s current
 * operating state. This register is in the Machine Mode.
 ****************************************************************************************************************************************************/
static inline void w_mstatus(uint64_t mstatus)
{
    asm volatile("csrw mstatus, %0" : : "r"(mstatus));
}

inline void w_mepc(uint64_t mepc)
{
    asm volatile("csrw mepc, %0" : : "r"(mepc));
}

/****************************************************************************************************************************************************
 * @brief this function's purpose is to read the Hart ID Register, which contains the integer ID of the hardware
 * thread running the code. This register is in the Machine Mode.
 ****************************************************************************************************************************************************/
static inline uint64_t r_mhartid()
{
    uint64_t mhartid;
    asm volatile("csrr %0, mhartid" : "=r"(mhartid));
    return mhartid;
}

static inline void w_medeleg(uint64_t medeleg)
{
    asm volatile("csrw medeleg, %0" : : "r"(medeleg));
}

static inline void w_mideleg(uint64_t mideleg)
{
    asm volatile("csrw mideleg, %0" : : "r"(mideleg));
}
/****************************************************************************************************************************************************
 * @brief this function's purpose is to read the  Supervisor Address Translation and Protection (satp) Register
 * , controls supervisor-mode address translation and protection.
 * In RV64, Mode currently has 5 options:
 * 0    -   Bare Mode   -   No translation or protection(no paging)
 * 8    -     Sv39      -   Page-based 39-bit virtual addressing
 * 9    -     Sv48      -   Page-based 48-bit virtual addressing
 * 10   -     Sv57      -   Reserved for page-based 57-bit virtual addressing
 * 11   -     Sv64      -   Reserved for page-based 64-bit virtual addressing
 * In RV32, Mode has only two options:
 * 0    -   Bare Mode   -   No translation or protection(no paging)
 * 1    -     Sv32      -   Page-based 32-bit virtual addressing
 ****************************************************************************************************************************************************/
static inline uint64_t r_satp()
{
    uint64_t satp;
    asm volatile("csrr %0, satp" : "=r"(satp));
    return satp;
}

/****************************************************************************************************************************************************
 * @brief this function's purpose is to write the  Supervisor Address Translation and Protection (satp) Register
 * , controls supervisor-mode address translation and protection.
 ****************************************************************************************************************************************************/
static inline void w_satp(uint64_t satp)
{
    asm volatile("csrw satp, %0" : : "r"(satp));
}

static inline uint64_t r_sie()
{
    uint64_t sie;
    asm volatile("csrr %0, sie" : "=r"(sie));
    return sie;
}

static inline void w_sie(uint64_t sie)
{
    asm volatile("csrw sie, %0" : : "r"(sie));
}

static inline void w_pmpaddr0(uint64_t pmpaddr0)
{
    asm volatile("csrw pmpaddr0, %0" : : "r"(pmpaddr0));
}

static inline void w_pmpcfg0(uint64_t pmpcfg0)
{
    asm volatile("csrw pmpcfg0, %0" : : "r"(pmpcfg0));
}

static inline uint64_t r_tp()
{
    uint64_t tp;
    asm volatile("mv %0, tp" : "=r"(tp));
    return tp;
}

static inline void w_tp(uint64_t tp)
{
    asm volatile("mv tp, %0" : : "r"(tp));
}

/****************************************************************************************************************************************************
 * @brief This function's purpose is to read the Supervisor Status Register, which  keeps track of and controls the hart’s current
 * operating state. This register is in the Machine Mode.
 ****************************************************************************************************************************************************/
static inline uint64_t r_sstatus()
{
    uint64_t sstatus;
    asm volatile("csrr %0, sstatus" : "=r"(sstatus));
    return sstatus;
}

/****************************************************************************************************************************************************
 * @brief This function's purpose is to write the Supervisor Status Register, which  keeps track of and controls the hart’s current
 * operating state. This register is in the Machine Mode.
 ****************************************************************************************************************************************************/
static inline void w_sstatus(uint64_t sstatus)
{
    asm volatile("csrw sstatus, %0" : : "r"(sstatus));
}

static inline void w_stvec(uint64_t stvec)
{
    asm volatile("csrw stvec, %0" : : "r"(stvec));
}

static inline uint64_t r_stvec()
{
    uint64_t stvec;
    asm volatile("csrr %0, stvec" : "=r"(stvec));
    return stvec;
}

static inline uint64_t r_scause()
{
    uint64_t scause;
    asm volatile("csrr %0, scause" : "=r"(scause));
    return scause;
}

static inline uint64_t r_stval()
{
    uint64_t stval;
    asm volatile("csrr %0, stval" : "=r"(stval));
    return stval;
}

static inline void turn_on_s_interrupt()
{
    w_sstatus(r_sstatus() | SSTATUS_SIE_MASK);
}

static inline void turn_off_s_interrupt()
{
    w_sstatus(r_sstatus() & ~SSTATUS_SIE_MASK);
}

static inline int s_interrupt_status()
{
    return (r_sstatus() & SSTATUS_SIE_MASK);
}

static inline void sfence_vma()
{
    // Flush all TLB entries.-
    asm volatile("sfence.vma zero, zero");
}

static inline int get_cpu_id()
{
    return 0;
    int cpu_id = (uint64_t)r_tp();
    return cpu_id;
}

static inline void w_sepc(uint64_t x)
{
    asm volatile("csrw sepc, %0" : : "r"(x));
}

static inline uint64_t r_sepc()
{
    uint64_t x;
    asm volatile("csrr %0, sepc" : "=r"(x));
    return x;
}
