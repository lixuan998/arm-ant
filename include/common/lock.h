#pragma once

#include <common/stdint.h>
#include <common/stddef.h>
#include <common/error.h>

typedef struct _spinlock {
    union {
        struct {
            uint32_t owner;
            uint32_t next;
        };
        uint64_t slock;
    };
} spinlock;

void spinlock_init(spinlock *splock);
void spinlock_lock(spinlock *splock);
void spinlock_unlock(spinlock *splock);
error_t spinlock_try_lock(spinlock *splock);