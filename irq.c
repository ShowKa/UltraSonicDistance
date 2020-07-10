#include "iodefine.h"
#include <machine.h>
#include "vect.h"

// プロトタイプ
void initIRQ();
void initIRQ() {
	IEN(ICU, IRQ0) = 0;
	IEN(ICU, IRQ1) = 0;
	// PORTをIRQとして設定
	PORTD.PDR.BIT.B0 = 0;
	PORTD.PMR.BIT.B0 = 0;
	PORTD.PDR.BIT.B1 = 0;
	PORTD.PMR.BIT.B1 = 0;
	
	// プロテクト解除
	MPC.PWPR.BYTE &= ~0x80;
	MPC.PWPR.BYTE |= 0x40;
	
	MPC.PD0PFS.BYTE = 0x40;
	MPC.PD1PFS.BYTE = 0x40;
	
	// 再プロテクト
	MPC.PWPR.BYTE &= ~0x40;
	MPC.PWPR.BYTE |= 0x80;
	
	// IRQの設定
	//検出：1:立下り, 2:立上り
	ICU.IRQCR[0].BIT.IRQMD = 0x02;
	ICU.IRQCR[1].BIT.IRQMD = 0x02;
	
	// 優先度の設定
	IPR(ICU, IRQ0) = 6;
	IPR(ICU, IRQ1) = 6;
	
	IR(ICU, IRQ0) = 0x00;
	IR(ICU, IRQ1) = 0x00;
	
	IEN(ICU, IRQ0) = 1;
	IEN(ICU, IRQ1) = 1;

}
