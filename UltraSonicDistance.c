#include <machine.h>

void main() {
	initLed();
	init_TPU2();
	setpsw_i();
	while(1) {
		delay_ms(500);
		turnOnAllLed();
		delay_ms(500);
		turnOffAllLed();
	}
	while(1);
}
