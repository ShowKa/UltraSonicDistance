#include "iodefine.h"

void init_TPU2(void)
{
		//プロテクトの解除
	SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : 書き換え時はA5hを設定
                        // クロック発生回路関連：許可、動作モード等：許可
	
	//TPU機能の消費電力低減機能解除
	// mstp = module stop
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;	// TPUユニット0(TPU0 - 5)
						
	//プロテクトの設定
	SYSTEM.PRCR.WORD = 0xA500;  // PRKEY[7:0] : 書き換え時はA5hを設定
                        // クロック発生回路関連：禁止、動作モード等：禁止
						
	//TPU0の動作設定
	//①タイマプリスケーラ(カウント速度)の設定
	TPU2.TCR.BIT.TPSC = 7;	//内部クロック：PCLK/1024でカウント
						//46,875[Hz]で動作(λ=21.333333・・・・・[uS]) = 1カウントあたり21.33333・・・・・[uS]
						
	//②入力クロックエッジ選択ビット(エッジ：入力信号電圧の立上がり/立下りの瞬間)
	TPU2.TCR.BIT.CKEG = 1;	//立ち上がりエッジでカウント
	
	//③カウンタクリア要因選択ビット(カウンタ(TCNT)の初期化条件の設定
	TPU2.TCR.BIT.CCLR = 1;	//TGRAとコンペアマッチ(一致したとき)にクリア（初期化）
	
	//TMDR（タイマモードレジスタ）の設定
	TPU2.TMDR.BIT.MD = 0;	//通常動作設定
	
}

void start_TIMER(void)
{
	TPUA.TSTR.BIT.CST2 = 1;
}
void stop_TIMER(void)
{
	TPUA.TSTR.BIT.CST2 = 0;
}

unsigned char isStart_TIMER(void) {
	return TPUA.TSTR.BIT.CST2;
}

void delay_s(unsigned short s)
{
	int i;
	//①タイマプリスケーラ(カウント速度)の設定
	TPU2.TCR.BIT.TPSC = 7;	//内部クロック：PCLK/64でカウント
				//46,875[Hz]で動作(λ=21.333333・・・・・[uS]) = 1カウントあたり21.33333・・・・・[uS]
	
	//TGRA(タイマジェネラルレジスタA)の設定
	//初期値の設定
	TPU2.TGRA = 46874;
	
	// タイマのカウント開始
	start_TIMER();
	
	for(i = 0; i < s; i++)
	{
		while(TPU2.TSR.BIT.TGFA == 0);
		TPU2.TSR.BIT.TGFA = 0;
	}
	
	// タイマのカウント停止
	stop_TIMER();
}

void delay_ms(unsigned short ms)
{
	int i;
	//①タイマプリスケーラ(カウント速度)の設定
	TPU2.TCR.BIT.TPSC = 3;	//内部クロック：PCLK/64でカウント
				//750,000[Hz]で動作(λ=1.333333・・・・・[uS]) = 1カウントあたり1.33333・・・・・[uS]
	
	//TGRA(タイマジェネラルレジスタA)の設定
	//初期値の設定
	TPU2.TGRA = 750;

	
	// タイマのカウント停止
	start_TIMER();
	
	for(i = 0; i < ms; i++)
	{
		while(TPU2.TSR.BIT.TGFA == 0);
		TPU2.TSR.BIT.TGFA = 0;
	}
	// タイマのカウント開始
	stop_TIMER();
}

void delay_us(unsigned short us)
{
	int i;
	//①タイマプリスケーラ(カウント速度)の設定
	TPU2.TCR.BIT.TPSC = 2;	//内部クロック：PCLK/16でカウント
				//3,000,000[Hz]で動作(λ=333.3333333・・・・・[nS]) = 1カウントあたり333.33333・・・・・[nS]
	
	//TGRA(タイマジェネラルレジスタA)の設定
	//初期値の設定
	TPU2.TGRA = 3;

	
	// タイマのカウント停止
	start_TIMER();
	
	for(i = 0; i < us; i++)
	{
		while(TPU2.TSR.BIT.TGFA == 0);
		TPU2.TSR.BIT.TGFA = 0;
	}
	// タイマのカウント開始
	stop_TIMER();
}

void delay_s_dbl(double sec) {
	// sec=2.500秒 => 2 & 500
	unsigned short timerSec = (unsigned short) sec;
	unsigned short timerMSec = (unsigned short) ((sec - timerSec) * 1000);
	delay_s(timerSec);
	delay_ms(timerMSec);
}