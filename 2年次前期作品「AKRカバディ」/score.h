//��-------------------------------------------------------------------------��
//
//	�X�R�Ah�t�@�C��[score.h]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��
#ifndef _SCORE_H_
#define _SCORE_H_

#define MAX_SCORE_KETA		(3)						//�X�R�A�̍ő包���@����𑝂₵����score.cpp�� UpdateScore�̂�����ScoreIreko�̂O�����₵�Ă�������
#define POLYGON_sNUM		(MAX_SCORE_KETA * 4)	//�\������O�p�`�|���S���̐�
#define TYOUTEN_sNUM		(MAX_SCORE_KETA * 4)	//�X�R�A�̒��_�̌�
#define DrawScorePosRight	(780)					//�X�R�A�̍��[�̈ʒu
#define DrawScorePosHeight	(70)					//�X�R�A�̏c��
#define DrawScorePosWidth	(30)					//��̃X�R�A�̉���
#define PlusScore			(10)					//���Z�����
#define MinusScore			(10)					//���Z�����
#define ScoreChangeColor	(500)					//�X�R�A�����̐��l�ȏ�ɂȂ�ƐԂ��Ȃ�܂�

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void GetScore(void);

#endif _SCORE_H_