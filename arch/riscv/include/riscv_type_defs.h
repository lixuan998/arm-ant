#ifndef __RISCV_TYPE_DEFS_H__
#define __RISCV_TYPE_DEFS_H__

#include "riscv_mem_layout.h"

typedef unsigned int                          uint;
typedef unsigned short                        ushort;
typedef unsigned char                         uchar;

typedef unsigned char                         uint8;
typedef unsigned short                        uint16;
typedef unsigned int                          uint32;
typedef unsigned long                         uint64;

typedef uint64                                isa_reg_t;
typedef uint32                                soc_reg_t;
typedef uint64                                ptr_t;

typedef uint64*                               pagetable_t;
typedef uint64                                pte_t;
typedef uint64                                addr_t;
typedef uint64                                pagesize_t;

#define NULL                                  0UL

#define bitof(x)   (sizeof(x) * 8)



/**
 * @brief Process Related Defines.
 * 
 */
#define VM_PROC_SHARED_MEM_ADDR (0x40000000)

enum PROC_STATE{
    PROC_STATE_RUNNING,
    PROC_STATE_READY,
    PROC_STATE_WAITING,
    PROC_STATE_EXIT,
    PROC_STATE_SLEEPING,
    PROC_STATE_ZOMBIE,
};

enum PROC_PRIORITY{
    PROC_PRIORITY_LOW,
    PROC_PRIORITY_MEDIUM,
    PROC_PRIORITY_HIGH,
};

typedef struct _TRAPFRAME{
    isa_reg_t k_satp;  // pagetable in kernel mode.
    isa_reg_t k_sp;    // used in kernel mode for processes when they trap to the kernel mode.
    isa_reg_t k_trap;
    isa_reg_t epc;     // saved user program counter.
    isa_reg_t pid;
    isa_reg_t ra;
    isa_reg_t sp;
    isa_reg_t gp;
    isa_reg_t tp;
    isa_reg_t t0;
    isa_reg_t t1;
    isa_reg_t t2;
    isa_reg_t s0;
    isa_reg_t s1;
    isa_reg_t a0;
    isa_reg_t a1;
    isa_reg_t a2;
    isa_reg_t a3;
    isa_reg_t a4;
    isa_reg_t a5;
    isa_reg_t a6;
    isa_reg_t a7;
    isa_reg_t s2;
    isa_reg_t s3;
    isa_reg_t s4;
    isa_reg_t s5;
    isa_reg_t s6;
    isa_reg_t s7;
    isa_reg_t s8;
    isa_reg_t s9;
    isa_reg_t s10;
    isa_reg_t s11;
    isa_reg_t t3;
    isa_reg_t t4;
    isa_reg_t t5;
    isa_reg_t t6;
} TRAPFRAME;

typedef struct _CONTEXT{
    isa_reg_t ra;
    isa_reg_t sp;
    isa_reg_t s0;
    isa_reg_t s1;
    isa_reg_t s2;
    isa_reg_t s3;
    isa_reg_t s4;
    isa_reg_t s5;
    isa_reg_t s6;
    isa_reg_t s7;
    isa_reg_t s8;
    isa_reg_t s9;
    isa_reg_t s10;
    isa_reg_t s11;
} CONTEXT;


typedef struct _PROC{
    void *sleep_for;
    int child_exit_ret;
    int pid;
    enum PROC_STATE proc_state;

    struct _PROC *parent;

    pagetable_t pagetable;
    addr_t phy_k_stack;
    addr_t vm_k_stack;
    addr_t shared_mem_addr;
    addr_t phy_code_addr;
    int proc_code_mem_pages;
    TRAPFRAME *trapframe;
    CONTEXT proc_context;

    enum PROC_PRIORITY priority;

    char proc_name[30];

} PROC;

typedef struct _PROC_LIST{
    PROC *procs[1000];
    int size;
    int idx;
} PROC_LIST;

/**
 * @brief CPU Related Defines.
 * 
 */
#define CPU_NUM 1
typedef struct _CPU
{
    int cpu_id;
    int slk_cnt;
    int interrupt_enabled;
    isa_reg_t reg_list[REGISTER_NUMBERS];
    CONTEXT context;
    PROC *proc;
} CPU;

/**
 * @brief Virtual Memory Related Defines.
 * 
 */
#define SV39





#define VM_MAP_SUCCESS                        (0)
#define VM_MAP_FAILED                         (-1)

#define VM_K_STACK_ADDR(pid)                  ((VM_TRAMPOLINE_ADDR - ((pid) + 1) * 2 * PAGE_SIZE))

/**
 * @brief Memory Allocate Related Defines.
 * 
 */








typedef struct _HEAP_MEM_BLK{
    int blk_free_space;
    char blk_cell[SQRT_PAGE_SIZE][SQRT_PAGE_SIZE / bitof(char)];
    struct _HEAP_MEM_BLK *next;
} HEAP_MEM_BLK;

/**
 * @brief Spinlock Related Defines.
 * 
 */
#define GENERAL_SPINLOCK_NUM        5
#define SLK_LOCKED                            1
#define SLK_UNLOCKED                          0

typedef struct SPINLOCK {
    char *slk_name;
    int locked;
    CPU *slk_owner;
} SPINLOCK;



#endif /* __RISCV_TYPE_DEFS_H__ */