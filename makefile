NAME   = lpc2148

CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld -v
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
OD		= arm-none-eabi-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g -mcpu=arm7tdmi-s
AFLAGS  = -ahls -mapcs-32 -o startup.o 
LFLAGS  =  -Map LED.map -T2148.cmd
CPFLAGS = -O binary
HEXFLAGS = -O ihex
ODFLAGS	= -x --syms

all: test

clean:
	-rm startup.lst startup.o LED.o LED.out LED.map LED.dmp LED.bin

test: LED.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) LED.out LED.bin
	$(OD) $(ODFLAGS) LED.out > LED.dmp
	@echo "...building hex"
	$(CP) $(HEXFLAGS) LED.out LED.hex

LED.out: startup.o LED.o 2148.cmd
	@ echo "..linking"
	$(LD) $(LFLAGS) -o LED.out  startup.o LED.o

startup.o: Startup.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) Startup.s > startup.lst

LED.o: LED.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) LED.c
