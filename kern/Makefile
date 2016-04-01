OBJ=kernel
CC=gcc -Wall

all: $(OBJ) 

kernel: kernel.o screen.o lib.o gdt.o idt.o interrupt.o int.o pic.o random.o pit.o str_utils.o rtc.o ports.o speaker.o shell.o
	ld --oformat binary -Ttext 1000 $^ -o $@

int.o: int.asm
	nasm -f elf -o $@ $^ 

.o: .c 
	$(CC) -c $^

clean:
	rm -f $(OBJ) *.o
