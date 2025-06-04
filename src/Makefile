# must provide arch={x86/x86_64/arm32/arm64}

C_SOURCES = $(wildcard kernel/*.c driver/video/*.c cpu/*.c cpu/*/*.c util/*.c)
ASM_SOURCES = $(wildcard kernel/*.asm driver/video/*.asm cpu/*.asm cpu/*/*.asm util/*.asm)
HEADERS = ${C_SOURCES:.c=.h}
OBJ = ${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}
CFLAGS = -ffreestanding -fno-stack-protector -z execstack -no-pie -fno-pic
CC = x86_64-elf-gcc
GDB = x86_64-elf-gdb
LD = x86_64-elf-ld
ifeq ($(OS),Windows_NT)
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),MSYS_NT-10.0-22631)
  	$(info MSYS2 detected)
    host_os = linux
  else
    $(info Windows detected)
    host_os = windows
    SHELL = cmd
  endif
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    host_os = linux
  endif
endif

# set flags for compiler and linker (Bits and Architecture)
ifeq ($(arch),x86_64)
  CFLAGS += -D CPU=1 -mno-red-zone
  LDFLAGS = -m elf_x86_64
  NASMFLAGS = -dBits=64
else ifeq ($(arch),x86)
  CFLAGS += -m32 -D CPU=2
  LDFLAGS = -m elf_i386
  NASMFLAGS = -dBits=32
else ifeq ($(arch),arm64)
  $(error arm64 not implemented yet! please use x86 or x86_64)
else ifeq ($(arch),arm32)
  $(error arm32 not implemented yet! please use x86 or x86_64)
endif

# make sure host OS is supported!
ifndef host_os
  $(warning host_os not defined! targets will not compile!)
endif
ifndef arch
  $(warning arch not defined! please set target architecture)
endif

all: os-image.bin

os-image.bin: x86-boot/boot-sect.bin kitty.bin #TODO add fs.bin (file system)
ifeq ($(host_os),windows)
	copy /B x86-boot\boot-sect.bin+kitty.bin /B os-image.bin
else ifeq ($(host_os),linux)
	cat $^ > os-image.bin
endif

kitty.bin: kernel/kitty.o ${OBJ}
	${LD} ${LDFLAGS} -o $@ -Ttext 0x8000 $^ --oformat binary --entry kitty

kitty.elf: kernel/kitty.o ${OBJ}
	${LD} ${LDFLAGS} -o $@ -Ttext 0x8000 $^  --entry kitty

run: os-image.bin
ifeq ($(arch),x86_64)
	qemu-system-x86_64 -hda os-image.bin
else ifeq ($(arch),x86)
	qemu-system-i386 -fda os-image.bin
else ifeq ($(arch),arm64)
	qemu-system-aarch64 os-image.bin
else ifeq ($(arch),arm32)
	qemu-system-arm os-image.bin
endif

run_boot: x86-boot/boot-sect.bin
ifeq ($(arch),x86_64)
	qemu-system-x86_64 -hda x86-boot/boot-sect.bin
else ifeq ($(arch),x86)
	qemu-system-i386 -hda x86-boot/boot-sect.bin
else ifeq ($(arch),arm64)
	qemu-system-aarch64 x86_boot_loader/bootsect.bin
else ifeq ($(arch),arm32)
	qemu-system-arm x86_boot_loader/bootsect.bin
endif

debug: os-image.bin kitty.elf # TODO needs work, change it so that a variable is added for break points
#ifeq ($(host_os),windows)
	qemu-system-x86_64 -s -S -d int -fda os-image.bin
#else ifeq ($(host_os),linux)
#	qemu-system-x86_64 -s -S -fda os-image.bin &
#endif
##${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf" -ex "break *0x7c00" -ex "break main" -ex "c" -ex "c"

%.o: %.asm
ifeq ($(arch),x86_64)
	nasm $< -f elf64 -o $@
else ifeq ($(arch),x86)
	nasm $< -f elf -o $@
else ifeq ($(arch),arm64)
	nasm $< -f elf64 -o $@
else ifeq ($(arch),arm32)
	nasm $< -f elf -o $@
endif

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
ifeq ($(host_os),windows)
	del /S *.bin *.o *.elf
else ifeq ($(host_os),linux)
	rm -rf *.bin *.o *.elf
	rm -rf kernel/*.o x86-boot/*.bin x86-boot/*.o
endif
