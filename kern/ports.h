#define COM1 0x3F8
#define COM2 0x2F8
#define LPT1 0x378

void open_serial(int port, int baud);
void write_serial(int port, char data);
int serial_available(int port);
char read_serial(int port);
char* rte_serial(int port);
void write_parallel(int port, char data);
char read_parallel(int port);
void control_parallel(int port, int control);
char status_parallel(int port);



