//��-------------------------------------------------------------------------��
//
//	�Q�[���J�E���g�_�E���w�b�_�[�t�@�C��[game_countdown.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _GAMECOUNTDOWN_H_
#define _GAMECOUNTDOWN_H_

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define MAX_CNTDOWN_KETA		(3)						//�X�R�A�̍ő包���@����𑝂₵����score.cpp�� UpdateScore�̂�����ScoreIreko�̂O�����₵�Ă�������
#define POLYGON_CNTDOWN_NUM		(MAX_CNTDOWN_KETA * 4)	//�\������O�p�`�|���S���̐�
#define TYOUTEN_CNTDOWN_NUM		(MAX_CNTDOWN_KETA * 4)	//�X�R�A�̒��_�̌�
#define DrawCountdownPosRight	(780)					//�X�R�A�̉E�[�̈ʒu
#define DrawCountdownPosHeight	(100)					//�J�E���g�_�E���̏c�̈ʒu
#define DrawCountdownHeightW	(70)					//�X�R�A�̏c��
#define DrawCountdownPosWidth	(30)					//��̃X�R�A�̉���
#define COUNTDOWN_TIME			(60)					//��������
#define CountdownChangeColor	(30)					//�X�R�A�����̐��l�ȏ�ɂȂ�ƐԂ��Ȃ�܂�
//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
void InitCountdown(void);
void UninitCountdown(void);
void UpdateCountdown(void);
void DrawCountdown(void);

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��



#endif