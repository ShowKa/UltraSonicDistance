/************************************************************************
*
* Device     : RX/RX600/RX63N,RX631
*
* File Name  : hwsetup.c
*
* Abstract   : Hardware Setup file.
*
* History    : 0.10  (2011-02-21)  [Hardware Manual Revision : 0.01]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2011 Renesas Electronics Corporation.
* and Renesas Solutions Corp.
*
************************************************************************/
#include "iodefine.h"
extern void HardwareSetup(void);
void HardwareSetup(void)
{
	int i;

    /* �v���e�N�g���� */
    SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : ������������A5h��ݒ�
                        // �N���b�N������H�֘A�F���A���샂�[�h���F����

    /* �N���b�N�p�[�q�ݒ� */
    PORT3.PDR.BYTE = 0x00;    // PORT3 all input 
    PORT3.PMR.BYTE = 0xC0;    // P37: XTAL, P36: EXTAL
    
    /* ���U��E�F�C�g�R���g���[�� */
    SYSTEM.MOSCWTCR.BYTE = 0x0E;  // main clock wait : 262144�T�C�N��
    SYSTEM.SOSCWTCR.BYTE = 0x0E;  // sub clock wait  : 262144�T�C�N��

    /* �֎~��Ԋm�F */
    while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);
    while(FLASH.FENTRYR.BIT.FENTRY0 == 1);
    while(FLASH.FENTRYR.BIT.FENTRY1 == 1);
    while(FLASH.FENTRYR.BIT.FENTRY2 == 1);
    while(FLASH.FENTRYR.BIT.FENTRY3 == 1);

    SYSTEM.MOSCCR.BYTE = 0x00;          /* ���C���N���b�N���U�퓮�� */
    while(SYSTEM.MOSCCR.BYTE == 0x01);    /* ���f�����܂ő҂� */
    
    SYSTEM.PLLCR.WORD = 0x0F00;            /* PLL ���{�~16 ����1���� */
    SYSTEM.PLLCR2.BYTE = 0x00;            /* PLL ENABLE */

    SYSTEM.PLLWTCR.BYTE = 0x0F;        /* 4194304cycle(Default) */

    for(i = 0;i< 200;i++)                /* wait */
    { }

    /* System Clock Setting (���C���N���b�N���番��) */
    SYSTEM.SCKCR.LONG = 0x21C21211; 
        /* FCK1/4 ICK1/2 BCLK��~ SDCLK��~ BCK1/4 PCLKA1/2 PCLKB1/4 */
    SYSTEM.SCKCR2.WORD = 0x0032;        /* UCLK1/4 IEBCK1/4 */
    SYSTEM.BCKCR.BYTE = 0x01;            /* BCLK = 1/2 */

    /* System Clock�̃\�[�X�N���b�N��I�� */
    SYSTEM.SCKCR3.WORD = 0x0400;        /* PLL��H�I�� */
}
