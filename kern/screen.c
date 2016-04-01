#include "types.h"
#include "io.h"

#define __SCREEN__
#include "screen.h"



void scrollup(unsigned int n)
{
	unsigned char *video, *tmp;

	for (video = (unsigned char *) RAMSCREEN;
	     video < (unsigned char *) SCREENLIM; video += 2) {
		tmp = (unsigned char *) (video + n * 160);

		if (tmp < (unsigned char *) SCREENLIM) {
			*video = *tmp;
			*(video + 1) = *(tmp + 1);
		} else {
			*video = 0;
			*(video + 1) = 0x07;
		}
	}

	kY -= n;
	if (kY < 0)
		kY = 0;
}

void putcar(uchar c)
{
	unsigned char *video;

	if (c == 10) {		/* CR-NL */
		kX = 0;
		kY++;
	} else if (c == 9) {	/* TAB */
		kX = kX + 8 - (kX % 8);
	} else if (c == 13) {	/* CR */
		kX = 0;
	} else {
		video = (unsigned char *) (RAMSCREEN + 2 * kX + 160 * kY);
		*video = c;
		*(video + 1) = kattr;

		kX++;
		if (kX > 79) {
			kX = 0;
			kY++;
		}
	}

	if (kY > 24)
		scrollup(kY - 24);
}

void print(char *string)
{
	while (*string != 0) {
		putcar(*string);
		string++;
	}
}

void dump(uchar* addr, int n)
{
	char c1, c2;
	char *tab = "0123456789ABCDEF";

	while(n--) {
		c1 = tab[(*addr & 0xF0)>>4];
		c2 = tab[*addr & 0x0F];
		addr++;
		putcar(c1);
		putcar(c2);
	}
}

void move_cursor(u8 x, u8 y)
{
	u16 c_pos;

	c_pos = y * 80 + x;

	outb(0x3d4, 0x0f);
	outb(0x3d5, (u8) c_pos);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (u8) (c_pos >> 8));
}

void show_cursor(void)
{
	move_cursor(kX, kY);
}

void hide_cursor(void)
{
	move_cursor(-1, -1);
}
