/*
*********************************
*            PenutOS            *
*             Shell             *
*                               *
* By: Alexandre Rouma           *
*********************************
*/


//Including all libraries
#include "types.h"
#include "lib.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "random.h"
#include "kbd.h"
#include "str_utils.h"
#include "rtc.h"
#include "ports.h"
#include "shell.h"

//Declaring all variables
int term_color = 2; //Terminal color
int lshift_enable; //Left-Shift pressed
int rshift_enable; //Right-Shift pressed
int alt_enable; //ALT pressed
int ctrl_enable; //CTRL pressed
char keyP = 0; //Key pressed keycode
int keyPrsd; //Key pressed caracter
int cmd_l = 0; //Command length
char cmd[40]; //Command

//Main shell loop
void shell(){
	int shell_running = 1;
	kattr = term_color;
    print("penut> ");
	show_cursor();
	while (1){
		if (keyPrsd){
			keyPrsd = 0;
			if (keyP == 0x0A){ //ENTER
				hide_cursor();
				print("\n");
				if (cmpac(cmd, "malou") == 1){//Just a joke with my friends xDDDDD: "malou"
					print("\n");
					kattr = 15;
					print("Bonjour messieux fidele, le nom de mon pere, c'est le nom du papa du savant de la republique Eddy malou, renaissence africaine comparrer la renac!");
					kattr = term_color;
					print("\n");
				}
				else if(cmpac(cmd, "test") == 1){ //Test command (insert you own code here ton test !!!): "test"
					
				}
				else if(cmpac(cmd, "colors") == 1){ //Show all the possible colors: "colors"
					print("\n");
					//------------------
					disp_colors();
					//------------------
					kattr = term_color;
				}
				else if(prefix("echo ", cmd) == 1){ //echo some text back: "echo [text]"
					print(substring(cmd,5,40));
				}
				else if(cmpac(cmd, "clear") == 1){ //Clear the shell: "clear"
					scrollup(26);
					kY = 0;
					goto no_new;
				}
				else if(cmpac(cmd, "help") == 1){ //Display the help menu: "help"
					print("\n");
					kattr = 5;
					print("-- HELP --\n");
					print("\n");
					print("clear    -   Clears teh screen\n");
					print("color    -   Change shell color\n");
					print("date     -   Show data\n");
					print("echo     -   Print a text to screen\n");
					print("help     -   Show this text\n");
					print("pread    -   Display the parallel port data\n");
					print("pwrite   -   Write to parallel port\n");
					print("reboot   -   Reboot the computer (NOT YET IMPLEMENTED)\n");
					print("shutdown -   Shutdown the computer (NOT YET IMPLEMENTED)\n");
					print("sread    -   Wait until data is received on a serial port and display it\n");
					print("swrite   -   Write to the serial port\n");
					print("time     -   Show time\n");					
					kattr = term_color;
				}
				else if(cmpac(cmd, "time") == 1){ //Show the time: "time"
					int h = getHour();
					int m = getMinute();
					int s = getSecond();
					if (h < 10){
						print("0");
						print(itoa(h));
					    print(":");
					}
					else{
						print(itoa(h));
						print(":");
					}
					
					if (m < 10){
						print("0");
						print(itoa(m));
						print(":");
					}
					else{
						print(itoa(m));
						print(":");
					}
					if (s < 10){
						print("0");
						print(itoa(s));
					}
					else{
						print(itoa(s));
					}
				}
				else if(cmpac(cmd, "date") == 1){ //Display date (and causes crash...): "date"
					print(itoa(getDay()));
					print("/");
					print(itoa(getMonth()));
					print("/");
					print(itoa(getYear()));
				}
				else if(cmpac(cmd, "") == 1){ //No command, just display an other line !
					goto no_new;
				}

				else if(prefix("color ", cmd) == 1){ //Change the text color: "color [text-color]"
					term_color = atoi(substring(cmd,6,8));
					kattr = term_color;
					print("\n");
					print("Shell color was changed !");
					print("\n");
				}
				else{
					kattr = 4;
					print("Command '");
					print(cmd);
					print("' not found !");
					kattr = term_color;
				}
				print("\n");
no_new:
				clear_cmd();
				print("penut> ");
				show_cursor();
			}
			else if(keyP == 0x08){ //back-space
				if (kX > 7){
					hide_cursor();
					cmd[cmd_l - 1] = 0;
					cmd_l = cmd_l - 1;
					kX = kX - 1;
					kattr = 7;
					putcar('\0');
					kattr = term_color;
					kX = kX - 1;
					show_cursor();
				}
			}
			else{ //normal-key
			    if (keyP == '\n'){
					
				}
				else{
					hide_cursor();
				    putcar(keyP);
				    cmd[cmd_l] = keyP;
					cmd_l++;
				    show_cursor();
				}
			}
		}
	}
}

