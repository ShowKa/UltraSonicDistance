#include <machine.h>
#include "iodefine.h"
#include "vect.h"
#include "sciDrv.h"

//グローバル変数宣言
extern unsigned char SCI0_RX_DATA;
extern unsigned char SCI0_RX_FLAG;
int distance; //cm

void setup();
void trigger();

void main() {
	//STARTメッセージ表示
	unsigned char Start_Message[] = "\n\rSCI Start\n\r";
	setup();
	pPrint_SCI( Start_Message, 100);
	while(1) {
		trigger();
		delay_ms(50);
	}
	while(1);
}

void setup() {
	initSCI0();
	initLed();
	initPort9();
	init_TPU2();
	init_TPU9();
	initIRQ();
	setpsw_i();
}

// trigger pulse: width=10us
void trigger() {
	setPort9(0x01);
	delay_us(10);
	setPort9(0x00);
}

// catch output Echo
void Excep_ICU_IRQ0(void){
	int span;
	char isStartTimer = isStart_TIMER();
	start_TPU9();
	while(PORTD.PIDR.BIT.B0 == 1);
	span = getTimeSpan_TPU9();
	distance = span / 58;
	if (isStartTimer) {
		start_TIMER();
	}
}
