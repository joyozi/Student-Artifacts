//��-------------------------------------------------------------------------��
//
//	File:CMeshBasisClass�̃w�b�_�[�t�@�C��[CMeshBasisClass.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _MESHBASISCLASS_H_
#define _MESHBASISCLASS_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
//#include "main.h"
#include "CScene3D.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CMeshBasisClass : public CScene3D
{
public:
	CMeshBasisClass(int nPriority = 31);
	virtual ~CMeshBasisClass();

	virtual void Uninit(void);
	virtual void Draw(void);

protected:
	LPDIRECT3DINDEXBUFFER9	m_IdxBuffer;
	int						m_VtxNum;
	int						m_IndexNum;
	int						m_PolygonNum;
	WORD*					m_pIdx;
};


#endif
