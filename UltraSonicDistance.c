#include <machine.h>
#include "iodefine.h"
#include "vect.h"
#include "sciDrv.h"

//�O���[�o���ϐ��錾
extern unsigned char SCI0_RX_DATA;
extern unsigned char SCI0_RX_FLAG;
int distance; //cm

void setup();
void trigger();

void main() {
	//START���b�Z�[�W�\��
	unsigned char Start_Message[] = "\n\rSCI Start\n\r";
	setup();
	pPrint_SCI( Start_Message, 100);
	while(1) {
		if (SCI0_RX_FLAG == 1) {
			if (SCI0_RX_DATA == 'd') {
				// show distance by SCI
				unsigned char distance_message[7];
				distance_message[0] = distance / 1000 % 10 + '0';
				distance_message[1] = distance / 100 % 10 + '0';
				distance_message[2] = distance / 10 % 10 + '0';
				distance_message[3] = distance / 1 % 10 + '0';
				distance_message[4] = 'c';
				distance_message[5] = 'm';
				distance_message[6] = '\n\r';
				pPrint_SCI( distance_message, 7);
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
	initPort9();
	init_TPU2();
	init_TPU9();
	initIRQ();
	init_CMT0();
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
	int span, i;
	char isStartTimer = isStart_TIMER();
	start_TPU9();
	// wait until interupted signal will be low.
	i = 0;
	while(PORTD.PIDR.BIT.B0 == 1) {
		// �����ނ�4���[�g�����Ńu���C�N������B��������̓e�L�g�[�Ȃ̂Ńo�O�邩���B
		if (++i > 131072) break;
	}
	// get distance
	span = getTimeSpan_TPU9();
	distance = span / 58;
	// restart timer
	if (isStartTimer) {
		start_TIMER();
	}
}

// CMT0 �����ݏ���
// trigger��60us���Ɏ��{�����悤�ɂ���B
void Excep_CMT0_CMI0(void) {
	char isStartTimer = isStart_TIMER();
	trigger();
	if (isStartTimer) {
		start_TIMER();
	}
}
