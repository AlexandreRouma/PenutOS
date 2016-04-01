#include "ports.h"
#include "io.h"
#include "str_utils.h"

int int_rcv = 0;

void open_serial(int port, int baud){
	int br = 115200 / baud;
	outb(port + 1, 0x00);
	outb(port + 3, 0x80);
    outb(port + 0, br);
	outb(port + 1, 0x00);
	outb(port + 3, 0x03);
    outb(port + 2, 0xC7);
    outb(port + 4, 0x0B);
}

void write_serial(int port, char a){
	while (transmit_empty() == 0);
    outb(port,a);
}

int serial_available(int port){
	return inb(port + 5) & 1;
}

char read_serial(int port){
	while (serial_available(port) == 0);
	return inb(port);
}

char* rte_serial(int port){
	char* ret = "";
	int i = 0;
	while (serial_available(port) == 1){
		char c = read_serial(port);
		ret[i] = c;
		i++;
	}
	return ret;
}

void write_parallel(int port, char data){
	outb(port, data);
}

char read_parallel(int port){
	return inb(port);
}

void control_parallel(int port, int control){
	outb(port + 2, control);
}

char status_parallel(int port){
	return inb(port + 1);
}

int transmit_empty(int port) {
   return inb(port + 5) & 0x20;
}

void isr_coma_int(void){
	int_rcv = 1;
}

void isr_comb_int(void){
	int_rcv = 1;
}