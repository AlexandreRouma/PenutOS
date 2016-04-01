OBJ=floppyA 

all: $(OBJ) 

floppyA: bootsect kernel
	cat boot/bootsect kern/kernel /dev/zero | dd of=floppyA.img bs=4096 count=2880

bootsect: 
	make -C boot

kernel: 
	make -C kern

clean:
	rm -f $(OBJ) *.o bochs.log
	make -C boot clean
	make -C kern clean
