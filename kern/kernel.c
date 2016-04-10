#include "types.h"
#include "lib.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "random.h"
#include "str_utils.h"
#include "rtc.h"
#include "ports.h"
#include "shell.h"
#include "pit.h"

void init_pic(void);
int main(void);
char* logo = "                                                    \n                                                    \n                                                    \n                                                    \n                                                    \n               ```````              ````            \n           ..-:--:::-:::..`  ```..-----:::-.`       \n        `-:::/:::::/oooo+//-.::::::://:-///++:.     \n      `--:///++oooo+++++/+o/::/+//++++o+so/+/++`    \n     `..-:///+ososososooosss+o++ooo++o+oso+++//`    \n     ://+++ooo++oo+++oo+oooo+o/+/++oyyssso+++:`     \n     -+++ooo+ososhsoooooossssssossysoooooo+/.       \n      .+oooo++++ooooossssyhysssoooosoooss+-         \n       `:oyssoyyyhhdmdyyyshmmdhysyyyhhyyo/::-..`    \n       `.:/oossssssssoo+++//++oossso++//::--..``    \n                                                    \n                                                    \n                                                    \n";
int color = 0;

void _start(void)
{	
    
	
    hide_cursor();
    scrollup(26);

	kY = 0;
	kattr = 0x03;
    print("Kernel Loaded!\n\n");
    
    kattr = 0x07;

    print("loading IDT... ");
	init_idt();
    print("[");
    kattr = 0x02;
    print("OK");
    kattr = 0x07;
	print("]\n");
        
    print("loading PIC... ");
	init_pic();
    print("[");
    kattr = 0x02;
	print("OK");
        kattr = 0x07;
	print("]\n");;
	
	print("loading PIT... ");
	set_pit_freq(1000);
    print("[");
    kattr = 0x02;
	print("OK");
        kattr = 0x07;
	print("]\n");;

	/* Initialisation de la GDT et des segments */
    print("loading GDT... ");
	init_gdt();
    print("[");
    kattr = 0x02;
	print("OK");
    kattr = 0x07;
	print("]\n");
    //scrollup(26);
    asm("sti");
	main();
}


	
int main(void)
{
	scrollup(26);
	kattr = 0x0B;
	print("Penut OS !!!");
	kattr = 0x0E;
	print(logo);
	kattr = 0x0B;
	print("By: Alexandre Rouma");
	sleep(2000);
	scrollup(26);
	kX = 0;
	kY = 0;
	kattr = 0x0B;
	print("   **************************************************************************\n");
	print("   *                                    PenutOS                             *\n");
	print("   *                                  Version 1.0                           *\n");
	print("   *  By: Alexandre Rouma                                                   *\n");
	print("   **************************************************************************");
	kattr = 0x02;
	print("\n");
	print("\n");
	shell();
	
}
