/*
 CMT0_�����ݓ���m�F
*/
#include <machine.h>
#include "iodefine.h"

#include "vect.h"	//�����݊֐���`���i�����݊֐��ƈꏏ�ɒǉ��j

void init_CMT0(void)
{
	// CMT�@�\�͏�����Ԏ��A�X�g�b�v��Ԃ̂��߉������삷��iP.302)
	SYSTEM.PRCR.WORD = 0xA503;
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	// CMT�̃R���y�A�}�b�`�@�\���g�p���������݁i�^�C�}�����݁j���g�p���邽�߁A�����݃t���O��ݒ肷��B
	// �����ݎw��x�N�^�e�[�u���FIER03-IEN4(P.387)
	ICU.IER[3].BIT.IEN4 = 1;
	// �����݃��x����ݒ�
	ICU.IPR[4].BYTE = 0x06;
	// CMT0���X�g�b�v
	// ����Ɋւ���ݒ��ύX���邽�߁A�K���X�g�b�v��Ԃɂ���B
	CMT.CMSTR0.BIT.STR0 = 0;
	// CMT�ɂ�銄���݂�������B
	CMT0.CMCR.BIT.CMIE = 1;
	// CMT���쎞�̃N���b�N���x��ύX����i��������ύX����B�j
	// ���݁A���Ӊ�H�̓���N���b�N��48MHz�ƂȂ��Ă��邽�߁A�J�E���g��48MHz(��0.02��S)�ŃJ�E���g�����
	// �R���y�A�}�b�`�p��r���W�X�^(CMCOR)��16bit�̂��߁A�ő�ł���1.31ms�ł���B
	// 500ms�̎��Ԃ���邽�߂ɁA��������CMCOR�𒲐�����B
	// �������� PCLK/512�ɐݒ肷��B
	CMT0.CMCR.BIT.CKS = 3;
	// 48MHz / 512 =�@93750Hz  (��10.67 ��S)
	// 500ms = 46874 �J�E���g�ŃR���y�A����悤�ɁACMCOR��ݒ肷��B
	CMT0.CMCOR = 5624;
	// (500ms *(48MHz/512)) - 1 = 46874
	 // 5624 => 60ms
	// CMCNT�̃J�E���g�l��46874�ɂȂ�ƁACMCOR�ƃR���y�A�}�b�`�������A�����ݏ��������{�B
	// �����݋��� I�t���O���P
	// �J�E���^���Z�b�g
	CMT0.CMCNT = 0;
	// CMT0 Start	
	CMT.CMSTR0.BIT.STR0 = 1; // CMT0 Start
}



