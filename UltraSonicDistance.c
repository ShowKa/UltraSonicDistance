#include <machine.h>

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

void trigger() {
	setPort9(0x01);
	delay_us(10);
	setPort9(0x00);
}

void setup() {
	initLed();
	initPort9();
	init_TPU2();
	initIRQ();
	setpsw_i();
}