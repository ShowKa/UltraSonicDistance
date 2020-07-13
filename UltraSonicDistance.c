#include <machine.h>
#include "iodefine.h"
#include "vect.h"

int distance; //cm

void setup();
void trigger();

void main() {
	setup();
	while(1) {
		trigger();
		delay_ms(50);
	}
	while(1);
}

void setup() {
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
