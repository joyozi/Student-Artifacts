//��-------------------------------------------------------------------------��
//
//	�X�R�Ah�t�@�C��[score.h]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��
#ifndef _SCORE_H_
#define _SCORE_H_

#define POLYGON_sNUM	(MAX_SCORE_KETA * 4)	//�\������O�p�`�|���S���̐�
#define TYOUTEN_sNUM	(MAX_SCORE_KETA * 4)	//�X�R�A�̒��_�̌�
#define DrawScorePosRight (1200)					//�X�R�A�̍��[�̈ʒu
#define DrawScorePosHeight (70)					//�X�R�A�̏c��
#define DrawScorePosWidth  (30)					//��̃X�R�A�̉���
#define MAX_SCORE_KETA	   (5)					//�X�R�A�̍ő包��

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void PlusScore(int score);

#endif _SCORE_H_