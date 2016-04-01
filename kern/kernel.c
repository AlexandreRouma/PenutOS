#include "types.h"
#include "lib.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "random.h"
//#include "kbd.h"
#include "str_utils.h"
#include "rtc.h"
#include "ports.h"
#include "shell.h"

void init_pic(void);
int main(void);

void _start(void)
{
    hide_cursor();
    scrollup(26);

	kY = 0;
	kattr = 0x03;
    print("Kernel Loaded!\n\n");
    
    kattr = 0x07;

    print("loading IDT ");
	init_idt();
    print("[");
    kattr = 0x02;
    print("OK");
    kattr = 0x07;
	print("]\n");
        
    print("loading PIC ");
	init_pic();
    print("[");
    kattr = 0x02;
	print("OK");
        kattr = 0x07;
	print("]\n");;
	
	print("loading PIT ");
	set_pit_freq(1000);
    print("[");
    kattr = 0x02;
	print("OK");
        kattr = 0x07;
	print("]\n");;

	/* Initialisation de la GDT et des segments */
    print("loading GDT ");
	init_gdt();
    print("[");
    kattr = 0x02;
	print("OK");
    kattr = 0x07;
	print("]\n");
    //scrollup(26);
    asm("sti");
	print("\n");
	print("\n");
	main();
}

int main(void)
{
	shell();
}