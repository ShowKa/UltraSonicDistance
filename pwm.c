#include "iodefine.h"

void ModulePowerSetup(void);		//����d�͒ጸ�@�\�̐ݒ�
void init_TPU0_PWM(void);			//TPU(�^�C�}�p���X���j�b�g)�̏����ݒ�
void PWM0Wide(int wide);		//PWM�̏o�͔g�`�ݒ�(Duty�̐ݒ�)
void startPWM0(void);			//PWM�M���o�͊J�n
void stopPWM0(void);			//PWM�M���o�͒�~
void PWM_duty(int value);		//PWM_duty�ݒ�֐�

//������H�����߂�B300:duty30% 500:duty50% 800:duty80%
void PWM_duty(int value)
{
	PWM0Wide(value);
	startPWM0();	//PWM�M���o�͊J�n
}

void ModulePowerSetup(void)
{
	/* �v���e�N�g���� */
	SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : ������������A5h��ݒ�
                        // �N���b�N������H�֘A�F���A���샂�[�h���F����
	// TPU���j�b�g0�̃��W���[���X�g�b�v��Ԃ�����
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;
	/* �v���e�N�g�Đݒ� */
	SYSTEM.PRCR.WORD = 0xA500;	//
}

void init_TPU0_PWM(void)
{
	ModulePowerSetup(); // ���W���[���X�g�b�v�R���g���[�����W�X�^�̐ݒ�

	// �e�f�o�C�X��PFS�r�b�g�ɐݒ肷�邽�߁A�v���e�N�g����(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWE�̃v���e�N�V��������
	MPC.PWPR.BIT.PFSWE = 1;	// PFS���W�X�^�ւ̏������݋���
	
	PORT8.PMR.BIT.B6 = 0xFF;
	MPC.P86PFS.BIT.PSEL = 3;	// P86 �� TIOCA0 �̋@�\�ɐݒ聚

	// PORTA.PMR.BIT.B6 = 0xFF;
	// MPC.PA6PFS.BIT.PSEL = 3;	// PA6 �� TIOCA2 �̋@�\�ɐݒ�
	
	// �e�f�o�C�X��PFS�r�b�g�ɐݒ�I����̍ăv���e�N�g(P720)
	MPC.PWPR.BIT.PFSWE = 0;	// PFS���W�X�^�ւ̏������݋���
	MPC.PWPR.BIT.B0WI = 1;	// PFSWE�̃v���e�N�V��������
		
	// TPU0 �̃J�E���^�N���b�N�ݒ�
	TPU0.TCR.BIT.TPSC = 3;	// PCLK/64 �ŃJ�E���g
	//1�J�E���g�N���b�N������ 1/(125[kHz] / 64) �� 500[uS]
	
	// TPU0 �J�E���g�v��
	TPU0.TCR.BIT.CKEG = 1;	// �����オ��G�b�W�ŃJ�E���g
	
	// TPU0 �eGRy�̃R���y�A�}�b�`�Ɋւ��铮��
	TPU0.TIORH.BIT.IOA = 1;	// TGRA�R���y�A�}�b�`�� Low�o��
	TPU0.TIORH.BIT.IOB = 2;	// TGRB�R���y�A�}�b�`�� high�o��
	
	// TPU0 ��TCNT�N���A�ݒ�
	TPU0.TCR.BIT.CCLR = 1;	// TGRA�R���y�A�}�b�`��TCNT�J�E���^�N���A

	// TPU0 �̃^�C�}���[�h�ݒ�
	TPU0.TMDR.BIT.MD = 2;	// PWM���[�h1	
}

void PWM0Wide(int wide)
{
	TPU0.TGRA = 1000;		// ������750Hz
	TPU0.TGRB = TPU0.TGRA - wide;	// H���F500�̎���50��
}

void startPWM0(void)
{
	TPUA.TSTR.BIT.CST0 = 1;	// TPU0 �J�E���g�X�^�[�g
}