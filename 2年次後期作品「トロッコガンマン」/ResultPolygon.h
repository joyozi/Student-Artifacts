//��-------------------------------------------------------------------------��
//
//	���U���g�|���S��h�t�@�C��[ResultPolygon.h]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��
#ifndef _RESULT_POLYGON_H_
#define _RESULT_POLYGON_H_

#define POLYGON_NUM (8)			//�\������O�p�`�|���S���̐�
#define TYOUTEN_NUM (8)			//���_�̌�
#define IDOURYOU	(10)		//�����C���O�}���̈ړ���
#define POLYGON_YOKO (80)		//�|���S���̏����̒��Sx���W
#define POLYGON_TATE (340)		//�|���S���̏����̒��Sy���W
//#define POLYGON_YOKOLONG (270)	//�|���S���̉��̒���
//#define POLYGON_TATELONG (550)	//�|���S���̏c�̒���
#define POLYGON_ZOOM	 (150)	//�|���S���̊g��k���̗�

void InitResultPolygon(bool Judge);
void UninitResultPolygon(void);
void UpdateResultPolygon(void);
void DrawResultPolygon(void);


#endif