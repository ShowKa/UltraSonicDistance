#include "iodefine.h"

void init_TPU2(void)
{
		//�v���e�N�g�̉���
	SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : ������������A5h��ݒ�
                        // �N���b�N������H�֘A�F���A���샂�[�h���F����
	
	//TPU�@�\�̏���d�͒ጸ�@�\����
	// mstp = module stop
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;	// TPU���j�b�g0(TPU0 - 5)
						
	//�v���e�N�g�̐ݒ�
	SYSTEM.PRCR.WORD = 0xA500;  // PRKEY[7:0] : ������������A5h��ݒ�
                        // �N���b�N������H�֘A�F�֎~�A���샂�[�h���F�֎~
						
	//TPU0�̓���ݒ�
	//�@�^�C�}�v���X�P�[��(�J�E���g���x)�̐ݒ�
	TPU2.TCR.BIT.TPSC = 7;	//�����N���b�N�FPCLK/1024�ŃJ�E���g
						//46,875[Hz]�œ���(��=21.333333�E�E�E�E�E[uS]) = 1�J�E���g������21.33333�E�E�E�E�E[uS]
						
	//�A���̓N���b�N�G�b�W�I���r�b�g(�G�b�W�F���͐M���d���̗��オ��/������̏u��)
	TPU2.TCR.BIT.CKEG = 1;	//�����オ��G�b�W�ŃJ�E���g
	
	//�B�J�E���^�N���A�v���I���r�b�g(�J�E���^(TCNT)�̏����������̐ݒ�
	TPU2.TCR.BIT.CCLR = 1;	//TGRA�ƃR���y�A�}�b�`(��v�����Ƃ�)�ɃN���A�i�������j
	
	//TMDR�i�^�C�}���[�h���W�X�^�j�̐ݒ�
	TPU2.TMDR.BIT.MD = 0;	//�ʏ퓮��ݒ�
	
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
	//�@�^�C�}�v���X�P�[��(�J�E���g���x)�̐ݒ�
	TPU2.TCR.BIT.TPSC = 7;	//�����N���b�N�FPCLK/64�ŃJ�E���g
				//46,875[Hz]�œ���(��=21.333333�E�E�E�E�E[uS]) = 1�J�E���g������21.33333�E�E�E�E�E[uS]
	
	//TGRA(�^�C�}�W�F�l�������W�X�^A)�̐ݒ�
	//�����l�̐ݒ�
	TPU2.TGRA = 46874;
	
	// �^�C�}�̃J�E���g�J�n
	start_TIMER();
	
	for(i = 0; i < s; i++)
	{
		while(TPU2.TSR.BIT.TGFA == 0);
		TPU2.TSR.BIT.TGFA = 0;
	}
	
	// �^�C�}�̃J�E���g��~
	stop_TIMER();
}

void delay_ms(unsigned short ms)
{
	int i;
	//�@�^�C�}�v���X�P�[��(�J�E���g���x)�̐ݒ�
	TPU2.TCR.BIT.TPSC = 3;	//�����N���b�N�FPCLK/64�ŃJ�E���g
				//750,000[Hz]�œ���(��=1.333333�E�E�E�E�E[uS]) = 1�J�E���g������1.33333�E�E�E�E�E[uS]
	
	//TGRA(�^�C�}�W�F�l�������W�X�^A)�̐ݒ�
	//�����l�̐ݒ�
	TPU2.TGRA = 750;

	
	// �^�C�}�̃J�E���g��~
	start_TIMER();
	
	for(i = 0; i < ms; i++)
	{
		while(TPU2.TSR.BIT.TGFA == 0);
		TPU2.TSR.BIT.TGFA = 0;
	}
	// �^�C�}�̃J�E���g�J�n
	stop_TIMER();
}

void delay_us(unsigned short us)
{
	int i;
	//�@�^�C�}�v���X�P�[��(�J�E���g���x)�̐ݒ�
	TPU2.TCR.BIT.TPSC = 2;	//�����N���b�N�FPCLK/16�ŃJ�E���g
				//3,000,000[Hz]�œ���(��=333.3333333�E�E�E�E�E[nS]) = 1�J�E���g������333.33333�E�E�E�E�E[nS]
	
	//TGRA(�^�C�}�W�F�l�������W�X�^A)�̐ݒ�
	//�����l�̐ݒ�
	TPU2.TGRA = 3;

	
	// �^�C�}�̃J�E���g��~
	start_TIMER();
	
	for(i = 0; i < us; i++)
	{
		while(TPU2.TSR.BIT.TGFA == 0);
		TPU2.TSR.BIT.TGFA = 0;
	}
	// �^�C�}�̃J�E���g�J�n
	stop_TIMER();
}

void delay_s_dbl(double sec) {
	// sec=2.500�b => 2 & 500
	unsigned short timerSec = (unsigned short) sec;
	unsigned short timerMSec = (unsigned short) ((sec - timerSec) * 1000);
	delay_s(timerSec);
	delay_ms(timerMSec);
}