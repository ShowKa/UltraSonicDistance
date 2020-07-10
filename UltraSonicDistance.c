#include <machine.h>
#include "iodefine.h"
#include "vect.h"

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
	int start, end, diff;
	char isStartTimer = isStart_TIMER();
	// TPU9 start
	TPU9.TCR.BIT.TPSC = 3;
	TPU9.TGRA = 50000;
	TPU9.TCNT = 0;
	TPUB.TSTR.BIT.CST9 = 1;
	start = TPU9.TCNT;
	while(PORTD.PIDR.BIT.B0 == 1);
	end = TPU9.TCNT;
	diff = end - start;
	if (isStartTimer) {
		start_TIMER();
	}
}
