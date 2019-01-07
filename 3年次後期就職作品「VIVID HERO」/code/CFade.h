//��-------------------------------------------------------------------------��
//
//	File:CFade�̃w�b�_�[�t�@�C��[CFade.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CFADE_H_
#define _CFADE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene2D.h"
#include "input.h"

//��-----------------------------------��
//
//��-----------------------------------��
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADE;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CFade : public CScene2D
{
public:
	CFade(int nPriority = PRIORITY_NUM - 1);
	virtual void Update(void);
	FADE GetFade(void);

	static CFade *Create(FADE Fade,D3DXCOLOR col,int FadeTime);

private:
	FADE	m_FadeType;
	int		m_FadeTime;
};



#endif
