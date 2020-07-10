#include	"iodefine.h"

// portA LED
#define  LED_IO PORTA.PDR.BYTE
#define  LED PORTA.PODR.BYTE

void turnOnLed(char status);
void turnOnAllLed();
void turnOffAllLed(void);

void initLed() {
	LED_IO = 0xff;
}

void turnOnAllLed(void)
{
	turnOnLed(0xff);
}

void turnOffAllLed(void)
{
	turnOnLed(0x00);
}

void turnOnLed(char status)
{
	LED = status;
}