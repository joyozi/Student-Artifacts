//��-------------------------------------------------------------------------��
//
//	File:CMissileGaze�̃w�b�_�[�t�@�C��[CMissileGaze.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CMISSILEGAZE_H_
#define _CMISSILEGAZE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene2D.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CMissileGaze : public CScene2D
{
public:
	CMissileGaze(int nPriority = 80);
	virtual ~CMissileGaze();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CMissileGaze *Create();
};


#endif
