#include "iodefine.h"

#define LCD_RS		PORT6.PODR.BIT.B0
#define LCD_RW		PORT6.PODR.BIT.B1
#define LCD_E		PORT6.PODR.BIT.B2
#define LCD_DATA	PORTE.PODR.BYTE

void LCD_write(unsigned char data, unsigned short rs);
void LCD_init(void);
void LCD_clear(void);
void LCD_locate(unsigned char x, unsigned char y);
void LCD_putchar(char moji);
void LCD_putstr(char *str);

void LCD_write(unsigned char data, unsigned short rs) {
	// 0:controll / 1:data
	LCD_RS = rs;
	// 0:read
	LCD_RW = 0;
	delay_us(10);
	LCD_E = 1;
	delay_us(10);
	LCD_DATA = data;
	delay_us(10);
	LCD_E = 0;
	delay_us(10);
	LCD_DATA = 0;
	// 1:write
	LCD_RW = 1;
}

void LCD_init(void) {
	PORT6.PDR.BYTE = 0xFF;
	PORTE.PDR.BYTE = 0xFF;
	delay_ms(100);
	// function set
	LCD_write(0x38, 0);
	delay_us(50);
	LCD_write(0x38, 0);
	delay_us(50);
	// display on/off
	LCD_write(0x0C, 0);
	delay_us(50);
	// clear
	LCD_clear();
	// entry mode set
	LCD_write(0x06, 0);
}

void LCD_clear() {
	// clear
	LCD_write(0x01, 0);
	delay_ms(2);
}

void LCD_locate(unsigned char x, unsigned char y) {
	unsigned char ad, DDRAM_data;
	switch(y) {
		case 0x01: ad = x-1; break;
		case 0x02: ad = 0x40 + (x-1); break;
		case 0x03: ad = 0x14 + (x-1); break;
		case 0x04: ad = 0x54 + (x-1); break;
		default: return;
	}
	DDRAM_data = ad | 0x80;
	LCD_write(DDRAM_data, 0);
}

void LCD_putchar(char moji) {
	LCD_write(moji, 1);
}

void LCD_putstr(char *str) {
	while(*str) {
		LCD_putchar(*str);
		str++;
	}
}