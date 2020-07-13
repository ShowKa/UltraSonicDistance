/*
 CMT0_割込み動作確認
*/
#include <machine.h>
#include "iodefine.h"

#include "vect.h"	//割込み関数定義★（割込み関数と一緒に追加）

void init_CMT0(void)
{
	// CMT機能は初期状態時、ストップ状態のため解除操作する（P.302)
	SYSTEM.PRCR.WORD = 0xA503;
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	// CMTのコンペアマッチ機能を使用した割込み（タイマ割込み）を使用するため、割込みフラグを設定する。
	// 割込み指定ベクタテーブル：IER03-IEN4(P.387)
	ICU.IER[3].BIT.IEN4 = 1;
	// 割込みレベルを設定
	ICU.IPR[4].BYTE = 0x06;
	// CMT0をストップ
	// 動作に関する設定を変更するため、必ずストップ状態にする。
	CMT.CMSTR0.BIT.STR0 = 0;
	// CMTによる割込みを許可する。
	CMT0.CMCR.BIT.CMIE = 1;
	// CMT動作時のクロック速度を変更する（分周率を変更する。）
	// 現在、周辺回路の動作クロックは48MHzとなっているため、カウントも48MHz(≒0.02μS)でカウントされる
	// コンペアマッチ用比較レジスタ(CMCOR)は16bitのため、最大でも≒1.31msである。
	// 500msの時間を作るために、分周率とCMCORを調整する。
	// 分周率を PCLK/512に設定する。
	CMT0.CMCR.BIT.CKS = 3;
	// 48MHz / 512 =　93750Hz  (≒10.67 μS)
	// 500ms = 46874 カウントでコンペアするように、CMCORを設定する。
	CMT0.CMCOR = 5624;
	// (500ms *(48MHz/512)) - 1 = 46874
	 // 5624 => 60ms
	// CMCNTのカウント値が46874になると、CMCORとコンペアマッチが発生、割込み処理を実施。
	// 割込み許可 Iフラグ＝１
	// カウンタリセット
	CMT0.CMCNT = 0;
	// CMT0 Start	
	CMT.CMSTR0.BIT.STR0 = 1; // CMT0 Start
}



