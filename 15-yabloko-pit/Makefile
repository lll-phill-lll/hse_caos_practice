GDB=gdb
OBJCOPY=objcopy

ifeq ($(shell uname -s),Darwin)
AS=x86_64-elf-as
LD=x86_64-elf-ld
CC=x86_64-elf-gcc
GDB=x86_64-elf-gdb
OBJCOPY=x86_64-elf-objcopy
endif

CFLAGS = -fno-pic -ffreestanding -static -fno-builtin -fno-strict-aliasing \
		 -mno-sse \
		 -Wall -ggdb -m32 -Werror -fno-omit-frame-pointer
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
ASMFLAGS = -m32 -ffreestanding -c -g

ifeq ($(LLVM),on)
#AS=llvm-as
LD=PATH=/usr/local/opt/llvm/bin:$(PATH) ld.lld
CC=clang
CFLAGS += -target elf-i386
ASMFLAGS = -target elf-i386 -ffreestanding -c -g
LDKERNELFLAGS = --script=script.ld
endif

OBJECTS = kernel.o console.o drivers/vga.o drivers/uart.o drivers/keyboard.o drivers/timer.o \
	cpu/idt.o cpu/gdt.o cpu/swtch.o cpu/vectors.o lib/mem.o proc.o lib/string.o \
	fs/fs.o

run: image.bin
	qemu-system-i386 -drive format=raw,file=$< -serial mon:stdio

run-nox: image.bin
	qemu-system-i386 -nographic -drive format=raw,file=$< -serial mon:stdio

ejudge.sh: image.bin
	echo >$@ "#!/bin/sh"
	echo >>$@ "base64 -d <<===EOF | gunzip >image.bin"
	gzip <$^ | base64 >>$@
	echo >>$@ "===EOF"
	echo >>$@ "exec qemu-system-i386 -nographic -drive format=raw,file=image.bin -serial mon:stdio"
	chmod +x $@

diag:
	-uname -a
	-$(CC) --version
	-$(LD) -v
	-gcc --version
	-ld -v

debug-boot-nox: image.bin mbr.elf
	qemu-system-i386 -nographic -drive format=raw,file=$< -s -S &
	$(GDB) mbr.elf \
		-ex "set architecture i8086" \
		-ex "target remote localhost:1234" \
		-ex "break *0x7c00" \
		-ex "continue"

debug-boot: image.bin mbr.elf
	qemu-system-i386 -drive format=raw,file=$< -s -S &
	$(GDB) mbr.elf \
		-ex "set architecture i8086" \
		-ex "target remote localhost:1234" \
		-ex "break *0x7c00" \
		-ex "continue"

debug-server: image.bin
	qemu-system-i386 -drive format=raw,file=$< -s -S

debug-server-nox: image.bin
	qemu-system-i386 -nographic -drive format=raw,file=$< -s -S

debug: image.bin
	qemu-system-i386 -drive format=raw,file=$< -s -S &
	$(GDB) kernel.bin \
		-ex "target remote localhost:1234" \
		-ex "break _start" \
		-ex "continue"

debug-nox: image.bin
	qemu-system-i386 -nographic -drive format=raw,file=$< -s -S &
	$(GDB) kernel.bin \
		-ex "target remote localhost:1234" \
		-ex "break _start" \
		-ex "continue"

fs.img: kernel.bin tools/mkfs user/false user/greet user/div0
	tools/mkfs $@ $< user/false user/greet user/div0

LDFLAGS=-m elf_i386

user/%: user/%.o user/crt.o
	$(LD) $(LDFLAGS) -o $@ -Ttext 0x1000 $^

image.bin: mbr.bin fs.img
	cat $^ >$@

kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) $(LDKERNELFLAGS) -o $@ -Ttext 0x9000 $^

bootmain.o: bootmain.c
	$(CC) $(CFLAGS) -Os -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(ASMFLAGS) $^ -o $@

mbr.bin: mbr.elf tools/mbrpad
	$(OBJCOPY) -S -O binary -j .text $< $@
	tools/mbrpad $@

mbr.raw: mbr.o bootmain.o
	$(LD) -N -m elf_i386 -Ttext=0x7c00 --oformat=binary $^ -o $@

mbr.elf: mbr.o bootmain.o
	$(LD) -N -m elf_i386 -Ttext=0x7c00 $^ -o $@

clean:
	rm -f *.elf *.img *.bin *.raw *.o */*.o tools/mkfs ejudge.sh

tools/%: tools/%.c
	gcc -Wall -Werror -g $^ -o $@
