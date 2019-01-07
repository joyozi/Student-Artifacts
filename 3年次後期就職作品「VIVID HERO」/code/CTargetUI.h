//��-------------------------------------------------------------------------��
//
//	File:CTargetUI�̃w�b�_�[�t�@�C��[CTargetUI.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CTARGETUI_H_
#define _CTARGETUI_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneBillboard.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CTargetUI : public CSceneBillboard
{
public:
	CTargetUI(int nPriority = 101);
	virtual ~CTargetUI();

	virtual void Update(void)override;
	virtual void Draw(void)override;

	static CTargetUI *Create(LPCTSTR TextureName);

private:
	bool		m_DrawJudge;
	D3DXCOLOR	m_FadeOutColor;


};


#endif
