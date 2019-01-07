//��-------------------------------------------------------------------------��
//
//	File:���b�V���X�J�C�̃w�b�_�[�t�@�C��[CMeshSky.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CMESHSKY_H_
#define _CMESHSKY_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CMeshBasisClass.h"

//��-----------------------------------��
//�}�N����`
//��-----------------------------------��
#define MESHSKY_PELYGON_WIDTH		(1000)		//�|���S���̉�
#define MESHSKY_POLYGON_HEIGHT		(4000)		//�|���S���c
#define MESHSKY_BUNKATSU			(20)		//���̕����@�ォ�猩���Ƃ����p�`�ɕ������邩�B3�����ȏ��
#define MESHSKY_DANSUU				(10)		//�c�̕����@�����猩�����̒i��

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CMeshSky : public CMeshBasisClass
{
public:
	CMeshSky(int nPriority = 34);
	~CMeshSky();

	HRESULT Init(void);
	void Update(void);

	static CMeshSky *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot);
};

#endif
