#
# Makefile for the project AVR-OS version 0.01
#

SERIAL   = COM1
TARGET   = image

#F_CPU   = 7372800
F_CPU    = 16000000
MCU      = atmega128
ARCH     = m128

#
# Modules
#

KERNEL  = arch.o kernel.o
LIBS    =
DRIVERS =
FS      =
TASKS   = tasks.o main.o

OBJECTS = $(KERNEL) $(DRIVERS) $(FS) $(LIBS) $(TASKS)

#
# Compiler options
#

CC       = avr-gcc
CPP      = avr-g++
LD       = avr-ld
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
INCLUDES = -I"../include" -I "D:/Program Files/WinAVR/avr/include"
COMMON   = -mmcu=$(MCU)

CFLAGS   = $(COMMON) -D$(MCU) -DF_CPU=$(F_CPU)
CFLAGS  += -Wall -gdwarf-2 -O0 -fsigned-char
CFLAGS  += -Wp,-M,-MP,-MT,$(*F).o,-MF,dep/$(@F).d

ASMFLAGS = $(COMMON) -x assembler-with-cpp -Wa,-gdwarf2
LDFLAGS  = $(COMMON) -Wl,-Map=$(TARGET).map

HEX_FLASH_FLAGS   = -R .eeprom
HEX_EEPROM_FLAGS  = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0

#
# Build all
#

all: $(TARGET).elf $(TARGET).bin $(TARGET).hex $(TARGET).eep $(TARGET).lss

# Kernel

arch.o: ../arch/$(ARCH)/arch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

kernel.o: ../kernel/kernel.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

# Tasks

tasks.o: ../tasks/tasks.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

# Init.

main.o: ../init/main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

#
# Target
#

$(TARGET).elf: $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LIBDIRS) -o $(TARGET).elf

#
# .bin
#

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

#
# Output HEX, EPP, LSS files
#

%.hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(HEX_FLASH_FLAGS) $< $@

%.eep: $(TARGET).elf
	$(OBJCOPY) $(HEX_EEPROM_FLAGS) -O ihex $< $@

%.lss: $(TARGET).elf
	$(OBJDUMP) -h -S $< > $@

#
# Read/Write EEPROM memory
#

reeprom:
	avrdude -p $(MCU) -P $(SERIAL) -c jtag1slow -u -U eeprom:r:$(TARGET).eep:r

weeprom:$(TARGET).eep
	avrdude -p $(MCU) -P $(SERIAL) -c jtag1slow -u -U eeprom:w:$(TARGET).eep:r

#
# Image install to device
#

program:$(TARGET).hex
	avrdude -p $(MCU) -P $(SERIAL) -c jtag1slow -u -e -U flash:w:$(TARGET).hex

#
# Clean target
#

.PHONY: clean
clean:
	-rm -rf dep/*
	-rm -rf *.o
	-rm -rf $(TARGET).elf
	-rm -rf $(TARGET).bin
	-rm -rf $(TARGET).hex
	-rm -rf $(TARGET).lss
	-rm -rf $(TARGET).map
	-rm -rf $(TARGET).eep

#
# Other dependencies
#

-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
