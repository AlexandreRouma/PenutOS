#include "pit.h"
#include "io.h"

void set_pit_freq(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

int ticks = 0;
int count  = 0;

void sleep(int ms){
	ticks = 0;
	count = 1;
	while (ticks < ms){
		
	}
	ticks = 0;
}

void isr_clock_int(void)
{
	if (count == 1){
		ticks++;
	}
}