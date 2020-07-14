#include "iodefine.h"

void ModulePowerSetup(void);		//消費電力低減機能の設定
void init_TPU0_PWM(void);			//TPU(タイマパルスユニット)の初期設定
void PWM0Wide(int wide);		//PWMの出力波形設定(Dutyの設定)
void startPWM0(void);			//PWM信号出力開始
void stopPWM0(void);			//PWM信号出力停止
void PWM_duty(int value);		//PWM_duty設定関数

//引数でH幅決める。300:duty30% 500:duty50% 800:duty80%
void PWM_duty(int value)
{
	PWM0Wide(value);
	startPWM0();	//PWM信号出力開始
}

void ModulePowerSetup(void)
{
	/* プロテクト解除 */
	SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : 書き換え時はA5hを設定
                        // クロック発生回路関連：許可、動作モード等：許可
	// TPUユニット0のモジュールストップ状態を解除
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;
	/* プロテクト再設定 */
	SYSTEM.PRCR.WORD = 0xA500;	//
}

void init_TPU0_PWM(void)
{
	ModulePowerSetup(); // モジュールストップコントロールレジスタの設定

	// 各デバイスのPFSビットに設定するため、プロテクト解除(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWEのプロテクション解除
	MPC.PWPR.BIT.PFSWE = 1;	// PFSレジスタへの書き込み許可
	
	PORT8.PMR.BIT.B6 = 0xFF;
	MPC.P86PFS.BIT.PSEL = 3;	// P86 を TIOCA0 の機能に設定★

	// PORTA.PMR.BIT.B6 = 0xFF;
	// MPC.PA6PFS.BIT.PSEL = 3;	// PA6 を TIOCA2 の機能に設定
	
	// 各デバイスのPFSビットに設定終了後の再プロテクト(P720)
	MPC.PWPR.BIT.PFSWE = 0;	// PFSレジスタへの書き込み許可
	MPC.PWPR.BIT.B0WI = 1;	// PFSWEのプロテクション解除
		
	// TPU0 のカウンタクロック設定
	TPU0.TCR.BIT.TPSC = 3;	// PCLK/64 でカウント
	//1カウントクロックあたり 1/(125[kHz] / 64) ≒ 500[uS]
	
	// TPU0 カウント要因
	TPU0.TCR.BIT.CKEG = 1;	// 立ち上がりエッジでカウント
	
	// TPU0 各GRyのコンペアマッチに関する動作
	TPU0.TIORH.BIT.IOA = 1;	// TGRAコンペアマッチで Low出力
	TPU0.TIORH.BIT.IOB = 2;	// TGRBコンペアマッチで high出力
	
	// TPU0 のTCNTクリア設定
	TPU0.TCR.BIT.CCLR = 1;	// TGRAコンペアマッチでTCNTカウンタクリア

	// TPU0 のタイマモード設定
	TPU0.TMDR.BIT.MD = 2;	// PWMモード1	
}

void PWM0Wide(int wide)
{
	TPU0.TGRA = 1000;		// 周期≒750Hz
	TPU0.TGRB = TPU0.TGRA - wide;	// H幅：500の時≒50％
}

void startPWM0(void)
{
	TPUA.TSTR.BIT.CST0 = 1;	// TPU0 カウントスタート
}