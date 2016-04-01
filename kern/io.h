/* desactive les interruptions */
#define cli asm("cli"::)

/* reactive les interruptions */
#define sti asm("sti"::)

/* ecrit un octet sur un port */
#define outb(port,value) \
	asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value));

/* ecrit un octet sur un port et marque une temporisation  */
#define outbp(port,value) \
	asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));

/* lit un octet sur un port */
#define inb(port) ({    \
	unsigned char _v;       \
	asm volatile ("inb %%dx, %%al" : "=a" (_v) : "d" (port)); \
        _v;     \
})
