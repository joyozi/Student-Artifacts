//��-------------------------------------------------------------------------��
//
//	���U���g�|���S��h�t�@�C��[ResultPolygon.h]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��
#ifndef _RESULT_POLYGON_H_
#define _RESULT_POLYGON_H_

#define RESULT_POLYGON_NUM (8)			//�\������O�p�`�|���S���̐�
#define TYOUTEN_NUM (8)					//���_�̌�
#define POLYGON_ZOOM	 (150)			//�|���S���̊g��k���̗�

void InitResultPolygon(void);
void UninitResultPolygon(void);
void UpdateResultPolygon(void);
void DrawResultPolygon(void);


#endif