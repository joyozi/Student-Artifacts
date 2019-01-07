//��-------------------------------------------------------------------------��
//
//	�^�C�g���|���S��h�t�@�C��[TittlePolygon.h]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��
#ifndef _TITTLE_POLYGON_H_
#define _TITTLE_POLYGON_H_

#define TITTLE_POLYGON_NUM (2)			//�\������O�p�`�|���S���̐�
#define TITTLE_TYOUTEN_NUM (4)			//���_�̌�
#define TITTLE_IDOURYOU	(10)			//�����C���O�}���̈ړ���
#define TITTLE_POLYGON_YOKO (80)		//�|���S���̏����̒��Sx���W
#define TITTLE_POLYGON_TATE (340)		//�|���S���̏����̒��Sy���W
#define TITTLE_POLYGON_YOKOLONG (270)	//�|���S���̉��̒���
#define TITTLE_POLYGON_TATELONG (550)	//�|���S���̏c�̒���
#define TITTLE_POLYGON_ZOOM	 (150)		//�|���S���̊g��k���̗�
#define TENMETU_TIME			(30)	//�v���X�G���^�[���_�ł���Ԋu
#define TENMETU_TIME_FADEOUT	(5)	//�v���X�G���^�[���_�ł���Ԋu


void InitTittlePolygon(void);
void UninitTittlePolygon(void);
void UpdateTittlePolygon(void);
void DrawTittlePolygon(void);


#endif