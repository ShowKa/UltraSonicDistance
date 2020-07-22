#include "iodefine.h"
#include <machine.h>
#include "vect.h"

unsigned  short TEMPERATURE = 0;

/*** S12AD S12ADI0 ***/
void Excep_S12AD_S12ADI0(void) {
    unsigned short int data_AN002;
    unsigned short int cal_AN002;
    S12AD.ADCSR.BIT.ADST = 1;
    data_AN002 = S12AD.ADDR2;
    cal_AN002 = (unsigned short) ((( data_AN002 * 3300 / 4096.0 -424) / 6.25 ) * 10 );
    TEMPERATURE = cal_AN002;
}

void init_S12AD(void) {
    /* Enable Module S21AD Converter */
    SYSTEM.PRCR.WORD = 0xA502;
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;
    SYSTEM.PRCR.WORD = 0xA500;
    /* P40&42 set Input pin */
    PORT4.PDR.BIT.B0 = 0;
    PORT4.PDR.BIT.B2 = 0;
    
    /* Setting PMR General I/O */
    PORT4.PMR.BIT.B0 = 0;
    PORT4.PMR.BIT.B2 = 0;
    
    /***** ADC Setting ******/

    /* Contorol Setting */
    S12AD.ADCSR.BIT.ADST = 0;  // Stop ADC
    S12AD.ADCSR.BYTE = 0x1C; 
    // Stop ADC, SingleScan, reserved, Enable Interrupt, 
    // Clock PCLK/1, trigger off, sync trigger
    
    /* channel select */
    S12AD.ADANS0.WORD = 0x05;  // ch0 convert AN000 & 002
    
    /* AD Data Format setting */
    S12AD.ADCER.BIT.ADRFMT = 0;    // Right-justfy 
    
    /**** MPC��P40�[�q���A�i���O���͒[�q�ɐݒ� ***/
    MPC.PWPR.BYTE &= ~0x80;    // �v���e�N�g����
    MPC.PWPR.BYTE |= 0x40;
    
    MPC.P40PFS.BYTE = 0x80;    // �A�i���O�[�q�ɐݒ�(ASEL�r�b�g���P)
    MPC.P42PFS.BYTE = 0x80;
    
    MPC.PWPR.BYTE &= ~0x40;    // �v���e�N�g�ݒ�
    MPC.PWPR.BYTE |= 0x80;
    
    /***** ���荞�݂̐ݒ� *****/
    ICU.IPR[102].BIT.IPR = 8;    // Priority level 8
    ICU.IR[102].BIT.IR = 0;     // clear Status Flag
    ICU.IER[0x0C].BIT.IEN6 = 1;   // Enable Interrupt
    
    // start
    S12AD.ADCSR.BIT.ADST = 1;
}
