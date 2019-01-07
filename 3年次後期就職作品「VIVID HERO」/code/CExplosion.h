//��-------------------------------------------------------------------------��
//
//	File:CExplosion�̃w�b�_�[�t�@�C��[CExplosion.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CEXPLOSION_H_
#define _CEXPLOSION_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CSceneBillboard.h"
#include "CManager.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CExplosion : public CSceneBillboard
{
public:
	CExplosion(int nPriority = 22);

	HRESULT Init(void);
	void Update(void);
	
	static CExplosion *Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight);

private:
	static const int	EXPLOSION_SEPARATE_NUM = 7;	//�����A�j���[�V�����̃e�N�X�`�������������邩
	static const int	EXPLOSION_COUNT = 5;			//���b�ŃA�j����؂�ւ��邩
	int					m_CounterAnim;								//�A�j�����ς���Ă����J�E���g
	int					m_PatternAnim;								//���Ԗڂ̃A�j����
};

#endif
