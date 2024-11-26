# MakeFile

common_objects  =

cpu             = MSP430G2553

cflags          = -MMCU=${cpu} -i../H -l/OPT/TI/MSP430_GCC/INCLUDE

# Switch the compiler

cc              = MSP430-ELF-GCC

as              = MSP430-ELF-AS

ALL: BUTTON_BUZZER.ELF

# Additional rules for files

BUTTON_BUZZER.ELF: ${common_objects} P1_INTERRUPT_HANDLER.O LED.O SWITASDASDASKLKASa# Makefile configuration

COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

# Switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button_buzzer.elf

# Additional rules for files

button_buzzer.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led.o switches.o buzzer.o buttonMain.o ../lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: button_buzzer.elf
	msp430loader.sh button_buzzer.elf
clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
buzzerMain.c: buzzer.h

