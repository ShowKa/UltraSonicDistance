#include "iodefine.h"

void init_TPU9(void);

void init_TPU9(void)
{
	//�v���e�N�g�̉���
	SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : ������������A5h��ݒ�
                        // �N���b�N������H�֘A�F���A���샂�[�h���F����
	//TPU�@�\�̏���d�͒ጸ�@�\����
	SYSTEM.MSTPCRA.BIT.MSTPA12 = 0;	// TPU���j�b�g1(TPU6 - 11)
	//�v���e�N�g�̐ݒ�
	SYSTEM.PRCR.WORD = 0xA500;  // PRKEY[7:0] : ������������A5h��ݒ�
                        // �N���b�N������H�֘A�F�֎~�A���샂�[�h���F�֎~
	//TPU0�̓���ݒ�
	//�@�^�C�}�v���X�P�[��(�J�E���g���x)�̐ݒ�
	TPU9.TCR.BIT.TPSC = 7;	//�����N���b�N�FPCLK/1024�ŃJ�E���g
						//46,875[Hz]�œ���(��=21.333333�E�E�E�E�E[uS]) = 1�J�E���g������21.33333�E�E�E�E�E[uS]
	//�A���̓N���b�N�G�b�W�I���r�b�g(�G�b�W�F���͐M���d���̗��オ��/������̏u��)
	TPU9.TCR.BIT.CKEG = 1;	//�����オ��G�b�W�ŃJ�E���g
	//�B�J�E���^�N���A�v���I���r�b�g(�J�E���^(TCNT)�̏����������̐ݒ�
	TPU9.TCR.BIT.CCLR = 1;	//TGRA�ƃR���y�A�}�b�`(��v�����Ƃ�)�ɃN���A�i�������j
	//TMDR�i�^�C�}���[�h���W�X�^�j�̐ݒ�
	TPU9.TMDR.BIT.MD = 0;	//�ʏ퓮��ݒ�
	TPU9.TGRA = 0xffff;
	TPUB.TSTR.BIT.CST9 = 1;
}
