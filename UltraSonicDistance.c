#include <machine.h>
#include "sciDrv.h"
#include "vect.h"

//グローバル変数宣言
extern int DISTANCE;
extern unsigned short TEMPERATURE;

void setup();
int convertTemp2Duty(unsigned short temperature);

void main() {
	setup();
	while(1);
}

// 初期化
void setup() {
	initSCI0();
	initLed();
	init_US_TRIGGER();
	init_TPU2();
	init_TPU9();
	initIRQ();
	init_CMT0();
	init_CMT1();
	init_CMT2();
	init_S12AD();
	init_TPU0_PWM();
	LCD_init();
	setpsw_i();
}

// CMT割込
// 温度によりPWM duty比調整
// ただし遮蔽物との距離が違い場合、PWM停止
void Excep_CMT1_CMI1(void){
	int duty;
	if (DISTANCE < 100) {
		// stopPWM0_EMERGENCY();
		stopPWM0();
	} else {
		duty = convertTemp2Duty(TEMPERATURE);
		PWM_duty(duty);
	}
}

// CMT割込
// LCDに距離と温度を表示する
void Excep_CMT2_CMI2(void) {
	static unsigned char message[7];
	LCD_clear();
	message[0] = DISTANCE / 1000 % 10 + '0';
	message[1] = DISTANCE / 100 % 10 + '0';
	message[2] = DISTANCE / 10 % 10 + '0';
	message[3] = DISTANCE / 1 % 10 + '0';
	message[4] = 'c';
	message[5] = 'm';
	message[6] = 0x00;
	LCD_locate(1, 1);
	LCD_putstr(message);
	message[0] = TEMPERATURE / 100 % 10 + '0';
	message[1] = TEMPERATURE / 10 % 10 + '0';
	message[2] = '.';
	message[3] = TEMPERATURE / 1 % 10 + '0';
	message[4] = 'c';
	message[5] = 0x00;
	LCD_locate(1, 2);
	LCD_putstr(message);
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
