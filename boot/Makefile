OBJ=bootsect 

all: $(OBJ) 

bootsect: bootsect.asm
	nasm -f bin -o $@ $^ ;

clean:
	rm -f $(OBJ) *.o
