include config.mk

AA_ARCH_DIRS := drivers
AA_ARCH_PATH := arch/$(AA_ARCH)

DIRS := ipc irq lib mm object sched syscall \TH)/,$(ARCH_DIRS)) \
        $(PLAT_PATH) $(addprefix $(PLAT_PATH)/,$(PLA
		$(ARCH_PATH) $(addprefix $(ARCH_PAT_DIRS)) \
        $(SPD_PATH)
C_SRCS := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
C_OBJS := $(C_SRCS:%.c=%.c.o)
ASM_SRCS += $(foreach dir,$(DIRS),$(wildcard $(dir)/*.S))
ASM_SRCS += incbin_promgr_bin.S
ASM_OBJS := $(ASM_SRCS:%.S=%.S.o)

INIT_C_SRCS := $(wildcard arch/$(CHCORE_ARCH)/boot/$(CHCORE_PLAT)/init/*.c)
INIT_C_OBJS := $(INIT_C_SRCS:%.c=%.c.o)
INIT_ASM_SRCS := $(wildcard arch/$(CHCORE_ARCH)/boot/$(CHCORE_PLAT)/init/*.S) \
                 $(wildcard arch/$(CHCORE_ARCH)/trustzone/spd/$(CHCORE_SPD)/init/*.S)
INIT_ASM_OBJS := $(INIT_ASM_SRCS:%.S=%.S.o)

ALL_OBJS := $(C_OBJS) $(ASM_OBJS) $(INIT_C_OBJS) $(INIT_ASM_OBJS)
ALL_DEPS := $(ALL_OBJS:.o=.d)


all : army-ant.bin army-ant.elf create_dir


army-ant.bin : army-ant.elf
	@echo "Making binary..."
	@${OBJCOPY} army-ant.elf -O binary army-ant.bin	

army-ant.elf : ${OBJS}
	@echo "Linking ELF..."
	@${LD} -z max-page-size=4096 -L${BSP_DIR} -T ${BSP_DIR}/linkld.ld $^ -o $@
	@echo "Making objdump to army-ant.txt..."
	@${OBJDUMP} -d army-ant.elf > army-ant.txt

create_dir :
	@echo "Making obj directories..."
	@mkdir -p arch/${ARCH}/obj
	@mkdir -p ${BSP_DIR}/obj
	@mkdir -p kernel/obj
	@mkdir -p console/obj
	@mkdir -p fs/obj
	@mkdir -p driver/obj
	@mkdir -p lib/obj
	@echo "Obj directories created."

.PHONY : clean mkdir
clean : 
	@echo "Cleaning..."
	@rm -f *.o *.elf *.d *.bin army-ant.txt *.lds ${OBJS} ${D} ${BSP_DIR}/*.lds
	