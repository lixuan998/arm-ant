#pragma once

#include <common/stdint.h>

/**
 * @brief CSR Related Defines.
 * 
 */
#define REGISTER_NUMBERS                      32

#define USER_MODE_CODE                        0
#define SUPERVISOR_MODE_CODE                  1
#define HYPERVISOR_MODE_CODE                  2
#define MACHINE_MODE_CODE                     3

#define MSTATUS_SIE_OFFSET                    1
#define MSTATUS_SIE_MASK                      1UL << MSTATUS_SIE_OFFSET
#define MSTATUS_MIE_OFFSET                    3
#define MSTATUS_MIE_MASK                      1UL << MSTATUS_MIE_OFFSET
#define MSTATUS_SPIE_OFFSET                   5
#define MSTATUS_SPIE_MASK                     1UL << MSTATUS_SPIE_OFFSET
#define MSTATUS_MPIE_OFFSET                   7
#define MSTATUS_MPIE_MASK                     1UL << MSTATUS_MPIE_OFFSET
#define MSTATUS_SPP_OFFSET                    8
#define MSTATUS_SPP_MASK                      1UL << MSTATUS_SPP_OFFSET
#define MSTATUS_MPP_OFFSET                    11UL
#define MSTATUS_MPP_MASK                      3UL << MSTATUS_MPP_OFFSET

#define SSTATUS_SIE_OFFSET                    1
#define SSTATUS_SIE_MASK                      1UL << SSTATUS_SIE_OFFSET
#define SSTATUS_SPIE_OFFSET                   5
#define SSTATUS_SPIE_MASK                     1UL << SSTATUS_SPIE_OFFSET
#define SSTATUS_SPP_OFFSET                    8
#define SSTATUS_SPP_MASK                      (1UL << SSTATUS_SPP_OFFSET)

/**
 * @brief Interrupt Related Defines.
 * 
 */
#define SIE_SSIE_OFFSET                       1
#define SIE_SSIE_MASK                         1UL << SIE_SSIE_OFFSET
#define SIE_STIE_OFFSET                       5
#define SIE_STIE_MASK                         1UL << SIE_STIE_OFFSET
#define SIE_SEIE_OFFSET                       9
#define SIE_SEIE_MASK                         1 << SIE_SEIE_OFFSET

#define SCAUSE_INTERRUPT                      1UL << 63
#define SCAUSE_EXCEPTION                      0UL << 63
#define SCAUSE_EXCEPTION_CODE_MASK            0x7FFFFFFFFFFFFFFFUL
#define SCAUSE_SOFTWARE_INTERRUPT             1
#define SCAUSE_TIMER_INTERRUPT                5
#define SCAUSE_EXTERNAL_INTERRUPT             9

#define SCAUSE_INST_ADDR_MISALIGN             0
#define SCAUSE_INST_ACCESS_FAULT              1
#define SCAUSE_ILLEGAL_INST                   2
#define SCAUSE_BREAKPOINT                     3
#define SCAUSE_LOAD_ADDR_MISALIGN             4
#define SCAUSE_LOAD_ACCESS_FAULT              5
#define SCAUSE_STORE_AMO_ADDR_MISALIGN        6
#define SCAUSE_STORE_AMO_ACCESS_FAULT         7
#define SCAUSE_ECALL_U                        8
#define SCAUSE_ECALL_S                        9
#define SCAUSE_INST_PAGE_FAULT                12
#define SCAUSE_LOAD_PAGE_FAULT                13
#define SCAUSE_STORE_AMO_PAGE_FAULT           15

typedef uintptr_t addr_t;