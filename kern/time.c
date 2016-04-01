#include "time.h"

int ticks = 0;
int count  = 0;

void sleep(int ms){
	ticks = 0;
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