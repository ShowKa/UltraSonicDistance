/*************************************************************************
	RX63N SCI

*************************************************************************/
#include "iodefine.h"
#include "typedefine.h"
#include "vect.h"

#include "sciDrv.h"

unsigned char SCI0_RX_DATA;
unsigned char SCI0_RX_FLAG;


/*============================================================
	SCI0�̎�M���荞�݊֐�
	�f�[�^���O���[�o���ϐ��Ɋi�[
	��intprg.c�̓����̊֐��������R�����g�A�E�g���Ă�������
===============================================================*/
void Excep_SCI0_RXI0(void)
{
	SCI0_RX_DATA = SCI0.RDR;
	SCI0_RX_FLAG = 1;
}

/*============================================================
	pGetChar_SCI�֐�

==============================================================*/
char pGetChar_SCI()
{
	return SCI0.RDR;

}
/*============================================================
	pSendChar_SCI�֐�
	�|�[�����O��SCI0�Ńf�[�^�𑗐M
==============================================================*/
char pSendChar_SCI(unsigned char data)
{
	while( SCI0.SSR.BIT.TEND == 0 );
	SCI0.TDR = data;
	return 0;
}

/*============================================================
	pPrint_SCI�֐�
	�|�[�����O�ŕ�����𑗐M
==============================================================*/
void pPrint_SCI(unsigned char *string, int max_length)
{
	unsigned char er = 0;
	int i = 0;
	while( string[i] != '\0' && i < max_length ) {
		er = pSendChar_SCI( string[i]);
		if( er != 0 ){	//�G���[���͂����Œ�~
			while(1);
		}
		i++;
	}
}

/*============================================================
	GetChar_SCI�֐�
	���荞�݂Ŏ擾������M�f�[�^��Ԃ�
==============================================================*/
unsigned char GetChar_SCI()
{
	return SCI0_RX_DATA;
}


/*==============	=========================================================
	Initialize SCI 0
	TXD0: P20 RXD0: P32
	
	- SCI Mode : Asyncronous Serial Communication, BitRate: 9600bps
	- Clock Source: Onchip Baud rate Generator.SCKn Pin Clock Output Off
	- SCI Clock : PCLK/4 ( n = 1 )	
	- Data Fomat : LSB First, Length: 8bit, StopBit: 1bit, Parity: None
=======================================================================*/
void initSCI0(void)
{
	/* Enable SCI0 Module */
	MSTP(SCI0) = 0;
	
	/* Stop Communication SCI0 */
	SCI0.SCR.BIT.TE = 0;		//�g�����X�~�b�g�C�l�[�u���r�b�g SCI0 Transmit Disable at setting
	SCI0.SCR.BIT.RE = 0;		//���V�[�u�C�l�[�u���r�b�g SCI0 Recive Disable at setting
	SCI0.SCR.BIT.TEIE = 0;		//�g�����X�~�b�g�G���h�C���^���v�g�C�l�[�u���r�b�g
	
	/* I/O PORT Setting */
	// PORT2.PDR.BYTE = 0x00;	// �s�v
	PORT2.PMR.BIT.B0 = 1;		// P20/TXD0 Peripheral Module
	PORT2.PMR.BIT.B1 = 1;       // P21/RXD0 Peripheral Module
	
	/*** SCI PIN Setting ***/
	MPC.PWPR.BYTE &= ~0x80;	// Release Protect
	MPC.PWPR.BYTE |= 0x40;
	
	MPC.P20PFS.BYTE = 0x0A;  //�}���`�t�@���N�V�����s���R���g���[��P726 PSEL�r�b�g: 01010b TXD0 Interrupt OFF
	MPC.P21PFS.BYTE = 0x0A;  //�}���`�t�@���N�V�����s���R���g���[��P726 PSEL�r�b�g: 01010b RXD0 Interrupt OFF 
	
	MPC.PWPR.BYTE &= ~0x40;	// Release Protect
	MPC.PWPR.BYTE |= 0x80;
	
	/* Clock Select */
	SCI0.SCR.BIT.CKE = 0;      // Clock Enable : �����{�[���[�g�W�F�l���[�^(SCK0�[�q�͓��o�̓|�[�g�Ƃ��ĉ�)
	
	/* SCI0 Module Mode Select ( all Default Value) */
	SCI0.SIMR1.BIT.IICM = 0;    // I2C Mode Select : Serial Interface Mode[default]
	SCI0.SPMR.BIT.CKPH = 0;     // Clock Phase Select : Clock Delay None
	SCI0.SPMR.BIT.CKPOL = 0;    // Clock Polarity Invert : None
	
	/* Communication Data Format Setting */

	SCI0.SMR.BIT.CKS = 0x01;   // Clock PCLK/4 n=1	( BRR )
	SCI0.SMR.BIT.MP = 0;	   // MultiProccesor communication function OFF
	SCI0.SMR.BIT.STOP = 0;     // Stop Bit : 1bit
	SCI0.SMR.BIT.PM = 0;       // Parity Mode : Even Parity
	SCI0.SMR.BIT.PE = 0;       // Parity Enable : No Parity
	SCI0.SMR.BIT.CHR = 0;      // Character Length : 8bit
	SCI0.SMR.BIT.CM = 0;     // �������������[�h

	SCI0.SCMR.BIT.SMIF = 0;    // SmartCard Interface Mode Select: Serial Communication
	SCI0.SCMR.BIT.SINV = 0;    // ����M�f�[�^�C���o�[�g(invert logic): Normal
	SCI0.SCMR.BIT.SDIR = 0;    // LSB First
	// SCI0.SCMR.BIT.BCP2 = 0x04;    // Basic Clock Pulse : 32 Clock for SmartCard
	
	SCI0.SEMR.BIT.ACS0 = 0;	    // Asynchronous Clock Source : external
	SCI0.SEMR.BIT.ABCS = 0;     // Asynchronous Base Clock Select : 16cycle
	SCI0.SEMR.BIT.NFEN = 0;     // Noise Filter Disable
	
	/* Bit Rate Setting */
	SCI0.BRR = 38;
	
	/* Enable SCI0 Communication */
	SCI0.SCR.BIT.TEIE = 1;     // Trancemit end interrupt Enable
	SCI0.SCR.BIT.MPIE = 0;     // MultiProcessor Interrupt Disable
	SCI0.SCR.BIT.RE = 1;       // Recive Enable
	SCI0.SCR.BIT.TE = 1;       // Transmit Enable
	SCI0.SCR.BIT.RIE = 1;      // Recive Interrupt Enable
	SCI0.SCR.BIT.TIE = 1;      // Transmit Interrupt Enable
	
	/**** SCI0 Interrupt Setting ***/
	/* SCI0 RXD Interrupt */
	IPR( SCI0, RXI0) = 10;	// Priory Level 10
	IR( SCI0, RXI0) = 0;	// clear status flag
	IEN( SCI0, RXI0) = 1;	// Enable Interrupt
	
	/* SCI0 TXD Interrupt */

	/* SCI0 TXE Interrupt */
}
