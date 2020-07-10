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

    /* プロテクト解除 */
    SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : 書き換え時はA5hを設定
                        // クロック発生回路関連：許可、動作モード等：許可

    /* クロック用端子設定 */
    PORT3.PDR.BYTE = 0x00;    // PORT3 all input 
    PORT3.PMR.BYTE = 0xC0;    // P37: XTAL, P36: EXTAL
    
    /* 発振器ウェイトコントロール */
    SYSTEM.MOSCWTCR.BYTE = 0x0E;  // main clock wait : 262144サイクル
    SYSTEM.SOSCWTCR.BYTE = 0x0E;  // sub clock wait  : 262144サイクル

    /* 禁止状態確認 */
    while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);
    while(FLASH.FENTRYR.BIT.FENTRY0 == 1);
    while(FLASH.FENTRYR.BIT.FENTRY1 == 1);
    while(FLASH.FENTRYR.BIT.FENTRY2 == 1);
    while(FLASH.FENTRYR.BIT.FENTRY3 == 1);

    SYSTEM.MOSCCR.BYTE = 0x00;          /* メインクロック発振器動作 */
    while(SYSTEM.MOSCCR.BYTE == 0x01);    /* 反映されるまで待つ */
    
    SYSTEM.PLLCR.WORD = 0x0F00;            /* PLL 逓倍×16 入力1分周 */
    SYSTEM.PLLCR2.BYTE = 0x00;            /* PLL ENABLE */

    SYSTEM.PLLWTCR.BYTE = 0x0F;        /* 4194304cycle(Default) */

    for(i = 0;i< 200;i++)                /* wait */
    { }

    /* System Clock Setting (メインクロックから分周) */
    SYSTEM.SCKCR.LONG = 0x21C21211; 
        /* FCK1/4 ICK1/2 BCLK停止 SDCLK停止 BCK1/4 PCLKA1/2 PCLKB1/4 */
    SYSTEM.SCKCR2.WORD = 0x0032;        /* UCLK1/4 IEBCK1/4 */
    SYSTEM.BCKCR.BYTE = 0x01;            /* BCLK = 1/2 */

    /* System Clockのソースクロックを選択 */
    SYSTEM.SCKCR3.WORD = 0x0400;        /* PLL回路選択 */
}
