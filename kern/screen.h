#include "types.h"

#ifdef __SCREEN__

#define RAMSCREEN 0xB8000
#define SIZESCREEN 0xFA0
#define SCREENLIM 0xB8FA0

char kX = 0;
char kY = 8;
char kattr = 0x07;


#else

extern char kX;
extern char kY;
extern char kattr;

#endif

void scrollup(unsigned int);
void putcar(uchar);
void print(char*);
void dump(uchar*, int);
void move_cursor(u8, u8);
void show_cursor(void);
void hide_cursor(void);

