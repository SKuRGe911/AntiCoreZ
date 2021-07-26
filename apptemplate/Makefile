# MAKEFILE

PROJECT_NAME					=	APP
OUTPUT_ROM						=	APP

BUILD_DIR						=	build

TOOLCHAIN_PREFIX				=	riscv64-unknown-elf-
#TOOLCHAIN_PREFIX				=	riscv-none-embed-

GERANIUMLIB						=	../gcclib/geranium.a
GERANIUMLINKSCRIPT				=	../gcclib/geranium.lds

GCC								=	$(TOOLCHAIN_PREFIX)gcc
GPP								=	$(TOOLCHAIN_PREFIX)g++
OBJCOPY							=	$(TOOLCHAIN_PREFIX)objcopy
LD								=	$(TOOLCHAIN_PREFIX)ld

PROJECT_FILES					=	$(BUILD_DIR)/main.o \
									$(BUILD_DIR)/command.o

# set to 4 for simulation 18 for real
FIRMWARE_COUNTER_BITS			=	18

CFLAGS += --param inline-min-speedup=0
CFLAGS += -W
CFLAGS += -Wall
CFLAGS += --std=c99
#CFLAGS += --std=gnu99
#CFLAGS += --std=c17
#CFLAGS += --std=gnu++17
CFLAGS += -O0
#CFLAGS += -lgcc
CFLAGS += -lm
CFLAGS += -mabi=ilp32
CFLAGS += -march=rv32im
CFLAGS += -falign-functions=4
CFLAGS += -falign-labels=4
CFLAGS += -falign-loops=4
CFLAGS += -falign-jumps=4
CFLAGS += -fdata-sections
CFLAGS += -ffunction-sections
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -fno-diagnostics-show-caret
CFLAGS += -Wno-sign-compare
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-sizeof-pointer-memaccess
CFLAGS += -static
CFLAGS += -mstrict-align
#CFLAGS += -v
#CFLAGS += -ffreestanding
#CFLAGS += -ffast-math
CFLAGS += -nostartfiles
#CFLAGS += -Wl,--script=firmware.lds
#CFLAGS += -flto
#CFLAGS += -nostdlib
#CFLAGS += -nodefaultlibs
CFLAGS += -lgloss
#CFLAGS += -mpreferred-stack-boundary=4
CFLAGS += -mno-explicit-relocs
#CFLAGS += -mno-relax
CFLAGS += -mno-riscv-attribute
CFLAGS += -DF_CPU=113280000
CFLAGS += -DSHIFT_COUNTER_BITS=$(FIRMWARE_COUNTER_BITS)

all: $(PROJECT_NAME).rom Makefile $(BUILD_DIR) ../$(OUTPUT_ROM).ROM A:/$(OUTPUT_ROM).ROM

## -------------------
## firmware generation
#--specs=nano.specs

A:/$(OUTPUT_ROM).ROM: $(PROJECT_NAME).rom
	cp $(PROJECT_NAME).rom A:/$(OUTPUT_ROM).ROM

../$(OUTPUT_ROM).ROM: $(PROJECT_NAME).rom
	cp $(PROJECT_NAME).rom ../$(PROJECT_NAME).ROM

$(PROJECT_NAME).elf: $(PROJECT_FILES) Makefile $(GERANIUMLINKSCRIPT) $(GERANIUMLIB)
	$(GCC) $(CFLAGS) --specs=nosys.specs -Wa,-aslh -o $@ $(PROJECT_FILES) $(GERANIUMLIB) -Wl,-Bstatic,-T,$(GERANIUMLINKSCRIPT),-Map,$(PROJECT_NAME).map,--strip-debug > $(PROJECT_NAME).S

$(PROJECT_NAME).rom: $(PROJECT_NAME).bin
	cp $(PROJECT_NAME).bin $(PROJECT_NAME).rom

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(OBJCOPY) -O binary $< $@ --remove-section=.comment --remove-section=.note
	chmod -x $@

## -------------------------------------------------------------------------------------------------------------------------##

$(BUILD_DIR)/main.o: ./main.c ../geranium.h
	$(GCC) $(CFLAGS) -o $@ -c ./main.c

$(BUILD_DIR)/command.o: ./command.c ../geranium.h
	$(GCC) $(CFLAGS) -o $@ -c ./command.c

## -------------------------------------------------------------------------------------------------------------------------##

clean:
	rm -f $(PROJECT_NAME).elf $(PROJECT_NAME).map $(PROJECT_NAME).bin $(PROJECT_NAME).rom $(PROJECT_NAME).S ../$(OUTPUT_ROM).ROM
	rm -f $(BUILD_DIR)/*.o

.PHONY: all clean
