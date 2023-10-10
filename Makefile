C_FILES = ./build/kernel.o ./build/terminal/terminal.o ./build/idt/idt.o ./build/memory/memory.o
ASM_FILES = ./build/kernel.asm.o ./build/idt/idt.asm.o ./build/io/io.asm.o
FILES = $(ASM_FILES) $(C_FILES)
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/os.bin

./bin/os.bin: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./src/boot.asm
	nasm -f bin ./src/boot.asm -o ./bin/boot.bin

$(ASM_FILES): ./build/%.asm.o : ./src/%.asm
	nasm -f elf -g $< -o $@

$(C_FILES): ./build/%.o : ./src/%.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $< -o $@

run: ./bin/os.bin
	qemu-system-i386 -hda ./bin/os.bin

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/os.bin
	rm -rf ${FILES}
	rm -rf ./build/kernelfull.o

.PHONY: all clean run