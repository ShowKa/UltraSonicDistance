#include <machine.h>
#include "sciDrv.h"
#include "vect.h"

//グローバル変数宣言
extern unsigned char SCI0_RX_DATA;
extern unsigned char SCI0_RX_FLAG;
extern int DISTANCE;

void setup();
int convertTemp2Duty(unsigned short temperature);

void main() {
	//STARTメッセージ表示
	unsigned char Start_Message[] = "\n\rSCI Start\n\r";
	setup();
	pPrint_SCI( Start_Message, 100);
	while(1) {
		if (SCI0_RX_FLAG == 1) {
			if (SCI0_RX_DATA == 'd') {
				// show distance by SCI
				unsigned char message[8];
				message[0] = DISTANCE / 1000 % 10 + '0';
				message[1] = DISTANCE / 100 % 10 + '0';
				message[2] = DISTANCE / 10 % 10 + '0';
				message[3] = DISTANCE / 1 % 10 + '0';
				message[4] = 'c';
				message[5] = 'm';
				message[6] = '\r';
				message[7] = '\n';
				pPrint_SCI(message, 8);
			} else if (SCI0_RX_DATA == 't') {
				unsigned char message[7];
				unsigned short temperature = getTemperature();
				message[0] = temperature / 100 % 10 + '0';
				message[1] = temperature / 10 % 10 + '0';
				message[2] = '.';
				message[3] = temperature / 1 % 10 + '0';
				message[4] = 'c';
				message[5] = '\r';
				message[6] = '\n';
				pPrint_SCI(message, 7);
			}
			// reset
			SCI0_RX_FLAG = 0;
		}
	}
	while(1);
}

void setup() {
	initSCI0();
	initLed();
	init_US_TRIGGER();
	init_TPU2();
	init_TPU9();
	initIRQ();
	init_CMT0();
	init_CMT1();
	init_S12AD();
	init_TPU0_PWM();
	setpsw_i();
}

int convertTemp2Duty(unsigned short temperature) {
	if(temperature < 290) {
	    return 200;
	} else if(290 <= temperature && temperature < 320) {
	    return 200 + ( temperature - 290 ) * 25;
	} else {
	    return 950;
	}
}

void Excep_CMT1_CMI1(void){
	unsigned short temp;
	int duty;

	if (DISTANCE < 100) {
		stopPWM0_EMERGENCY();
		return;
	}

	temp =  getTemperature();
	duty = convertTemp2Duty(temp);
	PWM_duty(duty);
}
