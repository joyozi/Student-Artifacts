//��-------------------------------------------------------------------------��
//
//	File:CDegeneracyStar�̃w�b�_�[�t�@�C��[CDegeneracyStar.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CDEGENERACYSTAR_H_
#define _CDEGENERACYSTAR_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CDegeneracyPolygon.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CDegeneracyStar : public CDegeneracyPolygon
{
public:
	CDegeneracyStar(int nPriority = 52);
	virtual ~CDegeneracyStar();

	virtual void SetOnlyInit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CDegeneracyStar *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot);

private:
	static const int DEGENERACYSTAR_MAX = 2048*3;

	D3DXCOLOR m_PolygonColor[DEGENERACYSTAR_MAX];
	bool m_PolygonColorJudge[DEGENERACYSTAR_MAX];

};

#endif