void isr_kbd_int(void)
{
	uchar i;
	

	do {
		i = inb(0x64);
	} while ((i & 0x01) == 0);

	i = inb(0x60);
	i--;

	if (i < 0x80) {	// Key pressed
        
		switch (i) {
		case 0x29:
			lshift_enable = 1;
			break;
		case 0x35:
			rshift_enable = 1;
			break;
		case 0x1C:
			ctrl_enable = 1;
			break;
		case 0x37:
			alt_enable = 1;
			break;
		default:
		    keyPrsd = 1;
			keyP = kbdmap[i * 4 + (lshift_enable || rshift_enable)];
		}
	} else {		//Key released
		i -= 0x80;
		switch (i) {
		case 0x29:
			lshift_enable = 0;
			break;
		case 0x35:
			rshift_enable = 0;
			break;
		case 0x1C:
			ctrl_enable = 0;
			break;
		case 0x37:
			alt_enable = 0;
			break;
		}
	}
    
}

void clear_cmd(){ //Clear command routine
	int i = 0;
	while (i < 40){
		cmd[i] = 0;
		i++;
	}
	cmd_l = 0;
}

void disp_colors(){ //Show colors routine
	kattr = 0x10;
	print("   ");
	kattr = 0x01;
	print(" 1  - Blue\n");
	kattr = 0x20;
	print("   ");
	kattr = 0x02;
	print(" 2  - Green\n");
	kattr = 0x30;
	print("   ");
	kattr = 0x03;
	print(" 3  - Cyan\n");
	kattr = 0x40;
	print("   ");
	kattr = 0x04;
	print(" 4  - Red\n");
	kattr = 0x50;
	print("   ");
	kattr = 0x05;
	print(" 5  - Magenta\n");
	kattr = 0x60;
	print("   ");
	kattr = 0x06;
	print(" 6  - Orange\n");
	kattr = 0x70;
	print("   ");
	kattr = 0x07;
	print(" 7  - Light grey\n");
	kattr = 0x80;
	print("   ");
	kattr = 0x08;
	print(" 8  - Dark grey\n");
	kattr = 0x90;
	print("   ");
	kattr = 0x09;
	print(" 9  - Light blue\n");
	kattr = 0xA0;
	print("   ");
	kattr = 0x0A;
	print(" 10 - Light green\n");
	kattr = 0xB0;
	print("   ");
	kattr = 0x0B;
	print(" 11 - Light cyan\n");
	kattr = 0xC0;
	print("   ");
	kattr = 0x0C;
	print(" 12 - Light red\n");
	kattr = 0xD0;
	print("   ");
	kattr = 0x0D;
	print(" 13 - Light Magenta\n");
	kattr = 0xE0;
	print("   ");
	kattr = 0x0E;
	print(" 14 - Light Yellow\n");
	kattr = 0xF0;
	print("   ");
	kattr = 0x0F;
	print(" 15 - White\n");
}