#include "iodefine.h"
#include <machine.h>
#include "vect.h"

// �v���g�^�C�v
void initIRQ();
void initIRQ() {
	IEN(ICU, IRQ0) = 0;
	IEN(ICU, IRQ1) = 0;
	// PORT��IRQ�Ƃ��Đݒ�
	PORTD.PDR.BIT.B0 = 0;
	PORTD.PMR.BIT.B0 = 0;
	PORTD.PDR.BIT.B1 = 0;
	PORTD.PMR.BIT.B1 = 0;
	
	// �v���e�N�g����
	MPC.PWPR.BYTE &= ~0x80;
	MPC.PWPR.BYTE |= 0x40;
	
	MPC.PD0PFS.BYTE = 0x40;
	MPC.PD1PFS.BYTE = 0x40;
	
	// �ăv���e�N�g
	MPC.PWPR.BYTE &= ~0x40;
	MPC.PWPR.BYTE |= 0x80;
	
	// IRQ�̐ݒ�
	//���o�F1:������, 2:�����
	ICU.IRQCR[0].BIT.IRQMD = 0x02;
	ICU.IRQCR[1].BIT.IRQMD = 0x02;
	
	// �D��x�̐ݒ�
	IPR(ICU, IRQ0) = 6;
	IPR(ICU, IRQ1) = 6;
	
	IR(ICU, IRQ0) = 0x00;
	IR(ICU, IRQ1) = 0x00;
	
	IEN(ICU, IRQ0) = 1;
	IEN(ICU, IRQ1) = 1;

}
