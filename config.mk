TOOLCHAIN_DIR := /home/climatex/tools/xuantie_toolchain/bin
TOOLCHAIN=riscv64-unknown-linux-gnu
LINKLD := linkld.ld

CC := ${TOOLCHAIN_DIR}/$(TOOLCHAIN)-gcc
LD := ${TOOLCHAIN_DIR}/$(TOOLCHAIN)-ld
OBJCOPY := ${TOOLCHAIN_DIR}/$(TOOLCHAIN)-objcopy
OBJDUMP := ${TOOLCHAIN_DIR}/$(TOOLCHAIN)-objdump

CFLAGS = -Wall -O -fno-omit-frame-pointer -ggdb -gdwarf-2
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -I.
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
CFLAGS += -march=rv64g -nostdinc

AA_ARCH = riscv64
AA_BOARD = nezha-d1-h